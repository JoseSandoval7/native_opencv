#include "ImageProcessor.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

vector<Mat> ImageProcessor::process_image(Mat &image){
    Mat grayScale;
    Mat filtered;
    Mat negative;
    Mat DM;

    // Get grayscale image
    grayScale = process_grayscale(image);

    // Get filtered image
    filtered = process_filtered(grayScale);

    // Get negative image
    negative = process_negative(grayScale);

    // Get DM
    DM = process_DM(image);

    return {
        grayScale,
        filtered,
        negative,
        DM
    };
}

Mat ImageProcessor::process_filtered(Mat input){
    Mat result;

    Canny(input, result, 50, 150);

    return result;
}

Mat ImageProcessor::process_negative(Mat input){
    Mat result;

    Mat filtered = process_filtered(input);

    bitwise_not(filtered, result);

    return result;
}

Mat ImageProcessor::process_DM(Mat input){
    Mat result;
    Mat negative = process_negative(input);


    // Split image in to RGB
    vector<Mat> channels;

    split(input, channels);

    // Discriminante por multiplicacion
    Mat redChannel = channels[2].mul(negative);
    Mat greenChannel = channels[1].mul(negative);
    Mat blueChannel = channels[0].mul(negative);

    merge(vector<Mat>{blueChannel, greenChannel, redChannel}, result);

    return result;
}

Mat ImageProcessor::process_grayscale(Mat input){
    Mat result;

    cvtColor(input, result, COLOR_BGR2GRAY);

    return result;
}