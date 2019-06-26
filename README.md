# amdCTRL

amdCTRL is a program for overclocking the AMD Radeon VII under Linux.
![Alt text](/screenshot.png?raw=true)
## Getting Started

### Download the newest stable relase
Prebuilt Linux binaries are available through the [git releases page](https://github.com/xhighway999/amdCTRL/releases).

### Building it yourself

Start by cloning this project by opening a terminal and typing
```
git clone --recurse-submodules https://github.com/xhighway999/amdCTRL.git
```
Create a new Folder and name it build
```
mkdir build
```
Cd into that folder and run cmake
```
cd build && cmake -G "Ninja" ../
```
Build the Project
```
ninja
```
Done ! The binary is located under build/AmdCtrl.
## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

