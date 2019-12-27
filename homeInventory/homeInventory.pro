#-----------------------------------------------------------------------------------------------------------------------------------
#
# PROJECT:            Home Inventory System
# FILE:								homeInventory.pro
# SUBSYSTEM:          Project File
# LANGUAGE:						C++
# TARGET OS:          LINUX
# LIBRARY DEPENDANCE:	None.
# NAMESPACE:          N/A
# AUTHOR:							Gavin Blakeman.
# LICENSE:            GPLv2
#
#                     Copyright 2019 Gavin Blakeman.
#                     This file is part of the homeInventory Project
#
#                     homeInventory is free software: you can redistribute it and/or modify it under the terms of the GNU
#                     General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
#                     your option) any later version.
#
#                     homeInventory is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
#                     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
#                     License for more details.
#
#                     You should have received a copy of the GNU General Public License along with homeInventory.  If not, see
#                     <http://www.gnu.org/licenses/>.
#
# OVERVIEW:						Project file for compiling the project
#
# HISTORY:            2019-12-27/GGB - Start Project
#
#-----------------------------------------------------------------------------------------------------------------------------------

TARGET = homeInventory.wt
TEMPLATE = app

QT += core
QT -= gui

CONFIG += console
CONFIG -= app_bundle
CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++17 -static -static-libgcc -DWT_CPP17_ANY_IMPLEMENTATION=std
DEFINES += BOOST_THREAD_USE_LIB QT_GUI_LIB QT_CORE_LIB

#OBJECTS_DIR = "objects"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH +=  \
  "/home/gavin/Documents/Projects/software/Library/Boost/boost_1_71_0"
#    "../ACL" \
#    "../GCL" \
#    "../MCL" \
#    "../PCL" \
#    "../SCL" \

#    "../cfitsio" \
#    "../LibRaw"
#    "../dlib-19.4" \
#    "../libWCS/wcstools-3.8.7/libwcs" \
#    "../NOVAS" \
#    "../SBIG" \
#    "../SOFA/src" \
#    "../GeographicLib/GeographicLib-1.48/include/GeographicLib"

SOURCES += \
  source/main.cpp \
    source/database/session.cpp \
    source/application.cpp \
    source/database/tbl_users.cpp \
    source/menuData.cpp \
    source/menuView.cpp \
    source/models/menuModel.cpp \
    source/transactionPages/housePage.cpp \
    source/transactionPages/roomPage.cpp \
    source/transactionPages/inventoryPage.cpp \
    source/widgets/inventoryWidget.cpp

LIBS += -L/usr/lib -lwt -lwthttp -lwtdbo -lwtdbomysql
LIBS += -L/usr/local/lib -lboost_system
LIBS += -L/usr/local/lib -lboost_filesystem
LIBS += -L/usr/local/lib -lboost_thread
LIBS += -L/usr/local/lib -lboost_program_options
#LIBS += -L../GCL -lGCL
#LIBS += -L../ACL -lACL
#LIBS += -L../SOFA -lSOFA

HEADERS += \
    include/database/session.h \
    include/database/database \
    include/database/databaseTables.h \
    include/application.h \
    include/database/tbl_users.h \
    include/transactions.h \
    include/transactionPages/transactionPage.h \
    include/menuData.h \
    include/menuView.h \
    include/models/menuModel.h \
    include/homeInventory.h \
    include/database/tbl_houses.h \
    include/database/tbl_rooms.h \
    include/database/tbl_inventory.h \
    include/database/tbl_documents.h \
    include/transactionPages/housePage.h \
    include/transactionPages/roomPage.h \
    include/transactionPages/inventoryPage.h \
    include/widgets/inventoryWidget.h


DISTFILES +=

STATECHARTS +=
