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

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 3.8;
  goal.target_pose.pose.orientation.w = 3.8;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  //if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  //  ROS_INFO("Hooray, the base moved 1 meter forward");
  //else
  //  ROS_INFO("The base failed to move forward for some reason");
  
  // Waiting 5 Seconds
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for base to finish picking up");
  }
  // Going back to initial position
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 0;
  goal.target_pose.pose.orientation.w = 3.14;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the base moved forward");
  else
    ROS_INFO("The base failed to move forward 1 meter for some reason");

  return 0;
}
