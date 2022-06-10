# Robotic-Arm-Pick-n-Drop-Simulator
The project is created using C++ and OpenGL.

This project shows the simulation of the Robotic Arm whose perspective view is controlled by arrow keys. The robot arm is specified by (1) the angle that the upper arm makes relative to the x-axis, called shoulderAngle, and (2) the angle that the lower arm makes relative to the upper arm, called elbowAngle. All the movements between upper and lower arm are carried through the specific keyboard keys. The robotic arm can also pick a ball from the specified location and then drop it at a specified location (basket).

# How to control the robotic arm?

| Keys          | Function      | Direction  |
| ------------- |:-------------:| -----:|
| ➡ , ⬅ , ⬆ , ⬇ | Move the Camera | - |
|<kbd> Q </kbd>|Rotate Shoulder section about Y axis|Anti-clockwise|
|<kbd> A </kbd>|Rotate Shoulder section about Y axis|Clockwise|
|<kbd> W </kbd>|Rotate Shoulder section about Z axis|Anti-clockwise|
|<kbd> S </kbd>|Rotate Shoulder section about Z axis|Clockwise|
|<kbd> E </kbd>|Rotate Elbow section about Z axis|Anti-clockwise|
|<kbd> D </kbd>|Rotate Elbow section about Z axis|Clockwise|
|<kbd> R </kbd>|Rotate Wrist section about X axis|Anti-clockwise|
|<kbd> F </kbd>|Rotate Wrist section about X axis|Clockwise|
|<kbd> T </kbd>|Rotate Wrist section about Z axis|Anti-clockwise|
|<kbd> G </kbd>|Rotate Wrist section about Z axis|Clockwise|
|<kbd> home </kbd>|Pick up the ball|-|
|<kbd> end </kbd>|Drop the ball |-|

Some constraints have been applied on the rotation angles of the various sections to mimic a human hand

# Video Demonstration
Here is a [Link](https://youtu.be/eqiJBn5vmX4) for the Video Demonsration of the arm in action.
