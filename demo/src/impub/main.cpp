#include <string.h>
#include <ros/ros.h>
#include <ros/package.h>
#include <sensor_msgs/image_encodings.h>
#include "CVInclude.h"

int main (int argc, char** argv)
{
    ros::init (argc, argv, "image_publisher");
    ros::NodeHandle nh;

    cv_bridge::CvImage cv_image;
    sensor_msgs::Image ros_image;

    std::string path = ros::package::getPath ("demo");
    path = path.append ("/utils/images/001.jpg");
    std::cout << "Image : " << path << std::endl;

    cv_image.image = cv::imread (path, CV_LOAD_IMAGE_COLOR);
    cv_image.encoding = "bgr8";
    cv_image.toImageMsg (ros_image);

    ros::Publisher pub = nh.advertise<sensor_msgs::Image>("/static_image", 1);
    ros::Rate loop_rate (30);

    while (nh.ok())
    {
        pub.publish (ros_image);
        loop_rate.sleep ();
    }

    return 0;
}
