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
 * @file      VisionModule.cpp
 * @author    Rohan Singh
 * @author    Arjun Gupta
 * @copyright MIT License (c) 2019 Rohan Singh, Arjun Gupta
 * @brief     Definition for VisionModule class
 */

#include <iostream>

#include "VisionModule.hpp"

VisionModule::VisionModule() {
}

VisionModule::~VisionModule() {
}

auto VisionModule::applyGaussianFilter(cv::Mat image, cv::Size kernelDim, \
                                                float sigma) -> cv::Mat {
    cv::Mat smoothenImage;
    /* Gaussian filter to remove noise */
    cv::GaussianBlur(image, smoothenImage, cv::Size(kernelDim), sigma, sigma);
    return smoothenImage;
}

auto VisionModule::applyFilter(cv::Mat image, \
                                cv::Size kernelDim) -> cv::Mat {
    cv::Mat smoothenImage;
    /* Standard/Mean filter to remove noise */
    cv::blur(image, smoothenImage, cv::Size(kernelDim), cv::Point(-1, -1));
    return smoothenImage;
}

auto VisionModule::applyMedianFilter(cv::Mat image, \
                    int kernelDim) -> cv::Mat {
    cv::Mat smoothenImage;
    /* Median filter to remove noise */
    cv::medianBlur(image, smoothenImage, kernelDim);
    return smoothenImage;
}

auto VisionModule::reshape(cv::Mat image, \
                                cv::Size size) -> cv::Mat {
    cv::Mat resizedImage;
    /* Reshapes images to the desired size without cropping */
    cv::resize(image, resizedImage, size, 0.0, 0.0);
    return resizedImage;
}

std::vector< std::vector<int> > VisionModule::nonMaximalSuppression(\
        cv::Mat& frame, std::vector<cv::Rect>& predictedBoxes, \
        std::vector<float> confidenceScores, std::vector<int> classIds, \
        int frameID) {
    std::vector< std::vector<int> > finalDetections;
    std::vector<int> indexes;
    /* Non Maximal Suppression Algorithm that removes the bounding boxes
    with significant overlap */
    cv::dnn::NMSBoxes(predictedBoxes, confidenceScores, \
    this->confidenceThreshold, this->nmsThreshold, indexes);
    for (auto index : indexes) {
        if (classIds[index] == 0) {
            cv::Rect rectangle_ = predictedBoxes[index];
            /* Calculating bottom right corner coordinates using the width,
            height and top left corner's information */
            int bottomRightX = rectangle_.x + rectangle_.width;
            if (bottomRightX > 416) bottomRightX = 416;
            int bottomRightY = rectangle_.y + rectangle_.height;
            if (bottomRightY > 416) bottomRightY = 416;
            /* Drawing rectangles on the image */
            cv::rectangle(frame, cv::Point(rectangle_.x, rectangle_.y), \
            cv::Point(bottomRightX, bottomRightY), cv::Scalar(0, 170, 50), 3);
            std::vector<int> temp{frameID, rectangle_.x, rectangle_.y, \
                        bottomRightX, bottomRightY};
            finalDetections.push_back(temp);

        }
    }
    return finalDetections;
}
