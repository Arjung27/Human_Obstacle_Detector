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
 * @file      TransformationTest.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Contains Unit Tests for Transformation class
 */

#include <gtest/gtest.h>

#include "../include/Transformation.hpp"

/**
 * @brief Test to check Base frame to End frame transformation
 *
 * @param none
 *
 * @return none
 */
TEST(TransformationTest, TestBaseToEnd) {
  cv::Mat testEnd = cv::Mat::zeros(4, 4, CV_32F);
  testEnd.at<float>(0, 1) = -1.0;
  testEnd.at<float>(1, 0) = 1.0;
  testEnd.at<float>(2, 2) = 1.0;
  testEnd.at<float>(3, 3) = 1.0;

  /* tf object initialized with identity base frame */
  Transformation tf(cv::Mat::eye(4, 4, CV_32F), testEnd);
  cv::Mat testVector1 = cv::Mat::ones(4, 1, CV_32F);
  cv::Mat testVector2 = cv::Mat::ones(3, 1, CV_32F);

  cv::Mat testOutput1 = tf.baseToEnd(testVector1);
  cv::Mat testOutput2 = tf.baseToEnd(testVector2);

  EXPECT_NEAR(1.0, testOutput1.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(-1.0, testOutput1.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(3, 0), 0.0001);

  EXPECT_NEAR(0.0, testOutput2.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(3, 0), 0.0001);
}

/**
 * @brief Test to check End frame to Base frame transformation
 *
 * @param none
 *
 * @return none
 */
TEST(TransformationTest, TestEndToBase) {
  cv::Mat testEnd = cv::Mat::zeros(4, 4, CV_32F);
  testEnd.at<float>(0, 1) = -1.0;
  testEnd.at<float>(1, 0) = 1.0;
  testEnd.at<float>(2, 2) = 1.0;
  testEnd.at<float>(3, 3) = 1.0;

  /* tf object initialized with identity base frame */
  Transformation tf(cv::Mat::eye(4, 4, CV_32F), testEnd);
  cv::Mat testVector1 = cv::Mat::ones(4, 1, CV_32F);
  cv::Mat testVector2 = cv::Mat::ones(3, 1, CV_32F);

  cv::Mat testOutput1 = tf.endToBase(testVector1);
  cv::Mat testOutput2 = tf.endToBase(testVector2);

  EXPECT_NEAR(-1.0, testOutput1.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(3, 0), 0.0001);

  EXPECT_NEAR(0.0, testOutput2.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(3, 0), 0.0001);
}

/**
 * @brief Test to check End frame to Base frame transformation
 *
 * @param none
 *
 * @return none
 */
TEST(TransformationTest, TestImageToCamera) {
  /* tf object initialized with identity base and end frame */
  Transformation tf;

  cv::Mat testVector1 = cv::Mat::ones(2, 1, CV_32F);
  testVector1.at<float>(1, 0) = 2.0;
  cv::Mat testVector2 = cv::Mat::ones(1, 1, CV_32F);

  /* Identity intrinsic camera matrix */
  cv::Mat testIntrinsic = cv::Mat::eye(3, 3, CV_32F);

  cv::Mat testOutput1 = tf.imageToCamera(testIntrinsic, testVector1);
  cv::Mat testOutput2 = tf.imageToCamera(testIntrinsic, testVector2);

  EXPECT_NEAR(1.0, testOutput1.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(2.0, testOutput1.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(1.0, testOutput1.at<float>(3, 0), 0.0001);

  EXPECT_NEAR(0.0, testOutput2.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(1, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(2, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(3, 0), 0.0001);
}

/**
 * @brief Test to check End frame to Base frame transformation
 *
 * @param none
 *
 * @return none
 */
TEST(TransformationTest, TestCameraToImage) {
  /* tf object initialized with identity base and end frame */
  Transformation tf;

  cv::Mat testVector1 = cv::Mat::ones(4, 1, CV_32F);
  testVector1.at<float>(1, 0) = 2.0;
  cv::Mat testVector2 = cv::Mat::ones(2, 1, CV_32F);

  /* Identity intrinsic camera matrix */
  cv::Mat testIntrinsic = cv::Mat::eye(3, 3, CV_32F);

  cv::Mat testOutput1 = tf.cameraToImage(testIntrinsic, testVector1);
  cv::Mat testOutput2 = tf.cameraToImage(testIntrinsic, testVector2);

  EXPECT_NEAR(1.0, testOutput1.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(2.0, testOutput1.at<float>(1, 0), 0.0001);

  EXPECT_NEAR(0.0, testOutput2.at<float>(0, 0), 0.0001);
  EXPECT_NEAR(0.0, testOutput2.at<float>(1, 0), 0.0001);
}

/**
 * @brief Test to check get functions
 *
 * @param none
 *
 * @return none
 */
TEST(TransformationTest, TestGetFunctions) {
  /* tf object initialized with identity base and end frame */
  Transformation tf;

  cv::Mat testEnd = tf.getEndFrame();
  cv::Mat testBase = tf.getBaseFrame();

  ASSERT_EQ(4, testEnd.cols);
  ASSERT_EQ(4, testEnd.rows);

  ASSERT_EQ(4, testBase.cols);
  ASSERT_EQ(4, testBase.rows);
}
