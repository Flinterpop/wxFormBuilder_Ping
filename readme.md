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

### UI Builder
There is a file called `RCS_PingBuilder.fbp` that is used by wxFormBuilder to generate code for the UI.

Features to add:
1. Read sites from a text file
2. Run a network discovery based on a subnet input (like 192.168.1.0/24)

   
<img width="1510" height="1096" alt="image" src="https://github.com/user-attachments/assets/9a36d31f-87c6-4697-a2d0-421ccd94f7fb" />



