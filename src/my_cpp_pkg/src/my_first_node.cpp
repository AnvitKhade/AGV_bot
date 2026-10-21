#include "rclcpp/rclcpp.hpp"

class myNode : public rclcpp::Node
{
public:
    myNode() : Node("cpp_test"), count(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello, ROS!");
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&myNode::timer_callback, this)
        );
    }
private:
    void timer_callback()
    {
        RCLCPP_INFO(this->get_logger(), "HIIIIIII");
        count++;    
    }
    rclcpp::TimerBase::SharedPtr timer_;
    int count;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<myNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}