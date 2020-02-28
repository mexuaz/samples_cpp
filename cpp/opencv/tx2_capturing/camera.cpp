#include <opencv2/opencv.hpp>
#define STREAMCON "nvcamerasrc ! video/x-raw(memory:NVMM), width=(int)1920, height=(int)1080,format=(string)I420, framerate=(fraction)60/1 ! nvvidconv flip-method=2 ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink"

using namespace cv;

int main(int argc, char ** argv) {

    VideoCapture cap;
    if(argc > 1) {
        cap.open(argv[1]);
    } else {
        //cap.open(CAP_ANY);
	cap.open(STREAMCON);
    }

    Mat frame;
    namedWindow("Camera");
    while(cap.isOpened() && cap.read(frame)) {
        imshow("Camera", frame);
        int ch = waitKey(33);
        if(ch==27) {
            cap.release();
        }
    }

    destroyAllWindows();

    return 0;
}
