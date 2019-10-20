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
 * @file      VisionModule.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares VisionModule base class for DetectionModule class
 */

#ifndef INCLUDE_VISIONMODULE_HPP_
#define INCLUDE_VISIONMODULE_HPP_

#include <iostream>
#include <vector>
#include <utility>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/**
 * @brief Class for Vision based functionality
 */
class VisionModule {
 public :
  /**
   * @brief Constructor for class
   */
  VisionModule();

  /** 
   * @brief Destrcutor for class
   */
  virtual ~VisionModule();

  /**
   * @brief Applies Gaussian Filter to given image.
   *
   * The kernel is assumed to be a square matrix with
   * equal sigma in both x and y directions
   *
   * @param image Image on which the filter will be applied
   * @param kernelDim Size of kernel matrix
   * @param sigma Standard deviation for the Gaussian kernel
   *
   * @return Image after applying filter
   */
  virtual cv::Mat applyGaussianFilter(cv::Mat image,
      int kernelDim, float sigma);

  /**
   * @brief Applies Mean Filter to given image.
   *
   * @param image Image on which the filter will be applied
   * @param kernelDim Size of kernel matrix
   *
   * @return Image after applying filter
   */
  virtual cv::Mat applyMeanFilter(cv::Mat image, int kernelDim);

  /**
   * @brief Applies Median Filter to given image.
   *
   * @param image Image on which the filter will be applied
   * @param kernelDim Size of kernel matrix
   *
   * @return Image after applying filter
   */
  virtual cv::Mat applyMedianFilter(cv::Mat image, int kernelDim);

  /**
   * @brief Reshapes given image to given dimension
   *
   * @param image Image to be reshaped
   * @param shape Pair of ints giving the Dimension the image
   *              has to be rehsaped to 
   *
   * @return Image after reshaping it
   */
  virtual cv::Mat reshape(cv::Mat image, std::pair<int, int> dim);

  /**
   * @brief Applies Non Maximal Suppression Algorithm
   *
   * Given a set of bounding boxes of detected objects in an
   * image, the algorithm removes overlapping boxes that may be
   * enclosing the same object.
   *
   * @param image Image on which the objects have been detected
   * @param boxes Vector of vectors of float, contains information
   *              of all the bounding boxes detected. In order, the
   *              information comprises of, frame no., object no.,
   *              center, upper left and bottom right points of the box,
   *              confidence level of enclosing the object.
   *
   * @return Modified Vector of bounding box information
   */
  virtual std::vector<std::vector<float>> nonMaximalSuppression(
      cv::Mat image, std::vector<std::vector<float>>);
};
#endif    // INCLUDE_VISIONMODULE_HPP_
