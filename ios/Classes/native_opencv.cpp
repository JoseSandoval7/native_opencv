
#include <opencv2/opencv.hpp>
#include "ImageProcessor.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

// Avoiding name mangling
extern "C" {
    // Attributes to prevent 'unused' function from being removed and to make it visible
    __attribute__((visibility("default"))) __attribute__((used))
    const char* version() {
        return CV_VERSION;
    }

    __attribute__((visibility("default"))) __attribute__((used))
    int processing(int height, int width, char* inputImage, unsigned char *grayScale, unsigned char *filtered, unsigned char *negative, unsigned char *DM) {        
        // Creating image from pointer
        Mat input = imread(inputImage, IMREAD_COLOR);

        if(!input.data){
            return -1;
        }

        vector<uchar> buffer, buffer2, buffer3, buffer4;

        vector<Mat> result = ImageProcessor::process_image(input);

        imencode(".jpg", result[3], buffer4);
        copy(buffer4.begin(), buffer4.end(), DM);

        imencode(".jpg", result[2], buffer3);
        copy(buffer3.begin(), buffer3.end(), negative);

        imencode(".jpg", result[1], buffer2);
        copy(buffer2.begin(), buffer2.end(), filtered); 

        imencode(".jpg", result[0], buffer);
        copy(buffer.begin(), buffer.end(), grayScale);

        return 0;
    }
}