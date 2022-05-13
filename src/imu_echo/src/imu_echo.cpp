#include <memory>
#include <iostream>
#include <string>
#include <fstream>

#include "rclcpp/rclcpp.hpp"
//#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/imu.hpp"
using std::placeholders::_1;

class IMU_echo2txt : public rclcpp::Node
{
public:
  IMU_echo2txt()
  : Node("imu_echo")
  {
    subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
      "/gw/odom/input/xsens", 20, std::bind(&IMU_echo2txt::topic_callback, this, _1));
  }

private:
  void topic_callback(const sensor_msgs::msg::Imu::SharedPtr msg) const
  {
    //RCLCPP_INFO(this->get_logger(), "start to print IMU data ");
    std::string path = "/media/wy/7089b057-a6d2-459b-a158-eae994447d5b/MA/data/imu.txt";
    //std_msgs::msg::Header h = msg->Header;
    double h_time = (double(msg->header.stamp.sec) + double(msg->header.stamp.nanosec/1e9)) * 1e9;
    //double h_time = double(msg->header.stamp.nanosec);
    std::ofstream loop_path_file(path, std::ios::app);
        loop_path_file.setf(std::ios::fixed, std::ios::floatfield);
        loop_path_file.precision(0);
        loop_path_file << h_time << ",";
        loop_path_file.precision(5);
        loop_path_file  << msg->angular_velocity.x << ","
              << msg->angular_velocity.y << ","
              << msg->angular_velocity.z << ","
              //<< linear_acceleration.w() << ","
              << msg->linear_acceleration.x << ","
              << msg->linear_acceleration.y << ","
              << msg->linear_acceleration.z << ","
              << std::endl;
        loop_path_file.close();
    	
    
  }
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<IMU_echo2txt>());
  rclcpp::shutdown();
  return 0;
}
