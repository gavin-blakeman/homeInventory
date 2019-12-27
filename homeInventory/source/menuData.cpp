//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                application.cpp
// SUBSYSTEM:
// LANGUAGE:						C++
// TARGET OS:           LINUX
// LIBRARY DEPENDANCE:	None.
// NAMESPACE:           N/A
// AUTHOR:							Gavin Blakeman.
// LICENSE:             GPLv2
//
//                      Copyright 2019 Gavin Blakeman.
//                      This file is part of the homeInventory Project
//
//                      homeInventory is free software: you can redistribute it and/or modify it under the terms of the GNU
//                      General Public License as published by the Free Software Foundation, either version 2 of the License, or (at
//                      your option) any later version.
//
//                      homeInventory is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
//                      even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
//                      Public License for more details.
//
//                      You should have received a copy of the GNU General Public License along with homeInventory.  If not,
//                      see <http://www.gnu.org/licenses/>.
//
// OVERVIEW:
//
// HISTORY:             2019-12-27/GGB - File Created.
//
//**********************************************************************************************************************************

#include "../include/menuData.h"

  // Wt framework header files

#include <Wt/Dbo/collection.h>
#include <Wt/Dbo/Query.h>
#include <Wt/Dbo/Transaction.h>

  // homeInventory header files.

std::map<transaction_t, SMenuEntry> menuMap =
{
  {TC::IP000, {0,         "House Management",                   true, 1}},
  {TC::MS000, {0,         "Room Management",                    true, 1}},
  {TC::RS000, {0,         "Inventory Management",               true, 1}},
  {TC::MT000, {0,         "Move Houses",                        false, 1}},
  {TC::AD000, {0,         "User Data",                          false, 1}},
};
