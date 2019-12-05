cmake_minimum_required(VERSION 3.13)
project(DataCentersManager)

set(CMAKE_CXX_STANDARD 11)

#add_executable(untitled main.cpp linkedList.h DataCenter.h DataManagerExceptions.h  "Data Structures/AVLTree/AVLTree.h" TreesTest.cpp "Data Structures/Queue.cpp" "Data Structures/Queue.h")
#add_executable(untitled linkedList.h AuxDataCenter.h DataCenter.h DataManagerExceptions.h "Data Structures/AVLTree/AVLTree.h" "Data Structures/AVLTree/BinarySearchTree.h" TreesTest.cpp DataCenterManager.h DataManagerExceptions.h)
#add_executable(untitled main.cpp linkedList.h DataCenter.h DataManagerExceptions.h "Data Structures/AVLTree/AVLTree.h")
add_executable(untitled TreesTest.cpp DataCenterManager.h AuxDataCenter.h DataCenter.h linkedList.h "Data Structures/AVLTree/AVLTree.h" "Data Structures/Array.h" "Data Structures/AVLTree/BinarySearchTree.h" "Data Structures/AVLTree/BinaryTree.h"  "Data Structures/Array.h" DataManagerExceptions.h)