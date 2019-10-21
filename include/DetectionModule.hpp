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
 * @file      DetectionModule.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares DetectionModule child class inheriting from VisionModule
 */

#ifndef INCLUDE_DETECTIONMODULE_HPP_
#define INCLUDE_DETECTIONMODULE_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "VisionModule.hpp"
#include "IOHandler.hpp"
#include "Network.hpp"
#include "Transformation.hpp"

/**
 * @brief Class for Implementing Human Obstacle Detection Algorithms
 *
 * Inherits from VisionModule class
 */
class DetectionModule : public VisionModule {
 private:
  /* Object of class Network */
  Network network;
  /* Object of class Transformation */
  Transformation tf;
  /* Object of class IOHandler */
  IOHandler io;
  /* Contains final detection information for one frame */
  std::vector<cv::Mat> detectedObjects;
  /* Choice of input - Image, Video or Live Cam Feed */
  int inputChoice;
  /* Object to parse the video frames */
  cv::VideoCapture videoFrames;
  /* Object to write the video frames*/
  cv::VideoWriter videoWriter;
  /* Confidence Threshold for the predictions */
  float confidenceThreshold = 0.9;
  /* Non-Maximum Threshold Value */
  float nmsThreshold = 0.9;
  /* Vector to store the vector of detection information */
  std::vector< std::vector <int> > finalDetections;

 public :
  /**
   * @brief Constructor for class
   */
  DetectionModule();

  /** 
   * @brief Destrcutor for class
   */
  ~DetectionModule();

  /**
   * @brief Function passes the processed image to the network
   *
   * The functions takes input the processed image and then calls another
   * function inside it to convert the image to blob
   * 
   * @param image the processed image in form of the matrix
   * @return Returns an int with an error code. Returns 0 if the total 
   * number of the detections is zero and 1 if not.
   */
  int detectObjects(cv::Mat image);

  /**
   * @brief Processes the current frame (image) before passing to the
   *        detection network
   *
   * Removes noise from the image and resizes it to appropriate shape
   *
   * @param image Current frame (image) on which detection is to be done
   * @param filterType Type of filter to be used for removing noise
   *
   * @return Image after Processing
   */
  cv::Mat preProcessImage(cv::Mat image, char filterType);

  /**
   * @brief Processes the current frame (image) and the obtained detection
   *        information from the detection network
   *
   * Filters obtained bounding boxes predicted from the network (using
   * confidence threshold) and calls the function to apply NMS and draw
   * the boxes on image for visualization.
   *
   * @param frame image on which the postProcessing would occur
   * @param frameID ID of the frame which is parsed
   *
   * @return Image after Processing
   */
  cv::Mat postProcessImage(cv::Mat frame, int frameID);

  /**
   * @brief Function to get input from user. Uses IOHandler functionality
   *
   * @return void
   */
  void getInput();
  /**
   * @brief Function to call all the other functions of the class and also
   *        the functions of class with part of relationship
   * 
   * This function performs the fundamental role in the module. It integrates
   * all the preprocess and postprocess of the data with the functionality of 
   * the network.
   * 
   * @param filePath contains the path of the file to be parsed and feeded to
   *                 the network.
   * @param cameraID contains the cameraID if user choses camera to be the mode
   *                 of input.
   * @param outputDirectory path where the results need to be stored  
   * @param choice Choice of input format(image/video/camera) given by user
   * 
   * @return 0 if the data is invalid or the cameraID is invalid and return 1
   *        if the module runs successfully.
   */
  int getFrame(std::string filePath, int cameraID, \
                        std::string outputDirectory, int choice);
};

#endif    // INCLUDE_DETECTIONMODULE_HPP_
