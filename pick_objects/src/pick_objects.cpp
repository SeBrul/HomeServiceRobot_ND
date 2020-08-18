#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup;

  // set up the frame parameters
  pickup.target_pose.header.frame_id = "map";
  pickup.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pickup.target_pose.pose.position.x = 3.8;
  pickup.target_pose.pose.orientation.w = 3.8;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(pickup);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the robot reaced the pick-up position");
    ros::Duration(5.0).sleep();
}
  else {
    ROS_INFO("The robot failed to reach the pick-up position");
}

  move_base_msgs::MoveBaseGoal dropoff;

  // set up the frame parameters
  dropoff.target_pose.header.frame_id = "map";
  dropoff.target_pose.header.stamp = ros::Time::now();
  // Going back to initial position
  // Define a position and orientation for the robot to reach
  dropoff.target_pose.pose.position.x = 0;
  dropoff.target_pose.pose.orientation.w = 3.14;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(dropoff);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED) {
    ROS_INFO("Hooray, the robot reached the drop-off position");
}
  else {
    ROS_INFO("The robot failed to reach the drop-off position");
}

  return 0;
}
