# GEANT4-muonCargo
* This repository is used for uploading the GEANT4 code for the cargo detection project, HK cluster, 2024.
* The code include:
1. Define a 3D cartesian geometry
2. 


# GEANT 4 installation and tutorial
* Pre-installation (Linux only):
```sh
sudo apt install cmake cmake-curses-gui gcc g++ libexpat1-dev libxmu-dev libmotif-dev qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools
```
* Please reflect to the instruction in the german boi series https://www.youtube.com/watch?v=4DTumUo3IKw&t=2s

# Simulation code in the project
* Download the code
```sh
git clone https://github.com/Tony1022/GEANT4-muonCargo.git
```
* CMake is required to compile the code
```sh
cd <path/to/GEANT4-muonCargo>
mkdir build
cd build
cmake ..
make
```
* Test the code
```sh
./sim
```
If your GEANT4 is installed properly, you will see a UI that have a cartesian coordinate system, a purple plate and parallel plates aligned parallelly in red and green.

# Author
Tony Kwok Ching Cheung
