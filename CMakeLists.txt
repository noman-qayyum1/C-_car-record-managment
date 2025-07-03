cmake_minimum_required(VERSION 3.30)
project(FileManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -- ADDED: point to your MySQL installation paths --
# Example: if you installed MySQL to "C:\Program Files\MySQL\MySQL Server 8.0"
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")

add_executable(FileManager
        main.cpp
        DatabaseManager.cpp
        DatabaseManager.h
        DerivedEntity.cpp
        DerivedEntity.h
        Entity.cpp
        Entity.h
        FileManager.cpp
        FileManager.h
        SyncManager.cpp
        SyncManager.h
        UserInterface.cpp
        UserInterface.h
)

# -- ADDED: link MySQL (and WinSock on Windows) --
target_link_libraries(FileManager PRIVATE mysqlclient ws2_32)
