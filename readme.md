# RCS_Pinger
App that periodically pings network nodes from predefined lists

Uses wxWidgets, wxFormBuilder and CMake.

To build
1. Clone the repo
3. make a build folder in the root
4. from the build folder run ```cmake ..```

There are several predefined Sites in the source code.
Each site is a list of IPs and a Name.
Modify as required.

Features to add:
1. Read sites from a text file
2. Run a network discovery based on a subnet input (like 192.168.1.0/24)

