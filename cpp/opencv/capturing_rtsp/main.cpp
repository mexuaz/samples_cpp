#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>

using namespace cv;

using namespace std;

static std::mutex mtx;
static std::condition_variable cnd;

static bool g_camera_on = true;

enum framebits_t {
    fb_none = 0x0,
    fb_win = 0x1,
    fb_rec = 0x2,
    fb_all = 0xFF
};

static framebits_t g_ready_frame = fb_none;

static double g_actual_fps = 0.;

static double g_fps = 25.;
static int g_width = 0;
static int g_height = 0;


static Mat g_frame_camera;

void print_osd(const std::string& osd, cv::Mat& img) {
    const int lineHeight = min(15, img.cols / 60);
    double fontScale = getFontScaleFromHeight(FONT_HERSHEY_COMPLEX_SMALL, static_cast<int>(lineHeight*.85));
    std::stringstream ss(osd);
    std::string to;

    int i = 1;
    while(std::getline(ss,to,'\n')){
        putText(img, to, Point(0, img.rows - lineHeight*i),
                FONT_HERSHEY_COMPLEX_SMALL, fontScale,
                Scalar(0, 0, 255), 1,
                LINE_AA);
        i++;
    }

}


void thread_capture(const std::string& file) {

	VideoCapture cap;
	cap.setExceptionMode(true);

	if(cap.open(file, CAP_FFMPEG)) {
	    g_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
	    g_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));
	    g_fps = cap.get(cv::CAP_PROP_FPS);
	    if( g_fps < 1 || g_fps > 200) {
	        cerr << "returned fps: " << g_fps << endl;
	        g_fps = 25; // set to a common value if the value does not make sense.
	    }

        std::cout << "Start capturing " << g_width << 'x' << g_height << '@' << g_fps << std::endl;

    }

	while(cap.isOpened()  && g_camera_on) {

        auto e1 = getTickCount();

        if(!cap.grab()) {
			g_camera_on = false;
			g_ready_frame = fb_all; // Forcing the window and record thread to acquire the lock and exit
			throw std::runtime_error("Can't read frame from camera");
		}

        g_actual_fps = getTickFrequency() / (getTickCount() - e1);

		if(mtx.try_lock()) {
			cap.retrieve(g_frame_camera);
			g_ready_frame = fb_all;
			mtx.unlock();
			cnd.notify_one();
		}

	}

	cap.release();

	std::cout << "Exiting capture process." << std::endl;
}

void thread_record(const std::string& file, const std::string& codec) {

    if(codec.size() < 4) {
        throw std::runtime_error("Not a valid number of chars for codec.");
    }

    VideoWriter vw(file, VideoWriter::fourcc(codec[0],codec[1],codec[2],codec[3]), g_fps, Size(g_width, g_height));

    if(!vw.isOpened()) {
        throw std::runtime_error("Could not open the file for saving video.");
    }

    std::cout << "Video writing started ... " << std::endl;

    while(vw.isOpened()) {

        Mat frame;
        {
            std::unique_lock<std::mutex> lk(mtx);
            cnd.wait(lk, []{return g_ready_frame & fb_rec;}); // wait for record bit
            frame = g_frame_camera.clone();
            g_ready_frame = static_cast<framebits_t>(g_ready_frame & ~fb_rec); // clear the record bit
        }
        cnd.notify_one();

        if(frame.empty()) {
            vw.write(frame);
        } else {
            vw.release();
        }

    } // End of loop

    cout << "Existing Writer thread." << endl;
}

void thread_window(const std::string& name, bool osd) {

    namedWindow(name, WINDOW_OPENGL);
    double time = 0;
    while(g_camera_on) {

        auto e1 = getTickCount();

        Mat frame;
        {
            std::unique_lock<std::mutex> lk(mtx);
            cnd.wait(lk, []{return g_ready_frame & fb_win;}); // wait for win bit
            frame = g_frame_camera.clone();
            g_ready_frame = static_cast<framebits_t>(g_ready_frame & ~fb_win); // clear the win bit
        }
        cnd.notify_one();

        if(osd) {
            ostringstream oss;
            oss
                    << "Resolution: " << g_width << 'x' << g_height << std::endl
                    << "FPS: " << std::fixed << std::setprecision(1) << g_actual_fps << std::endl
                    << "Decode FPS: " << std::fixed << std::setprecision(1) << 1. / time << std::endl;

            print_osd(oss.str(), frame);
        }


        imshow(name, frame);

        int key = waitKey(1);
        if(key==27){
            g_camera_on = false;
            cout << "Terminating capture!" << endl;
        } else if(key == 's') {            ostringstream oss;
            oss
                    << "Resolution: " << g_width << " x " << g_height << std::endl
                    << "FPS: " << std::fixed << std::setprecision(1) << g_actual_fps << std::endl
                    << "Decode FPS: " << std::fixed << std::setprecision(1) << 1. / time << std::endl;

            print_osd(oss.str(), frame);
            static int count = 0;
            std::ostringstream filename;
            filename << "img" << std::setfill('0') << std::setw(5) << ++count << ".png";
            imwrite(filename.str(), frame);
        } else if(key == 'o' || key == 'O') {
            osd = !osd;
        }


        time = (getTickCount() - e1) / getTickFrequency();

    } // End of loop

    destroyWindow(name);
    cout << "Existing GUI thread." << endl;
}



int main(int argc, char** argv) {

    const String keys =
            "{help h usage ? |                 | print this message        }"
            "{@host          |<none>           | host or ip address        }"
            "{u user         |administrator    | username                  }"
            "{p pass         |                 | password                  }"
            "{o port         |554              | port                      }"
            "{a address      |defaultSecondary | address                   }" // defaultPrimary defaultTertiary
            "{m params       |streamType=u     | parameters                }"
            "{s no-osd       |                 | turns off OSD info        }"
            "{w no-win       |                 | no window (performance)   }"
            "{c codec        |PIM1             | recording codec           }"
            "{r record       |                 | record the stream to file }"
    ;

    CommandLineParser parser(argc, argv, keys);
    parser.about("easy streamer v1.0.0");
    if (parser.has("help"))  {
        parser.printMessage();
        return 0;
    }

    string username = parser.get<std::string>("user");
    string password = parser.get<std::string>("pass");
    string host = parser.get<std::string>(0);
    short port = static_cast<short>(parser.get<int>("port"));

    string address = parser.get<std::string>("address");
    string params = parser.get<std::string>("params");

    bool use_win = !parser.has("no-win");
    bool osd = !parser.has("no-osd");
    std::string codec = parser.get<std::string>("codec");
    std::string record_file = parser.get<std::string>("record");

    if (!parser.check()) {
        parser.printErrors();
        return 0;
    }

    ostringstream oss;
    oss
        << "rtsp://"  << username
        << ':' << password
        << '@' << host
        << ':' << port
        << '/'  << address
        << '?' << params;


	thread th_camera(thread_capture, oss.str());

    thread th_window, th_record;

    if(use_win) {
        th_window = thread(thread_window, host + " - " + address, osd);
	}

    if(!record_file.empty()) {
        th_record = thread(thread_record, record_file, codec);
    }

    if(th_record.joinable()) {
        th_record.join();
    }

	if(th_window.joinable()) {
        th_window.join();
	}

    if(th_camera.joinable()) {
        th_camera.join();
    }


	return 0;
}
