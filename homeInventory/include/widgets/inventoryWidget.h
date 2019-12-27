//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                roomHierarchyWidget.h
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

#ifndef ROOMHIERARCHYWIDGET_H
#define ROOMHIERARCHYWIDGET_H

  // Standard C++ library header files

#include <memory>

  // Wt++ framework header files

#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WSignal.h>
#include <Wt/WTableView.h>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/QueryModel.h>

  // Miscellaneous library header files.

  // homeInventory header files

#include "include/application.h"
#include "include/database/database"

namespace widgets
{
  class CInventoryWidget : public Wt::WContainerWidget
  {
  private:
    CApplication *parent_ = nullptr;

    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>> queryModelHouses;
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_rooms>>> queryModelRooms;
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_inventory>>> queryModelInventory;

    Wt::WComboBox *comboBoxHouses = nullptr;
    Wt::WComboBox *comboBoxRooms = nullptr;
    Wt::WTableView *tableViewInventory = nullptr;

    Wt::Signal<std::int32_t> selectionChanged_;

    void setupUI();

  protected:
    void comboBoxChangedHouses(int);
    void comboBoxChangedRooms(int);

  public:
    CInventoryWidget(CApplication *);

    void populateModel();

      // Slots

    void inventorySelectionChanged();

      // Signals

    Wt::Signal<std::int32_t> &selectionChanged() { return selectionChanged_; }

  };
}

#endif // PLANTHIERARCHYCONTAINER_H
