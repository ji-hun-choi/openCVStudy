#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace cv::ml;
using namespace std;

Ptr<KNearest> train_knn();
void on_mouse(int event, int x, int y, int flags, void* userdata);

int main()
{
    Ptr<KNearest> knn = train_knn();

    if (knn.empty()) {
        cerr << "Training failed!" << endl;
        return -1;
    }

    Mat img = Mat::zeros(400, 400, CV_8U);

    imshow("img", img);
    setMouseCallback("img", on_mouse, (void*)&img);

    while (true) {
        int c = waitKey();

        if (c == 27) {
            break;
        } else if (c == ' ') {
            Mat img_resize, img_float, img_flatten, res;

            resize(img, img_resize, Size(20, 20), 0, 0, INTER_AREA);
            img_resize.convertTo(img_float, CV_32F);
            img_flatten = img_float.reshape(1, 1);

            knn->findNearest(img_flatten, 3, res);
            cout << cvRound(res.at<float>(0, 0)) << endl;

            img.setTo(0);
            imshow("img", img);
        }
    }

    return 0;
}

Ptr<KNearest> train_knn()
{
    Mat digits = imread("images/digits.png", IMREAD_GRAYSCALE);

    if (digits.empty()) {
        cerr << "Image load failed!" << endl;
        return 0;
    }

    Mat train_images, train_labels;

    for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 100; i++) {
            Mat roi, roi_float, roi_flatten;
            roi = digits(Rect(i * 20, j * 20, 20, 20));
            roi.convertTo(roi_float, CV_32F);
            roi_flatten = roi_float.reshape(1, 1);

            train_images.push_back(roi_flatten);
            train_labels.push_back(j / 5);
        }
    }

    Ptr<KNearest> knn = KNearest::create();
    knn->train(train_images, ROW_SAMPLE, train_labels);

    return knn;
}

Point ptPrev(-1, -1);

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
    Mat img = *(Mat*)userdata;

    if (event == EVENT_LBUTTONDOWN) {
        ptPrev = Point(x, y);
    } else if (event == EVENT_LBUTTONUP) {
        ptPrev = Point(-1, -1);
    } else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON)) {
        line(img, ptPrev, Point(x, y), Scalar::all(255), 40, LINE_AA, 0);
        ptPrev = Point(x, y);

        imshow("img", img);
    }
}