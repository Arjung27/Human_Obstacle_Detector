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
 * @file      Transformation.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Definition for Transformation class
 */

#include <iostream>

#include "Transformation.hpp"

/**
 * @brief Constructor for class
 *
 * Initializes base and end frames as identity matrices
 */
Transformation :: Transformation() {
  endFrame = cv::Mat::eye(4, 4, CV_32F);
  baseFrame = cv::Mat::eye(4, 4, CV_32F);
}

/**
 * @brief Constructor for class with base and end frame input
 *
 * @param base Base Frame
 * @param end End effector Frame
 */
Transformation :: Transformation(cv::Mat base, cv::Mat end) {
  endFrame = end;
  baseFrame = base;
}

/** 
 * @brief Destrcutor for class
 */
Transformation :: ~Transformation() {
}

/**
 * @brief Function to convert vector in base frame to end frame
 *
 * @param vec Vector in base frame coordinates
 *
 * @return Vector in end frame coordinates
 */
auto Transformation :: baseToEnd(cv::Mat vec) -> cv::Mat {
  if (vec.cols == 1 && vec.rows == 4) {
    cv::Mat Rend = endFrame(cv::Rect(0, 0, 3, 3));
    cv::Mat Tend = endFrame(cv::Rect(3, 0, 1, 3));
    cv::Mat RInvend = Rend.inv();
    cv::Mat TInvend = - RInvend * Tend;
    cv::Mat endInv = cv::Mat::eye(4, 4, CV_32F);
    RInvend.copyTo(endInv(cv::Rect(0, 0, 3, 3)));
    TInvend.copyTo(endInv(cv::Rect(3, 0, 1, 3)));

    cv::Mat tf = endInv * baseFrame;
    return tf * vec;
  } else {
    return cv::Mat::zeros(4, 1, CV_32F);
  }
}

/**
 * @brief Function to convert vector in end frame to base frame
 *
 * @param vec Vector in end frame coordinates
 *
 * @return Vector in base frame coordinates
 */
auto Transformation :: endToBase(cv::Mat vec) -> cv::Mat {
  if (vec.cols == 1 && vec.rows == 4) {
    cv::Mat Rbase = baseFrame(cv::Rect(0, 0, 3, 3));
    cv::Mat Tbase = baseFrame(cv::Rect(3, 0, 1, 3));
    cv::Mat RInvbase = Rbase.inv();
    cv::Mat TInvbase = - RInvbase * Tbase;
    cv::Mat baseInv = cv::Mat::eye(4, 4, CV_32F);
    RInvbase.copyTo(baseInv(cv::Rect(0, 0, 3, 3)));
    TInvbase.copyTo(baseInv(cv::Rect(3, 0, 1, 3)));
    cv::Mat tf = baseInv * endFrame;
    return tf * vec;
  } else {
    return cv::Mat::zeros(4, 1, CV_32F);
  }
}

/**
 * @brief Function to convert image coordinates to Camera coordinates
 *
 * @param vec Vector in end frame coordinates
 *
 * @return Vector in base frame coordinates
 */
auto Transformation :: imageToCamera(cv::Mat intrinsic, \
                          cv::Mat vecImage2d) -> cv::Mat {
  if (vecImage2d.cols == 1 && vecImage2d.rows == 2) {
  	/* vector in Image coordinates */
  	cv::Mat vecImage3d = cv::Mat::ones(3, 1, CV_32F);
  	vecImage2d.copyTo(vecImage3d(cv::Rect(0,0,1,2)));

  	/* Inverse of Intrinsic Camera marameter matrix */
  	cv::Mat invIntrinsic = intrinsic.inv();

  	/* 3d Normalized vector in Camera coordinates */
  	cv::Mat vecCamera3d = invIntrinsic * vecImage3d;
  	vecCamera3d = vecCamera3d / vecCamera3d.at<float>(2,0);

  	/* 4d vector of point in camera frame */
  	cv::Mat vecCamera4d = cv::Mat::ones(4, 1, CV_32F);
  	vecCamera3d.copyTo(vecCamera4d(cv::Rect(0,0,1,3)));

    return vecCamera4d;
  } else {
    return cv::Mat::zeros(4, 1, CV_32F);
  }
}

/**
 * @brief Function to convert Camera coordinates to image coordinates
 *
 * @param vec Vector in end frame coordinates
 *
 * @return Vector in base frame coordinates
 */
auto Transformation :: cameraToImage(cv::Mat intrinsic, \
                                cv::Mat vecCamera4d) -> cv::Mat {
  if (vecCamera4d.cols == 1 && vecCamera4d.rows == 4) {
  	/* 3d vector in Camera coordinates */
  	cv::Mat vecCamera3d = vecCamera4d(cv::Rect(0,0,1,3));

  	/* Normalized vector in Image coordinates */
  	cv::Mat vecImage3d = intrinsic * vecCamera3d;
  	vecImage3d = vecImage3d / vecImage3d.at<float>(2,0);

  	/* 2d vector of point in Image coordinates */
  	cv::Mat vecImage2d = vecImage3d(cv::Rect(0,0,1,2));

    return vecImage2d;
  } else {
    return cv::Mat::zeros(2, 1, CV_32F);
  }
}

/**
 * @brief Function to return base frame
 *
 * @return Base frame
 */
auto Transformation :: getBaseFrame() -> cv::Mat {
  return baseFrame;
}

/**
 * @brief Function to return end frame
 *
 * @return End frame
 */
auto Transformation :: getEndFrame() -> cv::Mat {
  return endFrame;
}
