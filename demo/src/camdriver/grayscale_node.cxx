#include <sstream>
#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include "CVInclude.h"

#define im_width 640
#define im_height 480
#define fps 30

using namespace std;

cv::VideoCapture cap;

void msgCallback (const sensor_msgs::ImageConstPtr& msg)
{
    cv::Mat image;
    image = cv_bridge::toCvShare (msg) -> image;

    if (!image.empty ()) {
        cv::cvtColor (image, image, CV_BGR2GRAY);
        cv::imshow ("gray", image);
        cv::waitKey (0);
        return;
    }
    ROS_ERROR_STREAM ("Camera not open!");
    return;
}


int main (int argc, char* argv [])
{
    ros::init (argc, argv, "gray_driver");
    ros::NodeHandle nh;

    image_transport::ImageTransport it (nh);
    image_transport::Subscriber sub = it.subscribe ("image_raw", 1000, msgCallback);

    cv::namedWindow ("gray");
    cv::startWindowThread ();

    ros::Rate loop_rate (fps);
    ros::spin();

    return 0;
}
