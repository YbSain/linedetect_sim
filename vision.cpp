#include "vision.hpp"

void ctrlc(int) {
    ctrl_c_pressed = true;
}

Mat makethresh(Mat frame) {
    int x = 0, y = 270, width = frame.cols, height = 90;
    Rect Roi(x, y, width, height);

    Mat Roiframe = frame(Roi);
    cvtColor(Roiframe, Roiframe, COLOR_BGR2GRAY);

    Scalar meanValue = mean(Roiframe);
    double currentBrightness = meanValue[0];
    double targetBrightness = 100.0;
    double adjustment = (targetBrightness - currentBrightness);
    Roiframe.convertTo(Roiframe, -1, 1, adjustment);

    threshold(Roiframe, Roiframe, 165, 255, THRESH_BINARY);
    morphologyEx(Roiframe, Roiframe, MORPH_OPEN, Mat(), Point(-1, -1));
    return Roiframe;
}

Mat Labeling(Mat Threshframe, Mat Grayframe) {
    Mat labels, stats, centroids;
    static Point2d firstCenter(Threshframe.cols / 2, Threshframe.rows / 2);
    int cnt = connectedComponentsWithStats(Threshframe, labels, stats, centroids);

    for (int i = 1; i < cnt; i++) {
        int* p = stats.ptr<int>(i);
        double* c = centroids.ptr<double>(i);
        if (p[4] < 20) continue;

        Rect currentBoundingBox(p[0], p[1], p[2], p[3]);
        Point2d currentCenter(c[0], c[1]);

        rectangle(Grayframe, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 255, 255), 2);
        double xdistance = targetCenter.x - c[0];

        if (!isTarget) {
            targetCenter = firstCenter;
            isTarget = true;
        }
        else if (abs(xdistance) <= 80) {
            rectangle(Grayframe, Rect(p[0], p[1], p[2], p[3]), Scalar(0, 0, 255), 2);
            targetBoundingBox = currentBoundingBox;
            targetCenter = currentCenter;
        }
        circle(Grayframe, targetCenter, 3, Scalar(0, 255, 0), 2);
        circle(Grayframe, currentCenter, 5, Scalar(0, 255, 0), FILLED);
    }
    return Grayframe;
}

int getError(Mat& Threshframe, Point& tmp_pt) {
    return (Threshframe.cols / 2) - tmp_pt.x;
}
