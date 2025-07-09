#include "rclcpp/rclcpp.hpp"

#include <iostream>
#include <memory>
#include <string> 

#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/imu.hpp"

// Include Boost Program Options for command line argument parsing
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class SensorSubscriber : public rclcpp::Node
{
public:
    SensorSubscriber(
        std::string imu_topic
    )
        : Node("sensor_subscriber"), imu_topic_(imu_topic)
    {
        imu_subscription_ = this->create_subscription<sensor_msgs::msg::Imu>(
            imu_topic_, 10, std::bind(&SensorSubscriber::imu_callback, this, std::placeholders::_1));
    }

private:

    void imu_callback(const sensor_msgs::msg::Imu::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received IMU data: ");
    }

    rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_subscription_;
    std::string imu_topic_; 

};

int main (int argc, char** argv) 
{
    
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("imu_topic", po::value<std::string>()->default_value("/imu/data"), "IMU Topic to subscribe to");
    
    po::variables_map var_map;

    po::store(po::parse_command_line(argc, argv, desc), var_map);

    po::notify(var_map);

    if (var_map.count("help"))
    {
        // Print the description of the available options.
        std::cout << desc << "\n";
        return 0; 
    }

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSubscriber>(var_map["imu_topic"].as<std::string>()));

    rclcpp::shutdown();
}