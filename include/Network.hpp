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
 * @file      Network.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares Network class
 */

#ifndef INCLUDE_NETWORK_HPP_
#define INCLUDE_NETWORK_HPP_

#include <iostream>
#include<vector>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief Class for Implementing Neural Network for Human Detection
 *
 */
class Network {
 private:
  /* Network object */
  cv::dnn::Net yoloNetwork;
  /* Contains file path to network weights */
  cv::String weightsFilePath;

  /* Contains file path to network onfiguration */
  cv::String configurationFilePath;

  /* Confidence Threshold for the predictions */
  float confidenceThreshold = 0.9;

  /* Non-Maximum Threshold Value */
  float nmsThreshold = 0.9;

  /* Image/Frame Width and Height */
  int imageWidth = 416;
  int imageHeight = 416;
  /* Input blob to the network */
  cv::Mat blob;
 public :
  /**
   * @brief Constructor for class
   */
  Network();

  /** 
   * @brief Destrcutor for class
   */
  ~Network();

  /**
   * @brief Function to convert the given image input into appropriate 
   *        format for the network
   *
   * @param image Input image on which the detection is to be performed
   *
   * @return Image in appropriate format for the network
   */
  int createNetworkInput(cv::Mat image);

  /**
   * @brief Applies the network for human detection
   *
   * @return Vector of matrices(and a Image) containing detection information
   */
  std::vector<cv::Mat> applyYOLONetwork();
};

#endif    // INCLUDE_NETWORK_HPP_
