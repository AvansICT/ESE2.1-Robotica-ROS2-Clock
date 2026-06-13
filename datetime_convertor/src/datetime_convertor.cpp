#include <memory>
#include <iomanip>
#include <sstream>
#include <regex>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class DateTimeConvertor : public rclcpp::Node
{
public:
    DateTimeConvertor()
        : Node("datetime_convertor")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("time_input", 10);
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "datetime_input", 10,
            std::bind(&DateTimeConvertor::topic_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "DateTime Convertor Node has been started.");
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());

        // Remove the date

        auto message = std_msgs::msg::String();

        std::string format = msg->data.c_str();
        format = std::regex_replace(format, std::regex(".* "), "");  // remove everything before SPACE (so the date)
        format = std::regex_replace(format, std::regex(":..$"), ""); // remove the last 2 digits (the seconds)

        // Create and publish the message
        message.data = format;

        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<DateTimeConvertor>());
    rclcpp::shutdown();
    return 0;
}