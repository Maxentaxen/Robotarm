# Robot arm
This repository contains the code for the robot arm project
The idea of this project is to have a few servos that can control an arm to direct it to a specified point. 


## §1. The math
There's quite a bit of math going on in this project but here's where it will be explained.

### §1.1. The main equation
This equation is what the entire project is based upon. Solving it is what allows the program to find the angles
to put the servos into. \
\
$`
L_1\begin{bmatrix} \cos(\alpha_1) \\ \sin(\alpha_1) \end{bmatrix} + L_2\begin{bmatrix} \cos(\alpha_1 + \alpha_2) \\ \sin(\alpha_1 + \alpha_2) \end{bmatrix} = \begin{bmatrix} x \\ y \end{bmatrix} 
`$ 

\
where $`L_1, L_2`$ are the lenghts of the segments and
$`\alpha_1, \alpha_2`$ are the joint angles measured up from the plane that the previous segment lies on. 
Solving this equation is not that hard, it only requires some simply geometry and trigonometry and also on the fact that $\alpha_1+\alpha_2 = \tan^{-1}\left(\frac{y}{x}\right)$ which can be seen easily in a diagram.

### §1.2. Making it 3d
Finding joint angles in 2 dimensions is great and all but we want this to be able to move in 3d-space. This only really adds one step to the processing and it's not that complicated.\
The only thing needed is to convert the 3d-problem into a 2d-problem. This is accomplished by converting the target point's cartesian coordinates $(x, y, z)$ into cylindrical coordinates $(r, \theta, h)$ where r is the radial distance from the z-axis, $\theta$ is the angle about the z-axis and h is the height. This is achieved using the following equation:

$`\begin{bmatrix} 
              r \\ 
              \theta \\ 
              h 
  \end{bmatrix} =\begin{bmatrix} 
              \sqrt{x^2+y^2} \\
              \tan^{-1}\left(\frac{y}{x}\right) \\ 
              z \end{bmatrix}`$\
\
After that, we use our main equation using $(r,h)$ as our target point and then simply rotate the base to achieve the correct $\theta$.
 

## §2. Components
The user of the project must be able to input a point that the arm is to move to. There are two parts to this:

### §2.1. OLED-display
The project will have an OLED-display that will display 3 numbers which represent the target point that the arm will move to when the target is confirmed.

### §2.2. Potentiometers
In order for the user to change the target point there will be 3 potentiometers each corresponding to one coordinate of the target point. Alongside these there will be a button to confirm the target and at that point will joint angles be calculated and servor rotated.

### §2.3. Servo motors
Obviously, this project requires servos. 3 of them to be exact. These are of course used to rotate the arm into position.
