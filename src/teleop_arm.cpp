#include <rclcpp/rclcpp.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory_point.hpp>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>

int getch() {
    int ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

class TeleopArm : public rclcpp::Node {
public:
    TeleopArm() : Node("teleop_arm") {
        publisher_ = this->create_publisher<trajectory_msgs::msg::JointTrajectory>(
            "/joint_trajectory_controller/joint_trajectory", 10);
        positions_ = {0.0, 0.0, 0.0, 0.0};
        joint_names_ = {"j0", "j1", "j2", "j3"};
        step_ = 0.1;
        RCLCPP_INFO(this->get_logger(), "Control Armando!\nQ/A: j0 | W/S: j1 | E/D: j2 | R/F: j3 \nCTRL-C to quit");
    }

    void loop() {
        while (rclcpp::ok()) {
            int key = getch();
            if (key == 3) break; 
            
            bool updated = false;
            switch(key) {
                case 'q': positions_[0] += step_; updated = true; break;
                case 'a': positions_[0] -= step_; updated = true; break;
                case 'w': positions_[1] += step_; updated = true; break;
                case 's': positions_[1] -= step_; updated = true; break;
                case 'e': positions_[2] += step_; updated = true; break;
                case 'd': positions_[2] -= step_; updated = true; break;
                case 'r': positions_[3] += step_; updated = true; break;
                case 'f': positions_[3] -= step_; updated = true; break;
            }

            if (updated) {
                auto msg = trajectory_msgs::msg::JointTrajectory();
                msg.joint_names = joint_names_;
                
                trajectory_msgs::msg::JointTrajectoryPoint point;
                point.positions = positions_;
                point.time_from_start.sec = 0;
                point.time_from_start.nanosec = 200000000; 
                
                msg.points.push_back(point);
                publisher_->publish(msg);
            }
        }
    }

private:
    rclcpp::Publisher<trajectory_msgs::msg::JointTrajectory>::SharedPtr publisher_;
    std::vector<double> positions_;
    std::vector<std::string> joint_names_;
    double step_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TeleopArm>();
    node->loop();
    rclcpp::shutdown();
    return 0;
}
