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

#include "../../include/models/menuModel.h"

  // Standard C++ library header files.

#include <any>

  // homeInventory header files.

#include "../../include/menuData.h"

namespace models
{

  std::unique_ptr<Wt::WStandardItem> CMenuModel::createMenuItem(Wt::WString const &location,
                                                                transaction_t userData)
  {
    auto result = std::make_unique<Wt::WStandardItem>(location);
    if (userData != 0)
    {
      result->setData(userData, Wt::ItemDataRole::User);
    };

    return result;
  }


  /// @brief Creates the main menu for the application.
  /// @version 2019-12-27/GGB - Function created.

  void CMenuModel::populateMenu()
  {
    std::unique_ptr<Wt::WStandardItem> level1;
    std::unique_ptr<Wt::WStandardItem> level2;

    for(auto const &p : menuMap)
    {
      switch (p.second.menuLevel)
      {
        case 1:
        {
          if (level2)
          {
            level1->appendRow(std::move(level2));
          };
          if (level1)
          {
            appendRow(std::move(level1));
          };
          level1 = createMenuItem(p.second.menuText, p.first);
          break;
        };
        case 2:
        {
          if (level2)
          {
            level1->appendRow(std::move(level2));
          };
          level2 = createMenuItem(p.second.menuText, p.first);
          break;
        };
        case 3:
        {
          level2->appendRow(createMenuItem(p.second.menuText, p.first));
          break;
        };
      };
    };

    if (level2)
    {
      level1->appendRow(std::move(level2));
    };
    if (level1)
    {
      appendRow(std::move(level1));
    };

    setHeaderData(0, Wt::Orientation::Horizontal, std::string("Main Menu"));

  }

} // namespace models
