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
 * @file      IOHandler.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Definition for IOHandler class 
 */

#include <iostream>

#include "IOHandler.hpp"

IOHandler::IOHandler() : inputStream(std::cin),
    outputStream(std::cout) {}
IOHandler::IOHandler(std::istream& input, std::ostream& output) :
    inputStream(input), outputStream(output) {}
IOHandler::~IOHandler() {
}

auto IOHandler::getInputChoice() -> int {
  outputStream << "Please choose the type of input from options below: " \
                                                      << std::endl;
  outputStream << "1. Image" << std::endl;
  outputStream << "2. Video" << std::endl;
  outputStream << "3. Camera" << std::endl;
  outputStream << "Enter your choice: " << std::flush;
  int userChoice;
  inputStream >> userChoice;
  int flag = 1;
  /** Loop to enforce that user choose one of the provided options*/
  while (flag == 1) {
    if (userChoice == 1 || userChoice == 2 || userChoice == 3) {
      flag = 0;
      return userChoice;
    } else {
      outputStream << "Incorrect Entry! Choose an option out " \
                                << "of 1,2,3: " << std::flush;
      inputStream >> userChoice;
    }
  }
  return userChoice;
}

auto IOHandler::getInputFilePath() -> std::string {
  std::string pathOfFile;
  int flag = 1;
  /** Loop to check that the path given by the user is correct or not */
  while (flag == 1) {
    outputStream << "Enter the path of the file: " << std::flush;
    inputStream >> pathOfFile;
    std::ifstream ifs(pathOfFile);
    if (!ifs.is_open()) {
      outputStream << "File path is incorrect!" << std :: endl;
      } else {
      flag = 0;
      }
    }
  return pathOfFile;
}

auto IOHandler::getDeviceID() -> int {
  outputStream << "Enter the camera ID: " << std::flush;
  int inputCameraID;
  inputStream >> inputCameraID;
  this->cameraID = inputCameraID;
  return inputCameraID;
}

auto IOHandler::getOutputFilePath() -> std::string {
  outputStream << "Enter output directory to store results: " << std::flush;
  std::string directoryPath;
  inputStream >> directoryPath;
  return directoryPath;
}

auto IOHandler::saveOutput(std::vector< std::vector<int> > finalDetections, \
                            std::string outputDirectory) -> void {
  std::ofstream textFile;
  /* Name appended to the outputDirectory */
  textFile.open(outputDirectory + "DetectionsFile.txt");
  int counter = 0;
  /* Loop to check write the detections in the desired directory. Also
  checks if the textfile path exists or not */
  if (textFile) {
    for (auto detections : finalDetections) {
      textFile << "FrameID: " << std::to_string(detections[0]) << " " \
        << "ObjectID: " << std::to_string(counter) << " Box_Coordinates: " \
        << std::to_string(detections[1]) << " " \
        << std::to_string(detections[2]) << " " \
        << std::to_string(detections[3]) << " " \
        << std::to_string(detections[4]) << "\n";
      counter += 1;
    }
    textFile.close();
    std::cout << "Thank you for using the Human Detection Module." \
      << " Your outputs are stored in " << outputDirectory << std::endl;
  } else {
    std::cout << "Can't find the output directory!" << std::endl;
  }
}
