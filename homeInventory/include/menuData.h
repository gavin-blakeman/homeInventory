//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                application.h
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

#ifndef MENUDATA_H
#define MENUDATA_H

  // Standard C++ library header files.

#include <cstdint>
#include <map>
#include <utility>

// Wt framework header files

#include <Wt/Dbo/Session.h>

  // ReliabilityManager header files.

#include "transactions.h"

struct SMenuEntry
{
  transaction_t parentID;
  std::string   menuText;
  bool          selectable;
  std::uint8_t  menuLevel;
};

extern std::map<transaction_t, SMenuEntry> menuMap;


#endif // MENUDATA_H
