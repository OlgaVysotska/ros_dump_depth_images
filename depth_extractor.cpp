#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

static const std::string OPENCV_WINDOW = "Image window";

int counter;

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  
public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    // image_sub_ = it_.subscribe("/camera/image_raw", 1, &ImageConverter::imageCb, this);
    image_sub_ = it_.subscribe("/X1/depth/image_raw", 1, &ImageConverter::imageCb, this);
    // image_pub_ = it_.advertise("/image_converter/output_video", 1);

    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      // cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_16UC1);
      counter++;
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, cv_ptr->image);
    cv::waitKey(3);
    
    // Output modified video stream
    // image_pub_.publish(cv_ptr->toImageMsg());
    //Write images
    ROS_INFO("counter %d", counter);
    std::ostringstream ss;
    ss <<"/home/olga/ros_workspace/data/pics/depth_"<<std::setw(6) << std::setfill('0') << counter << ".png";
    std::string img_name(ss.str());
    std::cout << img_name << std::endl;
    cv::imwrite(img_name, cv_ptr->image);

  }
};

int main(int argc, char** argv)
{
  counter = 0;
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  ros::spin();
  return 0;
}