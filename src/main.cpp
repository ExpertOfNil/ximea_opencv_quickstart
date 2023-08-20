#include "xiApiPlusOcv.hpp"
#include <iostream>
#include <opencv2/core/types.hpp>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>

#define EXPECTED_IMAGES 150

cv::Ptr<cv::SimpleBlobDetector> get_blob_detector();

int main() {
    xiAPIplusCameraOcv cam;
    cam.OpenFirst();
    cam.SetExposureTime(10000);
    cam.StartAcquisition();
    XI_IMG_FORMAT format = cam.GetImageDataFormat();

    cv::Mat image = cam.GetNextImageOcvMat();
    int width = image.cols;
    int height = image.rows;
    cv::Point center(width / 2, height / 2);
    cv::Scalar draw_color(255, 0, 255);
    // Set vertical and horizontal line limits
    cv::Point vline_start(center.x, 0);
    cv::Point vline_end(center.x, height);
    cv::Point hline_start(0, center.y);
    cv::Point hline_end(width, center.y);
    int radius = 20;
    // Set target x and y bounds
    auto xmin = (float)(center.x - radius);
    auto xmax = (float)(center.x + radius);
    auto ymin = (float)(center.y - radius);
    auto ymax = (float)(center.y + radius);

    bool roll_video = true;
    while (roll_video) {
        cv::Mat image = cam.GetNextImageOcvMat();
        cv::Mat image_out;
        cv::cvtColor(image, image_out, cv::COLOR_GRAY2RGB);

        line(image_out, vline_start, vline_end, draw_color, 2);
        line(image_out, hline_start, hline_end, draw_color, 2);
        circle(image_out, center, radius, draw_color, 2);

        cv::Ptr<cv::SimpleBlobDetector> sbd = get_blob_detector();
        std::vector<cv::KeyPoint> keypoints;
        sbd->detect(image, keypoints);

        // Display keypoint values
        size_t n_keypoints = keypoints.size();
        for (unsigned i = 0; i < n_keypoints; ++i) {
            auto pt = keypoints[i].pt;
            if ((pt.x > xmin) && (pt.x < xmax) && (pt.y > ymin) &&
                (pt.y < ymax)) {
                circle(image_out, keypoints[i].pt, 3, cv::Scalar(0, 0, 255), -1,
                       cv::LINE_8, 0);
            }
        }

        drawKeypoints(image_out, keypoints, image_out, cv::Scalar(0, 255, 0),
                      cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        imshow("Image from camera", image_out);
        int key = cv::waitKey(2);
        if (key == 32) {
            roll_video = false;
        }
    }

    cam.StopAcquisition();
    cam.Close();
    std::cout << "Done" << std::endl;
    cv::waitKey(0);
}

cv::Ptr<cv::SimpleBlobDetector> get_blob_detector() {
    cv::SimpleBlobDetector::Params params;
    params.minThreshold = 0.0;
    params.maxThreshold = 200.0;
    // params.thresholdStep = 200.0;
    // params.filterByArea = filterByArea;
    // params.minArea = minArea;
    // params.maxArea = maxArea;
    // params.filterByCircularity = filterByCircularity;
    // params.minCircularity = minCircularity;
    // params.maxCircularity = maxCircularity;
    // params.filterByConvexity = filterByConvexity;
    // params.minConvexity = minConvexity;
    // params.maxConvexity = maxConvexity;
    //params.filterByInertia = true;
    //params.minInertiaRatio = 0.5;
    //params.maxInertiaRatio = 1.0;
    // params.filterByColor = filterByColor;
    // params.blobColor = blobColor;
    // params.minRepeatability = minRepeatability;
    // params.minDistBetweenBlobs = minDistBetweenBlobs;

    cv::Ptr<cv::SimpleBlobDetector> sbd =
        cv::SimpleBlobDetector::create(params);
    return sbd;
}
