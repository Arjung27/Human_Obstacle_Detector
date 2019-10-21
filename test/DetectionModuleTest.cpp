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
 * @file      DetectionModuleTest.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Contains Unit Tests for DetectionModule class
 */

#include <gtest/gtest.h>

#include <DetectionModule.hpp>

/**
 * @brief Test to check get frame function, that executes main
 *        detection functionality
 *
 * @param none
 *
 * @return none
 */
TEST(DetectionModuleTest, TestGetFrame) {
  DetectionModule dm;
  std::string testFilePath1 = "../test/testData/testImage.jpg";
  std::string testFilePath2 = "../test/testData/notTestImage.jpg";
  std::string testFilePath3 = "../test/testData/testVideo.avi";
  std::string testOutputDirectory = "../test/testResults/";
  int testCameraID = -1;

  ASSERT_EQ(1, dm.getFrame(testFilePath1, testCameraID, \
                            testOutputDirectory, 1));
  ASSERT_EQ(1, dm.getFrame(testFilePath3, testCameraID, \
                            testOutputDirectory, 2));

  ASSERT_EQ(0, dm.getFrame(testFilePath2, testCameraID, \
                            testOutputDirectory, 1));
  ASSERT_EQ(0, dm.getFrame(testFilePath2, testCameraID, \
                            testOutputDirectory, 2));

  ASSERT_EQ(0, dm.getFrame(testFilePath1, testCameraID, \
                            testOutputDirectory, 3));

  cv::Mat testImage = cv::imread("../test/testData/testImage.jpg");
  cv::Mat testOutput = cv::imread("../test/testResults/testImageDetection.jpg");

  ASSERT_EQ(416, testOutput.cols);
  ASSERT_EQ(416, testOutput.rows);
}

/**
 * @brief Test to check pre processing steps
 *
 * @param none
 *
 * @return none
 */
TEST(DetectionModuleTest, TestPreProcessImage) {
  DetectionModule dm;

  cv::Mat testImage = cv::imread("../test/testData/testImage.jpg");
  cv::Mat testOutput = dm.preProcessImage(testImage, 'G');

  ASSERT_EQ(416, testOutput.cols);
  ASSERT_EQ(416, testOutput.rows);

  testOutput = dm.preProcessImage(testImage, 'B');

  ASSERT_EQ(416, testOutput.cols);
  ASSERT_EQ(416, testOutput.rows);

  testOutput = dm.preProcessImage(testImage, 'M');

  ASSERT_EQ(416, testOutput.cols);
  ASSERT_EQ(416, testOutput.rows);
}

/**
 * @brief Test to check network execution
 *
 * @param none
 *
 * @return none
 */
TEST(DetectionModuleTest, TestDetectObjects) {
  DetectionModule dm;

  cv::Mat testImage = cv::imread("../test/testData/testImage.jpg");

  ASSERT_EQ(1, dm.detectObjects(testImage));
}

/**
 * @brief Test to check post processing steps
 *
 * @param none
 *
 * @return none
 */
TEST(DetectionModuleTest, TestPostProcessImage) {
  DetectionModule dm;
  int testFrameID = 0;

  cv::Mat testImage = cv::imread("../test/testData/testImage.jpg");
  cv::Mat testOutput = dm.postProcessImage(testImage, testFrameID);

  ASSERT_EQ(testImage.cols, testOutput.cols);
  ASSERT_EQ(testImage.rows, testOutput.rows);
}

