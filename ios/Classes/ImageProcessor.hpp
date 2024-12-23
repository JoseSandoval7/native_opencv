#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class ImageProcessor {
    private:
        static Mat process_grayscale(Mat image);
        static Mat process_DM(Mat image);
        static Mat process_filtered(Mat image);
        static Mat process_negative(Mat image);

    public:
        static vector<Mat> process_image(Mat& image);
};