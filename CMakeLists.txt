<<<<<<< HEAD
cmake_minimum_required(VERSION 3.16)
project(RemoteLabMonitor)

set(CMAKE_CXX_STANDARD 17)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

# Enable MOC, UIC, RCC processing automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add server executable
add_executable(server
    src/server/server.cpp
)

target_link_libraries(server Qt6::Core Qt6::Network)

# Add client executable
add_executable(client
    src/client/main.cpp
    src/client/monitorwindow.cpp
    src/client/monitorwindow.h   # <- INCLUDE the header too
)

=======
cmake_minimum_required(VERSION 3.16)
project(RemoteLabMonitor)

set(CMAKE_CXX_STANDARD 17)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets)

# Enable MOC, UIC, RCC processing automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Add server executable
add_executable(server
    src/server/server.cpp
)

target_link_libraries(server Qt6::Core Qt6::Network)

# Add client executable
add_executable(client
    src/client/main.cpp
    src/client/monitorwindow.cpp
    src/client/monitorwindow.h   # <- INCLUDE the header too
)

>>>>>>> 14004d4a11d532f04bc6014b562f87398d2874ae
target_link_libraries(client Qt6::Core Qt6::Widgets Qt6::Network)