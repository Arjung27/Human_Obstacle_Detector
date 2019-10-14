set(GTEST_SHUFFLE 1)

add_executable(
    cpp-test
    main.cpp
    VisionModuleTest.cpp
    DetectionModuleTest.cpp
    CameraTest.cpp
    NetworkTest.cpp
    TransformationTest.cpp
    IOHandlerTest.cpp
    ../app/VisionModule.cpp
    ../app/DetectionModule.cpp
    ../app/Camera.cpp
    ../app/Network.cpp
    ../app/Transformation.cpp
    ../app/IOHandler.cpp)
)

target_include_directories(cpp-test PUBLIC ../vendor/googletest/googletest/include 
                                           ../vendor/googletest/googlemock/include
                                           ${CMAKE_SOURCE_DIR}/include ${OpenCV_INCLUDE_DIRS})
target_link_libraries(cpp-test PUBLIC gtest ${OpenCV_LIBS})