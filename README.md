## Setting up VSCode in WSL for Computer Graphics Lab

## Install g++ compiler (for C++)
- Run the cmd `sudo apt install g++`.
## Installing CMake 
- There are instances CMake extensions in VSCode doesn't show up when using WSL. <br>
Run the command `sudo apt install cmake`.
### Install OpenGL development libraries and GLUT
- Now we have to install the OpenGL and GLUT libraries. <br>
Enter `sudo apt install libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev` and `sudo apt install freeglut3-dev libglfw3-dev`.
### Running CMake via terminal
- We need to create first a directory for build and then execute those files. <br>
`mkdir build` <br>
`cd build`
- Then we can chain commands configure-compile-run (you can find executable name in *CMakeLists.txt*). <br>
`cmake .. && make && ./<name_of_executable`.

### Compiling file
- It is recommended to include `-Wall -Werror` to avoid compiling issuess. <br>
`g++ -Wall -Werror <program>.cpp -o <desired_name>`.
