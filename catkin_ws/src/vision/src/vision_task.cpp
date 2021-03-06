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
    // Publisher for advertising center of ball
    ros::Publisher x_pub_ = nh_.advertise<std_msgs::Int32>("/x_center", 1000);

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
            cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::RGB8); // Swapped BGR8 to RGB8
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        cv::Mat hsv;
        cv::cvtColor(cv_ptr->image, hsv, CV_BGR2HSV);

        std::vector<cv::Mat> channels;
        cv::split(hsv, channels);

        cv::Mat H = channels[0];
        cv::Mat S = channels[1];
        cv::Mat V = channels[2];

        cv::Mat shiftedH = H.clone();
        int shift = 25; // in openCV hue values go from 0 to 180 (so have to be doubled to get to 0 .. 360) because of byte range from 0 to 255
        for(int j=0; j<shiftedH.rows; ++j)
            for(int i=0; i<shiftedH.cols; ++i)
                shiftedH.at<unsigned char>(j,i) = (shiftedH.at<unsigned char>(j,i) + shift)%180;

        cv::Mat cannyS;
        cv::Mat cannyH;
        cv::Canny(shiftedH, cannyH, 100, 50);
        cv::dilate(cannyH, cannyH, cv::Mat());
        cv::dilate(cannyH, cannyH, cv::Mat());

        // extract contours of the canny image:
        std::vector<std::vector<cv::Point> > contoursH;
        std::vector<cv::Vec4i> hierarchyH;
        cv::findContours(cannyH, contoursH, hierarchyH, CV_RETR_TREE , CV_CHAIN_APPROX_SIMPLE);

        // draw the contours to the input image:
        int largest_contour_index;
        double largest_area;
        double area;
        for( int i = 0; i < contoursH.size(); i++ )
        {
            area = contourArea(contoursH[i], false);
            if (area > largest_area) 
            {
                largest_area = area;
                largest_contour_index = i;
            }
        }
        
        // draw bounding box for ball
        cv::Rect bounding_rect = cv::boundingRect(contoursH[largest_contour_index]);
        cv::rectangle(cv_ptr->image, bounding_rect, CV_RGB(0,255,0), 1, 8, 0);

        // find center of bounding box
        int x = bounding_rect.x + bounding_rect.width/2;
        int y = bounding_rect.y + bounding_rect.height/2;

        // YOUR CODE BELOW
        // Create a Int32 std msg 

        // Set its data to the value of x

        // Publish using x_pub_


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