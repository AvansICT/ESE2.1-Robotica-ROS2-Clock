#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include <string>
#include <vector>

class SevenSegmentDisplay : public rclcpp::Node
{
public:
    SevenSegmentDisplay() : Node("seven_segment_display")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "time_input", 10,
            std::bind(&SevenSegmentDisplay::topic_callback, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "7-Segment Display Node started. Listening on 'time_input' topic...");

        // Initialize 7-segment patterns for digits 0-9 and colon
        init_segments();
    }

private:
    void init_segments()
    {
        // Each character is represented by 5 lines of display

        segments_['0'] = {
            " ███ ",
            "█   █",
            "█   █",
            "█   █",
            " ███ "};

        segments_['1'] = {
            "    █",
            "    █",
            "    █",
            "    █",
            "    █"};

        segments_['2'] = {
            " ███ ",
            "    █",
            " ███ ",
            "█    ",
            " ███ "};

        segments_['3'] = {
            " ███ ",
            "    █",
            " ███ ",
            "    █",
            " ███ "};

        segments_['4'] = {
            "█   █",
            "█   █",
            " ███ ",
            "    █",
            "    █"};

        segments_['5'] = {
            " ███ ",
            "█    ",
            " ███ ",
            "    █",
            " ███ "};

        segments_['6'] = {
            " ███ ",
            "█    ",
            " ███ ",
            "█   █",
            " ███ "};

        segments_['7'] = {
            " ███ ",
            "    █",
            "    █",
            "    █",
            "    █"};

        segments_['8'] = {
            " ███ ",
            "█   █",
            " ███ ",
            "█   █",
            " ███ "};

        segments_['9'] = {
            " ███ ",
            "█   █",
            " ███ ",
            "    █",
            " ███ "};

        segments_[':'] = {
            "     ",
            "  █  ",
            "     ",
            "  █  ",
            "     "};

        // Space character for unsupported chars
        segments_[' '] = {
            "     ",
            "     ",
            "     ",
            "     ",
            "     "};
    }

    void display_string(const std::string &str)
    {
        if (str.empty())
        {
            RCLCPP_WARN(this->get_logger(), "Empty string received");
            return;
        }

        // Clear screen (optional - comment out if you want history)
        std::cout << "\033[2J\033[1;1H";

        std::cout << "\n";
        std::cout << "Received: " << str << "\n\n";

        // Print each line of the 7-segment display
        for (int line = 0; line < 5; line++)
        {
            std::cout << "  ";
            for (char c : str)
            {
                // Check if character is supported
                if (segments_.find(c) != segments_.end())
                {
                    std::cout << segments_[c][line] << " ";
                }
                else
                {
                    RCLCPP_WARN_ONCE(this->get_logger(), "Unsupported character: '%c' (will be displayed as space)", c);
                    std::cout << segments_[' '][line] << " ";
                }
            }
            std::cout << "\n";
        }

        std::cout << "\n";
        std::cout.flush();
    }

    void topic_callback(const std_msgs::msg::String::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received: %s", msg->data.c_str());
        display_string(msg->data);
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
    std::map<char, std::vector<std::string>> segments_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SevenSegmentDisplay>());
    rclcpp::shutdown();
    return 0;
}