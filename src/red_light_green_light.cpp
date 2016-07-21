#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"

int main(int argc, char **argv)
{

    ros::init(argc, argv, "red_light_green_light");

    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    
    geometry_msgs::Twist red_light_twist;
    geometry_msgs::Twist green_light_twist;
    green_light_twist.linear.x = 0.5;

    bool driving_forward = false;
    ros::Time light_change_time = ros::Time::now();
    ros::Rate loop_rate(10);

    while(ros::ok())
    {
        if(driving_forward)
        {
            cmd_vel_pub.publish(green_light_twist);
        }
        else 
        {
            cmd_vel_pub.publish(red_light_twist);
        }

        if(light_change_time > ros::Time::now())
        {
            driving_forward = !driving_forward;
            light_change_time = ros::Time::now() + ros::Duration(3);
        }

        loop_rate.sleep();

    }

}
