#include <chrono>
#include <memory>
#include <iomanip>
#include <sstream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class DateTimePublisher : public rclcpp::Node
{
public:
  DateTimePublisher()
      : Node("datetime_publisher")
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("date_time", 10);
    timer_ = this->create_wall_timer(
        1000ms, std::bind(&DateTimePublisher::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "DateTime Publisher Node has been started.");
  }

private:
  void timer_callback()
  {
    // Get current system time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
    std::tm local_time = *std::localtime(&time_t_now);

    // Format the date and time as a string
    std::stringstream ss;
    ss << std::put_time(&local_time, "%Y-%m-%d %H:%M:%S");

    // Create and publish the message
    auto message = std_msgs::msg::String();
    message.data = ss.str();

    RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DateTimePublisher>());
  rclcpp::shutdown();
  return 0;
}