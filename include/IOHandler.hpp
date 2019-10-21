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
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
/**
 * @brief Class to manage the input output functionality of the module
 */
class IOHandler {
 private:
  /* Input choice of the user */
  int inputChoice = 1;
  /* Input file's path */
  std::string filePath;
  /* CameraID if camera is the source of input */
  int cameraID = 0;
  /* Output directory path to store the results */
  std::string outputDirectory;
  /* Image that is being processed */
  cv::Mat image;
  /* Object of VideoCapture to parse video frames */
  cv::VideoCapture video;
  /* Manages the input data */
  std::istream& inputStream;
  /* Manages the output data */
  std::ostream& outputStream;

 public:
  /**
   * @brief Default constructor
   */
  IOHandler();
  /**
   * @brief Parametric constructor
   * 
   * @param input the input entered by the user
   * @param output the information to be output by the module
   */
  IOHandler(std::istream& input, std::ostream& output);
  /**
   * @brief Default Destructor
   */
  ~IOHandler();
  /**
   * @brief Takes the input from the user
   * 
   * Takes the input of the options from the user and also checks whether the
   * input is valid or not
   * 
   * @return the integer entered by the user as a choice
   */
  int getInputChoice();
  /**
   * @brief Takes the input file path from the user
   * 
   * Also checks whether the file mentioned exists or not
   * 
   * @return path of the input file as entered by the user
   */
  std::string getInputFilePath();
  /**
   * @brief Takes the device ID if the input is taken using camera
   * 
   * @return the ID of the device
   */
  int getDeviceID();
  /**
   * @brief Gets the path of the output directory to story detections and
   *    and text files.
   * @return path of the directory where the results will be stored
   */
  std::string getOutputFilePath();
  /**
   * @brief Saves the text file in the output directory
   * 
   * @param finalDetections Vector of vectors to store the final detections
   *                    after the complete preprocessing
   * @param outputDirectory the path of the directory to store the results
   * 
   * @return void
   */
  void saveOutput(std::vector< std::vector<int> > finalDetections, \
  std::string outputDirectory);
};
#endif    // INCLUDE_IOHANDLER_HPP_
