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
 * @file      Transformation.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares Transformation class
 */

#ifndef INCLUDE_TRANSFORMATION_HPP_
#define INCLUDE_TRANSFORMATION_HPP_

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * @brief Class for implementing Frame transformations
 */
class Transformation {
 public:
  /**
   * @brief Constructor for class
   *
   * Initializes base and end frames as identity matrices
   */
  Transformation();

  /**
   * @brief Constructor for class with base and end frame input
   *
   * @param base Base Frame
   * @param end End effector Frame
   */
  Transformation(cv::Mat base, cv::Mat end);

  /** 
   * @brief Destrcutor for class
   */
  ~Transformation();

  /**
   * @brief Function to convert vector in base frame to end frame
   *
   * @param vec Vector in base frame coordinates
   *
   * @return Vector in end frame coordinates
   */
  cv::Mat baseToEnd(cv::Mat vec);

  /**
   * @brief Function to convert vector in end frame to base frame
   *
   * @param vec Vector in end frame coordinates
   *
   * @return Vector in base frame coordinates
   */
  cv::Mat endToBase(cv::Mat vec);

  /**
   * @brief Function to convert image coordinates to Camera coordinates
   *
   * @param vec Vector in end frame coordinates
   *
   * @return Vector in base frame coordinates
   */
  cv::Mat imageToCamera(cv::Mat intrinsic, cv::Mat vecImage2d);

  /**
   * @brief Function to convert Camera coordinates to image coordinates
   *
   * @param vec Vector in end frame coordinates
   *
   * @return Vector in base frame coordinates
   */
  cv::Mat cameraToImage(cv::Mat intrinsic, cv::Mat vecCamera4d);

  /**
   * @brief Function to return base frame
   *
   * @return Base frame
   */
  cv::Mat getBaseFrame();

  /**
   * @brief Function to return end frame
   *
   * @return End frame
   */
  cv::Mat getEndFrame();

 private:
  /* Base frame transformation matrix in Global Coordinate Frame */
  cv::Mat baseFrame;

  /* End frame transformation matrix in Global Coordinate Frame */
  cv::Mat endFrame;
};
#endif    // INCLUDE_TRANSFORMATION_HPP_
