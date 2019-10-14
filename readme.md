# Human Obstacle Detection Module
[![Build Status](https://travis-ci.org/rohansingh42/HODM.svg?branch=master)](https://travis-ci.org/rohansingh42/HODM)
[![Coverage Status](https://coveralls.io/repos/github/rohansingh42/HODM/badge.svg?branch=master)](https://coveralls.io/github/rohansingh42/HODM?branch=master)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
---

## Overview

This repository contains the implementation of the Human Obstacle Detection module. The human obstacle detector module can take the image/video as input and output the localization of the detected humans in the robot’s reference frame. The output of the module contains the bottom left corner, the top right corner and the center of the bounding box (that contains the human), and a confidence value of detection. This module can be further integrated with a task-specific control module (such as path planning module) which utilizes the detection information.

## Product Backlog 
[![Packagist](https://img.shields.io/badge/AIP-Backlog-orange)](https://docs.google.com/spreadsheets/d/1Du2DV9m7JFUn_xO6RULXBDN6mna-3IR8e5ZURudZHeg/edit?usp=sharing)

The Agile Iterative Process was followed for the development of the software. Follow this Google Sheets [link](https://docs.google.com/spreadsheets/d/1Du2DV9m7JFUn_xO6RULXBDN6mna-3IR8e5ZURudZHeg/edit?usp=sharing) to view the product backlog and sprint schedules.

## License

```
MIT License

Copyright (c) 2019 Rohan Singh, Arjun Gupta

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```