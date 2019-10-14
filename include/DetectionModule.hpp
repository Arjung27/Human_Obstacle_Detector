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

#include "VisionModule.hpp"
#include "Interface.hpp"
#include "Camera.hpp"
#include "IOHandler.hpp"

/**
 * @brief Class for Implementing Human Obstacle Detection Algorithms
 *
 * Inherits from VisionModule class
 */
class DetectionModule : public VisionModule {
 public :
  /**
   * @brief Constructor for class
   */
  DetectionModule();

  /**
   * @brief Constructor with params for class
   *
   * @param io Object containing Input/Output functionality
   * @param camera Object containing Camera information
   */
  DetectionModule(IOHandler io, Camera camera);

  /** 
   * @brief Destrcutor for class
   */
  ~DetectionModule();

  /**
   * @brief Function executing the main pipeline of the detection module
   *
   * Gets input, processes images, runs detection network on image, filters
   * obtained detections, transforms obtained bounding boxes to robot frame
   * and finally save output.
   *
   * @return Returns an int with an error code. Returns 0 if execution is
   *         completed with no errors
   */
  int detectObjects();

  /**
   * @brief Processes the current frame (image) before passing to the
   *        detection network
   *
   * Removes noise from the image and resizes it to appropriate shape
   *
   * @param image Current frame (image) on which detection is to be done
   *
   * @return Image after Processing
   */
  cv::Mat preProcessImage(cv::Mat image);

  /**
   * @brief Processes the current frame (image) and the obtained detection
   *        information from the detection network
   *
   * Filters obtained bounding boxes from the network (using non-maximal
   * suppresion) and draws the boxes on image for visualization.
   *
   * @param boxes Vector of OpenCV matrices containing bounding box information
   *
   * @return Image after Processing
   */
  cv::Mat postProcessImage(cv::Mat image);

  /**
   * @brief Function to get input from user. Uses IOHandler functionality
   *
   * @return Returns an int with an error code. Returns 0 if execution is
   *         completed with no errors
   */
  int getInput();

 private:
  Camera camera;
  Network network;
  Transformation tf;
  IOHandler io;

  /* Contains final detection information for one frame */
  std::vector<std::vector<float>> detectedObjects;

  /* Choice of input - Image, Video or Live Cam Feed */
  int inputChoice;
}

#endif    // INCLUDE_DETECTIONMODULE_HPP_
