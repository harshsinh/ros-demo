#include <sstream>
#include <ros/ros.h>
#include <std_msgs/Int16.h>
#include "CVInclude.h"

cv::VideoCapture cap;

void msgCallback (const std_msgs::Int16::ConstPtr& msg) {

    if (msg -> data == 1)
        cap.release ();

}


int main (int argc, char ** argv)
{
    int count = 0;
    int camera = argv [1][0] - 48;

    if (camera < 0) {

        ROS_ERROR_STREAM ("Not a  valid camera address");

    }

    ros::init (argc, argv, "camera_driver");
    ros::NodeHandle nh;
    image_transport::ImageTransport it (nh);

    image_transport::Publisher pub = it.advertise ("image_raw", 1);

    ros::Subscriber sub = nh.subscribe ("toggle", 1000, msgCallback);

    cap.open (camera);

    cv::namedWindow ("here");
    cv::startWindowThread ();

    if ( !cap.isOpened ()) {

        ROS_ERROR_STREAM ("Camera Not Open");
        return 1;

    }

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate (30);

    while (nh.ok ())
    {
        cap >> frame;

        if ( !frame.empty ()) {

            cv::imshow("here", frame);
            msg = cv_bridge::CvImage (std_msgs::Header (), "bgr8", frame).toImageMsg ();
            pub.publish (msg);

        }

        else {
            ROS_ERROR_STREAM ("No Image found!.");
            return 1;
        }

        ros::spinOnce ();
        loop_rate.sleep ();

        if ( !cap.isOpened ()) {

            return 0;

        }
    }
}
