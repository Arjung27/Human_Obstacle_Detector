add_executable(hodm-app main.cpp 
						 VisionModule.cpp
						 DetectionModule.cpp
						 Network.cpp
						 Transformation.cpp
						 IOHandler.cpp)
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries( hodm-app ${OpenCV_LIBS}
)
