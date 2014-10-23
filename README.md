Dumping depth images to the disk using ROS
=====================

This is an example of how to write a ros node, which listens to the topic `/X1/depth/image_raw`, which stores the depth information from the AsusXtion camera.
The code also extract the images via cvBridge and dumps the images to the disk using OpenCV functions.

Note: The file was originally created to work on the ros-hydro, that is why the OpenCV is included as a stand alone library in the `CMakeLists.txt` file

To make the code work:

1. Create a ros package (e.g `extract_depth`) inside the catkin workspace using `catkin_create_pkg`
2. mkdir `src/` in folder `extract_depth`
3. run `catkin_make` in catkin workspace
After this step the executable `extract_depth_node` will appear in a folder corresponding to the package name in the catkin workspace in the `devel` section.

4. `rosrun extract_depth extract_depth_node` to use the node
