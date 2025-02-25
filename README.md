# Robot arm
This repository contains the code for the robot arm project

## Main idea
The idea of this project is to have a few servos that can control an arm to direct it to a specified point. 


## The math
There's a lot of math involved in this but put simply, the main equation that is being solved is: 
$`
L_1\begin{bmatrix} \cos(\alpha_1) \\ \sin(\alpha_1) \end{bmatrix} + L_2\begin{bmatrix} \cos(\alpha_1 + \alpha_2) \\ \sin(\alpha_1 + \alpha_2) \end{bmatrix} = \begin{bmatrix} x \\ y \end{bmatrix} 
`$ 
 
\
where $`L_1, L_2`$ are the lenghts of the segments and
$`\alpha_1, \alpha_2`$ are the joint angles measured up from the plane that the previous segment lies on. 
This equation technically has two solutions (one where the arm looks concave and another where it's convex) but we will only consider one. \
\
This gets slighly more complicated when considering putting the whole thing in 3d-space but has quite a simple solution.
The way to go about this is to convert the cartesian coordinates $`(x,y,z)`$ into cylindrical coordinates $`(r,h,\theta)`$ where r is the distance from the z-axis, h is the vertical distance from the xy-plane and $\theta$ is the angle measured counterclockwise from the positive x-axis.
 

## Input

The user is intended to input a target point through an OLED-screen with 3 potentiometers that control the x, y and z coordinates of the target point along with a "confirm" button that will disable the potentiometers and move the arm into position.
