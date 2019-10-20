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
 * @file      IOHandlerTest.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Contains Unit Tests for IOHandler class
 */

#include <gtest/gtest.h>
#include <sstream>

#include "../include/IOHandler.hpp"

TEST(IOHandler, TestGetInputChoice) {

  std::istringstream mockInputBuffer1("1");
  std::ostringstream mockOutputBuffer;
  IOHandler io1(mockInputBuffer1, mockOutputBuffer);

  std::istringstream mockInputBuffer2("2");
  IOHandler io2(mockInputBuffer2, mockOutputBuffer);

  std::istringstream mockInputBuffer3("3");
  IOHandler io3(mockInputBuffer3, mockOutputBuffer);

  std::istringstream mockInputBuffer4("4 1");
  IOHandler io4(mockInputBuffer4, mockOutputBuffer);

  ASSERT_EQ(1, io1.getInputChoice());
  ASSERT_EQ(2, io2.getInputChoice());
  ASSERT_EQ(3, io3.getInputChoice());
  ASSERT_EQ(1, io4.getInputChoice());
}

TEST(IOHandler, TestGetInputFilePath) {

  std::string testString1 = "/home/arjun/Courseworks/Projects/ENPM808X/HODM/test/testData/testImage.jpg";
  std::string testString2 = "../test/testData/notTestImage.jpg";
  testString2 = testString2 + " " + testString1;
  std::istringstream mockInputBuffer1(testString1);
  std::ostringstream mockOutputBuffer;
  IOHandler io1(mockInputBuffer1, mockOutputBuffer);

  std::istringstream mockInputBuffer2(testString1);
  IOHandler io2(mockInputBuffer2, mockOutputBuffer);

  ASSERT_EQ(testString1, io1.getInputFilePath());
  ASSERT_EQ(testString1, io2.getInputFilePath());
}

TEST(IOHandler, TestGetDeviceID) {

  std::istringstream mockInputBuffer("1");
  std::ostringstream mockOutputBuffer;
  IOHandler io(mockInputBuffer, mockOutputBuffer);

  ASSERT_EQ(1, io.getDeviceID());
}

TEST(IOHandler, TestGetOutputFilePath) {

  std::istringstream mockInputBuffer("output/");
  std::ostringstream mockOutputBuffer;
  IOHandler io(mockInputBuffer, mockOutputBuffer);

  ASSERT_EQ("output/", io.getOutputFilePath());
}