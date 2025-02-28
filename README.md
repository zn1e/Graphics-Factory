## Setting up VSCode in WSL for Computer Graphics Lab

## Install g++ compiler (for C++)
- Run the cmd `sudo apt install g++`.
## Installing CMake 
- There are instances CMake extensions in VSCode doesn't show up when using WSL. <br>
Run the command `sudo apt install cmake`.
### Install OpenGL development libraries and GLUT
- Now we have to install the OpenGL and GLUT libraries. <br>
Enter `sudo apt install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev` and `sudo apt install freeglut3-dev libglfw3-dev`.
### Compiling file
- It is recommended to include `-Wall -Werror` to avoid compiling issuess. <br>
`g++ -Wall -Werror <program>.cpp -o <desired_name>`.
