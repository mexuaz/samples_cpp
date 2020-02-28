#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, char ** argv) {

    const char* win{"capturing"};

    VideoCapture cap;
    if(argc > 1) {
        cap.open(argv[1]);
    } else {
        cap.open(CAP_ANY);
    }

    Mat frame;
    namedWindow(win);
    while(cap.isOpened() && cap.read(frame)) {
        imshow(win, frame);
        if(27==waitKey(33)) {
            cap.release();
        }
    }

    destroyAllWindows();

    return 0;
}
