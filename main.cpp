#include "vision.hpp"

bool ctrl_c_pressed = false;
Rect targetBoundingBox;
Point2d targetCenter;
bool isTarget = false;

int main() {
    TickMeter tm;
    //원본
    // string src = "nvarguscamerasrc sensor-id=0 ! 
    //     video/x-raw(memory:NVMM), width=(int)640, height=(int)360, 
    //     format=(string)NV12, framerate=(fraction)30/1 ! 
    //     nvvidconv flip-method=0 ! video/x-raw, 
    //     width=(int)640, height=(int)360, format=(string)BGRx ! 
    //     videoconvert ! video/x-raw, format=(string)BGR ! appsink";

    // VideoCapture source(src, CAP_GSTREAMER);
    // if(!source.isOpened()) { cerr << "Video Open Failed!!" << endl; return -1; }
    VideoCapture cap("5_lt_cw_100rpm_out.mp4");
    //VideoCapture cap("7_lt_ccw_100rpm_in.mp4");
    if (!cap.isOpened()) { cerr << "video open failed!" << endl; return -1; }

    string dst1 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
            nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
            h264parse ! rtph264pay pt=96 ! \
            udpsink host=203.234.58.170 port=8001 sync=false";
            
    string dst2 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
            nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
            h264parse ! rtph264pay pt=96 ! \
            udpsink host=203.234.58.170 port=8002 sync=false";
    VideoWriter writer1(dst1, 0, (double)30, Size(640, 360), true);
    if (!writer1.isOpened()) { cerr << "Writer open failed!" << endl; return -1; }
    VideoWriter writer2(dst2, 0, (double)30, Size(640, 90), true);
    if (!writer2.isOpened()) { cerr << "Writer open failed!" << endl; return -1; }
    if (!writer1.isOpened() || !writer2.isOpened()) {
        cerr << "Writer open failed!" << endl;
        return -1;
    }

    Mat frame;
    Dxl mx;
    bool mode = false;
    int lval = 0, rval = 0;

    struct timeval start, end1;
    double diff;

    signal(SIGINT, ctrlc);
    if (!mx.open()) {
        cerr << "Dxl error" << endl;
        return -1;
    }

    while (true) {
        gettimeofday(&start, NULL);
        cap >> frame;
        if (frame.empty()) break;

        Mat Threshframe = makethresh(frame);
        Mat displaymorph = Threshframe.clone();
        cvtColor(displaymorph, displaymorph, COLOR_GRAY2BGR);

        Point tmp_pt = targetCenter;
        Mat result = Labeling(Threshframe, displaymorph);
        int error = getError(Threshframe, tmp_pt);

        if (mx.kbhit()) {
            char ch = mx.getch();
            if (ch == 'q') break;
            else if (ch == 's') mode = true;
        }
        if (ctrl_c_pressed) break;

        lval = 100 - 0.1 * error;
        rval = -(100 + 0.1 * error);
        if (mode) mx.setVelocity(lval, rval);

        usleep(30 * 1000);
        gettimeofday(&end1, NULL);
        diff = end1.tv_sec + end1.tv_usec / 1000000.0 - start.tv_sec - start.tv_usec / 1000000.0;

        cout << "lval: " << lval << "\trval: " << rval << "\ttime: " << diff << endl;
        cout << "error: " << error << endl;

        writer1 << frame;
        writer2 << result;
    }
    mx.close();
    return 0;
}
