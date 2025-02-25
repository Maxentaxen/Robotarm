# Robot arm
This repository contains the code for the robot arm project

## Main idea
The idea of this project is to have a few servos that can control an arm to direct it to a specified point. There's a lot of math involved in this but put simply, the two most important equations are: \
\
\
 $`
 L_1\begin{bmatrix} \cos{\alpha_1} \\ \sin{\alpha_1} \end{bmatrix} + L_2\begin{bmatrix} \cos{\alpha_2} \\ \sin{\alpha_2} \end{bmatrix} + L_3\begin{bmatrix} \cos{\alpha_3} \\ \sin{\alpha_3} \end{bmatrix} = \begin{bmatrix} x \\ y \end{bmatrix} 
 `$ \
 \
 where $`L_1, L_2, L_3`$ are the lenghts of the segments and
 $`\alpha_1, \alpha_2, \alpha_3`$ are the joint angles measured up from the xy-plane. This equation, along with some other things, is how the servo angles are found.
 \
 \
 $`P = \begin{bmatrix} L_1\cos{\alpha_1} + L_2\cos{\alpha_2} + L_3\cos{\alpha_3} \\ 
                              L_1\sin{\alpha_1} + L_2\sin{\alpha_2} + L_3\sin{\alpha_3} \\ 0\end{bmatrix} \cdot \begin{bmatrix} \cos{\theta} & -\sin{\theta} & 0 \\ \sin{\theta} & cos{\theta} & 0 \\ 0 & 0 & 1 \end{bmatrix} `$ \

where $\theta$ is the angle of the base around the z-axis. This equation will be used to find the position of the arm's endpoint.\
\
The rest of the math is mostly basic linear algebra.
