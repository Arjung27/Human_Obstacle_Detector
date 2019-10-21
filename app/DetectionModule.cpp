/******************************************************************************
 *  MIT License
 *
 *  Copyright (c) 2019 Rohan Singh, Arjun Gupta
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *******************************************************************************/

/**
 * @file      DetectionModule.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Definition for DetectionModule class
 */

#include <iostream>
#include "DetectionModule.hpp"

DetectionModule::DetectionModule() {
    /* Default input choice */
    inputChoice = 1;
}

auto DetectionModule::getFrame(std::string filePath, int cameraID, \
                        std::string outputDirectory, int choice) -> int {
  int frameID = 0;
  inputChoice = choice;
  char filterType = 'G';
  cv::Mat image;
  /* The conditions below check the input type entered by the user and
     then read the data accordingly and feed it to the network */
  if (inputChoice == 1) {
    image = cv::imread(filePath);
    if (!image.data) {
      std::cout << "ERROR: Invalid image input" << std::endl;
      return 0;
    }
    image = preProcessImage(image, filterType);
    int flag = detectObjects(image);
    if (flag != 0) {
      image = postProcessImage(image, frameID);
    }
    frameID += 1;
    cv::imwrite(outputDirectory + "testImageDetection.jpg", image);
  } else if (inputChoice == 2) {
      videoFrames = cv::VideoCapture(filePath);
      /* Check if the file entered by the user is correct */
      if (!videoFrames.isOpened()) {
        std::cout << "Error: Invalid video file" << std::endl;
        return 0;
      }
      videoWriter.open(outputDirectory + "testVideoDetection.avi", \
      cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 15.0, \
      cv::Size(416, 416), true);
      /* Read frames and pass each frame as an image to the network */
      while (videoFrames.read(image)) {
        if (image.empty()) {
          break;
        }
        image = preProcessImage(image, filterType);
        int flag = detectObjects(image);
        if (flag != 0) {
          image = postProcessImage(image, frameID);
        }
        frameID += 1;
        videoWriter.write(image);
      }
  } else if (inputChoice == 3) {
    if (cameraID < 0) {
      return 0;
    } else {
      /* Check if the cameraID entered by the user is correct */
      videoFrames = cv::VideoCapture(cameraID);
      if (!videoFrames.isOpened()) {
        std::cout << "Error: Invalid camera ID" << std::endl;
        return 0;
      }
      /* Read frames and pass each frame as an image to the network */
      while (videoFrames.read(image)) {
        image = preProcessImage(image, filterType);
        int flag = detectObjects(image);
        if (flag != 0) {
          image = postProcessImage(image, frameID);
        }
        frameID += 1;
        cv::imshow("Box", image);
        /* Press esc to stop the feed from the camera */
        char c = static_cast<char>(cv::waitKey(25));
        if (c == 27) {
          break;
        }
      }
    }
  }
  io.saveOutput(finalDetections, outputDirectory);
  return 1;
}

auto DetectionModule::getInput() -> void {
  inputChoice = io.getInputChoice();
  std::string filePath, outputDirectory;
  int cameraID;
  /* Take the input about the file according to the inputChoice */
  if (inputChoice == 1 || inputChoice == 2) {
    filePath = io.getInputFilePath();
  } else {
    cameraID = io.getDeviceID();
  }
  outputDirectory = io.getOutputFilePath();
  int exitStatus = getFrame(filePath, cameraID, outputDirectory, inputChoice);
  if (exitStatus == 0) {
    exit(10);
  }
}

auto DetectionModule::preProcessImage(cv::Mat image, \
                                      char filterType) -> cv::Mat {
  /* Sixe of the image after reshaping */
  cv::Size size(416, 416);
  image = VisionModule::reshape(image, size);
  if (filterType == 'G') {
    /* The kernel dimension for gaussian filter */
    cv::Size kernelDim(3, 3);
    float sigma = 0;
    image = VisionModule::applyGaussianFilter(image, kernelDim, sigma);
  } else if (filterType == 'M') {
    /* The kernel dimension for median filter */
    int kernelDim = 3;
    image = VisionModule::applyMedianFilter(image, kernelDim);
  } else if (filterType == 'B') {
    /* The kernel dimension for standard/mean filter */
    cv::Size kernelDim(3, 3);
    image = VisionModule::applyFilter(image, kernelDim);
  }
  return image;
}

auto DetectionModule::detectObjects(cv::Mat image) -> int {
  /* Converts the image in consideration to blob */
  int flag = network.createNetworkInput(image);
  if (flag == 1) {
    detectedObjects = network.applyYOLONetwork();
    /* Check if any objects are detected in the passed image or not */
    if ((detectedObjects).size() == 0) {
      return 0;
    }
  }
  return 1;
}

auto DetectionModule::postProcessImage(cv::Mat frame, int frameID) -> cv::Mat {
  std::vector<int> classIds;
  std::vector<float> confidenceScores;
  std::vector<cv::Rect> predictedBoxes;
  /* Iterate over all the bounding boxes prediced by the network */
  for (auto objects : detectedObjects) {
    float* object = reinterpret_cast<float*>(objects.data);
    for (int i = 0; i < objects.rows; ++i, object += objects.cols) {
      cv::Mat predictedScores = objects.row(i).colRange(5, objects.cols);
      cv::Point classId;
      double confidence;
      /* Find the global minimum and maximum in an array */
      cv::minMaxLoc(predictedScores, 0, &confidence, 0, &classId);
      /* Checks if the bounding box's confidence score is greated then
      threshold or not and if yes then store it */
      if (confidence > confidenceThreshold) {
        int centerCoordinateX = static_cast<int>(object[0] * \
                                                    frame.cols);
        int centerCoordinateY = static_cast<int>(object[0] * \
                                                    frame.rows);
        int boxWidth = static_cast<int>(object[2] * \
                                                    frame.cols);
        int boxHeight = static_cast<int>(object[3] * \
                                                    frame.rows);
        int topLeftX = (centerCoordinateX - boxWidth/2);
        /* if calculated topLeftX is -ve then make it zero */
        if (topLeftX < 0) topLeftX = 0;
        int topLeftY = (centerCoordinateY - boxHeight/2);
        /* if calculated topLeftY is -ve then make it zero */
        if (topLeftY < 0) topLeftY = 0;
        classIds.push_back(classId.x);
        confidenceScores.push_back(static_cast<float>(confidence));
        predictedBoxes.push_back(cv::Rect(topLeftX, topLeftY, \
                                                boxWidth, boxHeight));
      }
    }
  }
  std::vector< std::vector <int> > Detections = \
              VisionModule::nonMaximalSuppression(frame, \
              predictedBoxes, confidenceScores, classIds, frameID);
  /* Intrinsic Matrix for the transformation */
  cv::Mat intrinsic = cv::Mat::eye(3, 3, CV_32F);
  /* Iterates over each detection and get the detectons in robot's
  perspective frame */
  for (auto values : Detections) {
    cv::Mat coordinates = cv::Mat(2, 1, CV_32F, \
        {static_cast<float>(values[1]), static_cast<float>(values[2])});
    cv::Mat imagetoCamera = tf.imageToCamera(intrinsic, coordinates);
    cv::Mat endtoBase = tf.endToBase(imagetoCamera);
    cv::Mat cameratoImage = tf.cameraToImage(intrinsic, endtoBase);
    int newx1 = cameratoImage.at<float>(0, 0);
    int newy1 = cameratoImage.at<float>(1, 0);
    cv::Mat coordinates1 = cv::Mat(2, 1, CV_32F, \
        {static_cast<float>(values[3]), static_cast<float>(values[4])});
    cv::Mat imagetoCamera1 = tf.imageToCamera(intrinsic, coordinates1);
    cv::Mat endtoBase1 = tf.endToBase(imagetoCamera1);
    cv::Mat cameratoImage1 = tf.cameraToImage(intrinsic, endtoBase1);
    int newx2 = cameratoImage1.at<float>(0, 0);
    int newy2 = cameratoImage1.at<float>(1, 0);
    /* Storing the detections to temporary variable for next step */
    std::vector <int> transformedDetections{values[0], newx1, newy1, \
                                    newx2, newy2};
    finalDetections.push_back(transformedDetections);
  }
  return frame;
}
DetectionModule::~DetectionModule() {
}
