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
 * @file      IOHandler.hpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Declares IOHandler class
 */

#ifndef INCLUDE_IOHANDLER_HPP_
#define INCLUDE_IOHANDLER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
class IOHandler {
 private:
    int inputChoice;
    std::string filePath;
    int cameraID;
    std::string outputDirectory;
    cv::Mat image;
    cv::VideoCapture video;
    std::istream& inputStream;
    std::ostream& outputStream;

 public:
    IOHandler();
    IOHandler(std::istream& input, std::ostream& output);
    ~IOHandler();
    int getInputChoice();
    std::string getInputFilePath();
    int getDeviceID();
    std::string getOutputFilePath();
    void saveOutput(std::vector< std::vector<int> > finalDetections, \
    std::string outputDirectory);
};
#endif    // INCLUDE_IOHANDLER_HPP_
