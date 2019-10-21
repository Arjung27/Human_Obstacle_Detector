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
 * @file      Network.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Definition for Network class
 */

#include <iostream>
#include "../include/Network.hpp"

Network::Network() {
}

Network::~Network() {
}

auto Network::createNetworkInput(cv::Mat image) -> int {
    /* Checks if the given image is valid or not */
    if (!image.data) {
      return 0;
    } else {
      /* Make a blob for the input to the network */
      blob = cv::dnn::blobFromImage(image, 1/255.0, \
      cv::Size(imageWidth, imageHeight), \
      cv::Scalar(0, 0, 0), true, false);
      return 1;
    }
}

auto Network::applyYOLONetwork() -> std::vector<cv::Mat> {
    std::vector<cv::Mat> detectedObjects;
    /* Store the path of configuration and weight files */
    configurationFilePath = "../modelFiles/yolov3.cfg";
    weightsFilePath = "../modelFiles/yolov3.weights";
    /* Load the weights and the config file to the Network */
    yoloNetwork = cv::dnn::readNetFromDarknet(\
            configurationFilePath, weightsFilePath);
    /* Set backend type for the network */
    yoloNetwork.setPreferableBackend(cv::dnn::DNN_BACKEND_DEFAULT);
    /* Set the target processor */
    yoloNetwork.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);
    /* Pass the input to the network */
    yoloNetwork.setInput(blob);
    std::vector<int> outLayers{yoloNetwork.getUnconnectedOutLayers()};
    std::vector<cv::String> outLayerNames{yoloNetwork.getLayerNames()};
    std::vector<cv::String> outLayerNamesCopy;
    /* Make a copy of names of the layers */
    outLayerNamesCopy.resize(outLayerNames.size());
    int i = 0;
    for (auto names : outLayers) {
        outLayerNamesCopy[i] = outLayerNames[names - 1];
        i++;
    }
    /* Forward pass of the network */
    yoloNetwork.forward(detectedObjects, outLayerNamesCopy);
    return detectedObjects;
}
