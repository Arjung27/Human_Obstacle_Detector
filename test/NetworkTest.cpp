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
 * @file      NetworkTest.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Contains Unit Tests for Network class
 */

#include <gtest/gtest.h>

#include <Network.hpp>

/**
 * @brief Test to check blob creation
 *
 * @param none
 *
 * @return none
 */
TEST(NetworkTest, TestCreateNetworkInput) {

  Network network;

  cv::Mat testImage1 = cv::imread("../test/testData/testImage.jpg");
  cv::Mat testImage2 = cv::imread("../test/testData/notTestImage.jpg");
  int testFlag1 = network.createNetworkInput(testImage1);
  int testFlag2 = network.createNetworkInput(testImage2);

  ASSERT_EQ(1, testFlag1);
  ASSERT_EQ(0, testFlag2);
}

/**
 * @brief Test to check network execution
 *
 * @param none
 *
 * @return none
 */
TEST(NetworkTest, TestApplyYOLONetwork) {

  Network network;

  cv::Mat testImage = cv::imread("../test/testData/testImage.jpg");
  int testFlag = network.createNetworkInput(testImage);
  std::vector<cv::Mat> testDetections = network.applyYOLONetwork();

  ASSERT_GE(testDetections.size(), 1);
}