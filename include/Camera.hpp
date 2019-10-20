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
 * @file      Camera.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares Camera class
 */

#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * @brief Class for storing Camera Information
 */
class Camera {
 public:
  /**
   * @brief Constructor for class
   */
  Camera();

  /**
   * @brief Constructor for class with id and resolution
   *
   * @param id Camera device ID
   * @param res Camera resolution
   */
  Camera(int id, std::pair<int, int> res);

  /**
   * @brief Constructor for class with id, resolution and calibration
   *        matrix
   *
   * @param id Camera device ID
   * @param res Camera resolution
   * @param calibMat Camera Calibration Matrix
   */
  Camera(int id, std::pair<int, int> res, cv::Mat calibMat);

  /** 
   * @brief Destrcutor for class
   */
  ~Camera();

  /**
   * @brief Function to display Camera Information.
   */
  void displayInfo();

  /**
   * @brief Function to check if Camera is active
   *
   * @return Returns true if Camera is active
   */
  bool isActive();

  /**
   * @brief Function to return Camera device ID
   *
   * @return Returns device ID
   */
  int getID();

  /**
   * @brief Function to return Camera calibration matrix
   *
   * @return Returns Camera calibration matrix
   */
  cv::Mat getCalibrationMatrix();

  /**
   * @brief Function to get Camera resolution
   *
   * @return Returns Camera resolution
   */
  std::pair<int, int> getResolution();

 private:
  int cameraID;
  cv::Mat calibrationMatrix;
  std::pair<int,int> resolution;
};

#endif    // INCLUDE_CAMERA_HPP_
