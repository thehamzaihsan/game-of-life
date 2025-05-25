# Install script for directory: /home/hamzaihsan/Desktop/DAA-PRJ/TGUI/gui-builder

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/applications" TYPE FILE FILES "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/gui-builder/tgui-gui-builder.desktop")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/48x48/apps" TYPE FILE FILES "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/cmake/gui-builder/TexusGUI.png")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder"
         RPATH "\$ORIGIN/../../../lib64:/usr/local/lib64")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE EXECUTABLE FILES "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/gui-builder/gui-builder")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder"
         OLD_RPATH "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/lib:/usr/local/lib64:"
         NEW_RPATH "\$ORIGIN/../../../lib64:/usr/local/lib64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder/gui-builder")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE DIRECTORY FILES "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/gui-builder/resources")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "gui-builder" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/tgui-1/gui-builder" TYPE DIRECTORY FILES "/home/hamzaihsan/Desktop/DAA-PRJ/TGUI/themes")
endif()

