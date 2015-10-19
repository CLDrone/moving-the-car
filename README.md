# moving-the-car
moving the husky or a simplecar like an "8"

to spawn and control a husky car in mbzirc world, "roslaunch myhusky_gazebo husky_empty_world.launch world_name:=/home/robot/myworld_ws/src/myworld/robot_gazebo/worlds/robot_mbzirc.world"
then "rosrun robot_description car_cmd_vel_pub"

to spawn and control the simple car "roslaunch robot_gazebo gazebo.launch model:=$(rospack find robot_description)/urdf/robot1_base_04.xacro"
then "rosrun robot_description car_cmd_vel_pub"
