![](/images/world.jpg?raw=false)

# Service Robot

> Combining SLAM and Navigation into a service robot that autonomously transports objects from A to B.
> Capstone Project of the Robotics Software Engineer Nanodegree Programme

With the help of the ROS system, a digital service robot based on the turtlebot is created. The robot takes its pick-up destination in the form of a coordinate input, navigates towards it, starts the pick-up process, navigates towards its original position and starts the drop-off process. The problem is split in mapping, localization & navigation and service functions.

![](/images/PickupDropoff.gif)
---

## Table of Contents
- [Built With](#built-with)
- [SLAM](#slam)
- [Localization and Navigation](#localization-and-navigation)
- [Service Functions](#service-functions)

---

## Built With
The project is built primarily on the following official ROS packages. 

- [gmapping](http://wiki.ros.org/turtlebot_teleop)
- [turtlebot_teleop](http://wiki.ros.org/turtlebot_teleop)
- [turtlebot_rviz_launcher](http://wiki.ros.org/turtlebot_rviz_launchers)
- [turtlebot_gazebo](wiki.ros.org/turtlebot_gazebo)

Each shell script need the permission to be executed:

```javascript
cd ~/catkin_ws/
chmod +x ./src/*script_name*.sh
```
---

## SLAM
First, the Simultaneous Localization and Mapping (**SLAM**) is implemented from the ROS package [gmapping](http://wiki.ros.org/gmapping). This allows the robot to create a map and localize itself with the help of the equipped laser range finder sensors and RGB-D camera. The turtlebot is planted into an environment without any prior knowledge of its environment.

![](/images/SLAM.gif) ![](/images/2dmap.png?raw=false)
<!--![](/images/smallWorld.jpg?raw=false)-->


```javascript
./src/test_slam
```

## Localization and Navigation
The next goal for the robot is to find its way to a defined set of coordinates and orient itself with respect to them. This is the next step towards an autonomous pick-up and drop-off service. This part is based on the previously implemented SLAM algorithm. The localization is performed with the ROS Navigation stack, which is based on the Dijkstra algorithm, a variant of the **Uniform Cost Search** algorithm. With the help of the Adaptive Monte Carlo Localization (**AMCL**) the robot is able to localize itself.

![](/images/Localization.png?raw=false)

```javascript
./src/test_slam
```

## Service Functions

Next, two additional packages are created and integrated the *pick_objects* node and the *add_markers* node. The *add_marker* node is a virtual object that is picked up and delivered by the robot. Thus it should first appear in its pick-up zone, and then in its drop off zone once the robot reaches it. Therefore the *add_markers* node has to publish to the robot the position of the pick-up destination. The *pick_up node* is then commanding the robot where to move.

![](/images/add_marker_pick_up.png?raw=false)

```javascript
./src/add_marker.sh
./src/pick_object.sh
```

Finally, all nodes can be launched with the shell script *home_service.sh*

```javascript
./src/home_service.sh
```
