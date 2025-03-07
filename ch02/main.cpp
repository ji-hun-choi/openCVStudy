#include <iostream>
#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;
int main() {
    cout << "Hello, CV!" << CV_VERSION << endl;

    Mat img;
    img = imread("../images/lena.jpg");

    if (img.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    namedWindow("image");
    imshow("image", img);

    waitKey();

    return 0;
}
