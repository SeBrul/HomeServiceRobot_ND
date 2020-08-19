![](/images/world.jpg?raw=false)

# Service Robot

> Combining SLAM and Navigation into a service robot that autonomously tranpsports objects from A to B.
> Capstone Project of the Robotics Software Engineer Nanodegree Programme

With the help of the ROS system a digital service robot of based on the turtlebot is created. The robot takes its pick-up destination in form of a coordinate input, navigates towards it, picks it up and brings it back to its original position. The problem is split in mapping, localization & navigation and service functions.

![](/images/PickupDropoff.gif)
---

## Table of Contents
- [Built With](#built-with)
- [SLAM](#slam)
- [Localization and Navigation](#localization-and-navigation)
- [Service Functions](#service-functions)
- [Results](#results)

---

## Built With
The project is built primarly on the following official ROS packages. 

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
First the Simultaneous Localization and Mapping (**SLAM**) is implemented from the ROS package [gmapping](http://wiki.ros.org/gmapping). This allows the robot to create a map and localize itself with help of the equipped laser range finder sensors and RGB-D camera. The turtlebot is planted into an environment without any prior knowledge of its environment.

![](/images/SLAM.gif)
![](/images/smallWorld.jpg?raw=false)
![](/images/2dmap.png?raw=false)

```javascript
./src/test_slam
```

## Localization and Navigation
The next goal for the robot is to find its way to a defined set of coordinates and orient itself with respect to them. This is the next step towards an autonomously pick-up and dropp-off service. This part is based on the previously implemented SLAM algorithm. The localisation is performed with the ROS Navigation stack, which is based on the Dijkstra algorithm, a variant of the **Uniform Cost Search** algorithm. With the help of the Adaptive Monte Carlo Localication (**AMCL**) the robot is able to localize itself.

![](/images/localization.png?raw=false)

```javascript
./src/test_slam
```

## Service Functions

Lastly two addional packages are created and integrated the *pick_objects* node and the *add_markers* node. The *add_marker* node is a virtual object that is picked up and delivered by the robot, thus it should first appear in its pickup zone, and then in its drop off zone once the robot reaches it. Therefore the *add_markers* node has to publish to the robot the position of the pick-up destination. The *pick_up node* is then commanding the robot where to move.

```javascript
./src/add_marker.sh
./src/pick_object.sh
```
![](/images/add_marker_pick_up.png?raw=false)

Lastly all nodes can be launched with the shell script *home_service.sh*

```javascript
./src/home_service.sh
```
