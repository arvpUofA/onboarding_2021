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
    // Add your bounding box publisher here using the nh_ node handler
    ros::Publisher bounding_box_ = nh_.advertise<std_msgs::Int32>("/bounding_box", 1000);
    std_msgs::Int32 message;

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

        // Converting the image into an HSV version
        cv::Mat hsv;
        cv::cvtColor(cv_ptr->image, hsv, CV_BGR2HSV);

        //std::vector<cv::Mat> channels;
        std::vector<cv::Mat> channels;
        cv::split(hsv, channels);

        // Separating the Hue, saturation, and value channels
        cv::Mat H = channels[0];
        cv::Mat S = channels[1];
        cv::Mat V = channels[2];

        // Creating the canny image from the hue 
        cv::Mat cannyH;
        cv::Canny(H, cannyH, 0, 100);

        // Extracting the contours from the canny image
        std::vector<std::vector<cv::Point> > contoursH;
        std::vector<cv::Vec4i> heirarchyH;
        cv::findContours(cannyH, contoursH, heirarchyH, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

        //Finding the largest contour
        int largest_contour_index;
        double largest_area;
        for (int i = 0; i < contoursH.size(); i++) {

            double area = contourArea(contoursH[i], false);
            if (!largest_area || (area > largest_area)) {
                largest_area = area;
                largest_contour_index = i;
            }
        }

        // Drawing the bounding box
        cv::Rect bounding_rect = boundingRect(contoursH[largest_contour_index]);
        rectangle(cv_ptr->image, bounding_rect, cv::Scalar(0, 255, 0), 1, 8, 0);
        
        message.data = bounding_rect.x + ((bounding_rect.width)/2);
        bounding_box_.publish(message);
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
