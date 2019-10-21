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
 * @file      VisionModuleTest.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Contains Unit Tests for VisionModule class
 */

#include <gtest/gtest.h>
#include "../include/VisionModule.hpp"

/**
 * @brief Test to check gaussian filter function
 *
 * @param none
 *
 * @return none
 */
TEST(VisionModuleTest, TestApplyGaussianFilter) {
  VisionModule vm;
  cv::Mat testImage, testOutput;
  cv::Size testKernelSize(5, 5);
  float testSigma = 0.1;
  testImage = cv::imread("../test/testData/testImage.jpg");
  testOutput = vm.applyGaussianFilter(testImage, testKernelSize, testSigma);

  ASSERT_EQ(testImage.cols, testOutput.cols);
  ASSERT_EQ(testImage.rows, testOutput.rows);
}

/**
 * @brief Test to check mean filter function
 *
 * @param none
 *
 * @return none
 */
TEST(VisionModuleTest, TestApplyMeanFilter) {
  VisionModule vm;
  cv::Mat testImage, testOutput;
  cv::Size testKernelSize(5, 5);
  testImage = cv::imread("../test/testData/testImage.jpg");
  testOutput = vm.applyFilter(testImage, testKernelSize);

  ASSERT_EQ(testImage.cols, testOutput.cols);
  ASSERT_EQ(testImage.rows, testOutput.rows);
}

/**
 * @brief Test to check median filter function
 *
 * @param none
 *
 * @return none
 */
TEST(VisionModuleTest, TestApplyMedianFilter) {
  VisionModule vm;
  cv::Mat testImage, testOutput;
  int testKernelSize = 5;
  testImage = cv::imread("../test/testData/testImage.jpg");
  testOutput = vm.applyMedianFilter(testImage, testKernelSize);

  ASSERT_EQ(testImage.cols, testOutput.cols);
  ASSERT_EQ(testImage.rows, testOutput.rows);
}

/**
 * @brief Test to check image reshape function
 *
 * @param none
 *
 * @return none
 */
TEST(VisionModuleTest, TestReshape) {
  VisionModule vm;
  cv::Mat testImage, testOutput;
  cv::Size dim(500, 500);
  testImage = cv::imread("../test/testData/testImage.jpg");
  testOutput = vm.reshape(testImage, dim);

  ASSERT_EQ(500, testOutput.cols);
  ASSERT_EQ(500, testOutput.rows);
}

/**
 * @brief Test to check non-maximal suppression algorithm
 *
 * @param none
 *
 * @return none
 */
TEST(VisionModuleTest, TestNonMaximalSuppression) {
  VisionModule vm;
  cv::Mat testImage;
  std::vector<cv::Rect> testPredictedBoxes;
  std::vector< std::vector<int> > testFinalBoxes;
  std::vector<float> testConfidenceScores;
  std::vector<int> classIds{0, 0};
  int frameID = 0;
  testPredictedBoxes.push_back(cv::Rect(200, 200, 50, 50));
  testPredictedBoxes.push_back(cv::Rect(200, 200, 260, 240));
  testConfidenceScores.push_back(0.5);
  testConfidenceScores.push_back(0.95);
  testImage = cv::imread("../test/testData/testImage.jpg");
  testFinalBoxes = vm.nonMaximalSuppression(testImage, testPredictedBoxes, \
                    testConfidenceScores, classIds, frameID);

  ASSERT_EQ(1, static_cast<signed>(testFinalBoxes.size()));
  ASSERT_EQ(200, testFinalBoxes[0][1]);
}
