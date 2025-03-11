#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main() {
      Mat img = imread("images/lenna.bmp");
      if (img.empty()) {
              cerr << "Can't open image." << endl;
              return -1;
      }

      namedWindow("img");
      imshow("img", img);

      while (true) {
            int keycode = waitKey();

            if (keycode == 'i' || keycode == 'I') {
                  img = ~img;
                  imshow("img", img);
            }
            else if (keycode == 27 || keycode == 'q' || keycode == 'Q') {
                  break;
            }
      }
      return 0;
}