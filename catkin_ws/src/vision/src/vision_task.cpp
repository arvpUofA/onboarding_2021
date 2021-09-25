#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <std_msgs/Int32.h>

class ImageConverter
{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;
    ros::Publisher center_point = nh_.advertise<std_msgs::Int32> ("center_point", 1000);

public:
    ImageConverter()
            : it_(nh_)
    {
        // Subscribe to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/jetbot_camera/image_raw", 1,
                                   &ImageConverter::imageCb, this);
        image_pub_ = it_.advertise("/image_converter/output_video", 1);


    }

    ~ImageConverter()
    {

    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        cv_bridge::CvImagePtr cv_ptr;
        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        // DElETE CODE BELOW AND PUT YOUR OWN CODE FOR DRAWING BOUNDING BOXES

        // Draw an example circle on the video stream
        //if (cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
        //    cv::circle(cv_ptr->image, cv::Point(50, 50), 10, CV_RGB(255,0,0));

        // creates an image array
        cv::Mat hsv;
        cv::cvtColor(cv_ptr->image, hsv, CV_BGR2HSV);

        // I think this gets the hue, saturation and something else into arrays
        std::vector<cv::Mat> channels;
        cv::split(hsv, channels);

        cv::Mat H = channels[0];
        cv::Mat S = channels[1];
        cv::Mat V = channels[2];

        cv::Mat shiftedH = H.clone();
        int shift = 25;
        for (int j = 0; j < shiftedH.rows; j++) {
            for (int i = 0; i < shiftedH.cols; i++) {
                shiftedH.at<unsigned char> (j, i) = (shiftedH.at<unsigned char> (j, i) + shift) % 180;
            }
        }
        
        cv::Mat cannyH;
        cv::Canny(shiftedH, cannyH, 100, 50);

        std::vector<std::vector<cv::Point>> contoursH;
        std::vector<cv::Vec4i> hierarchyH;
        cv::findContours(cannyH, contoursH, hierarchyH, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE);

        int largest_contour_index;
        double largest_area = 0;

        // gets largest contour area and the index of that contour
        for (int i = 0; i < contoursH.size(); i++) {
            double area = contourArea(contoursH[i], false);
            if (area > largest_area) {
                largest_area = area;
                largest_contour_index = i;
            }
        }

        // creates bounding rect with largest contour and then draws it onto the image
        cv::Rect bounding_rect = boundingRect(contoursH[largest_contour_index]);
        rectangle(cv_ptr->image, bounding_rect, cv::Scalar(0,255,0), 1, 8, 0);

        // gets x and y coordinate of top left corner of bounding rect
        int x = bounding_rect.x;
        int y = bounding_rect.y;

        // creates point center and puts midpoint coordinate into the new point center
        cv::Point center;
        center.x = x + bounding_rect.width/2;
        center.y = y + bounding_rect.height/2;
        
        //cv::circle(cv_ptr->image, center, 10, cv::Scalar(0,255,0));

        // creates x coordinate data and publishes it to center_point topic
        std_msgs::Int32 midpoint;
        midpoint.data = center.x;
        center_point.publish(midpoint);
        
        // YOUR CODE ABOVE


        // Output modified video stream
        image_pub_.publish(cv_ptr->toImageMsg());
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_converter");
    ImageConverter ic;
    ros::spin();
    return 0;
}
