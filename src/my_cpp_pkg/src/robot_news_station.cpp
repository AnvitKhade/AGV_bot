#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;

class robotNewsStationNode : public rclcpp::Node
{
public:
    robotNewsStationNode() : Node("robot_news_station"), robot_name_("R2D2")
    {
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this->create_wall_timer(500ms, std::bind(&robotNewsStationNode::publishNews, this));
        RCLCPP_INFO(this->get_logger(), "Robot news station node has been started.");
    }
private:
    void publishNews()
    {
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi this is ") + robot_name_ + std::string(" from the robot news station!");
        publisher_->publish(msg);
    }
    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<robotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}