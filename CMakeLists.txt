cmake_minimum_required(VERSION 3.5)

project(RFID_Work LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Sql Network REQUIRED)

if(ANDROID)
  add_library(RFID_Work SHARED
          main.cpp
          Src/Main.cpp
          Src/Main.h
          Src/Main.ui
          Src/MyTCP.cpp
          Src/MyTCP.h
          Src/MySQL_X.cpp
          Src/MySQL_X.h
          UI/Login.cpp
          UI/Login.h
          UI/Login.ui
          UI/Registered.cpp
          UI/Registered.h
          UI/Registered.ui
  )
else()
  add_executable(RFID_Work
          main.cpp
          Src/Main.cpp
          Src/Main.h
          Src/Main.ui
          Src/MyTCP.cpp
          Src/MyTCP.h
          Src/MySQL_X.cpp
          Src/MySQL_X.h
          UI/Login.cpp
          UI/Login.h
          UI/Login.ui
          UI/Registered.cpp
          UI/Registered.h
          UI/Registered.ui
  )
endif()

target_link_libraries(RFID_Work PRIVATE Qt5::Widgets Qt5::Sql Qt5::Network)
