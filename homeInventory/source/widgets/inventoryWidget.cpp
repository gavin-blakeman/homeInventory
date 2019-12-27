//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                roomHierarchyWidget.cpp
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

#include "include/widgets/inventoryWidget.h"

  // Standard C++ library header files.

#include <cstdint>

  // Wt++ framework header files.

#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>

namespace  widgets
{
  /// @brief Constructor for the class.
  /// @param[in] parent: The Application that owns this object. (Needed for session)
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  CInventoryWidget::CInventoryWidget(CApplication *parent)
    : Wt::WContainerWidget(), parent_(parent), queryModelHouses(), queryModelRooms(), queryModelInventory(), selectionChanged_()
  {
    queryModelHouses = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>>();
    queryModelHouses->setQuery(parent_->session().find<database::tbl_houses>().where("RecordDeleted = false"));
    queryModelHouses->addColumn("Description");
    queryModelHouses->sort(0);

    queryModelRooms = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_rooms>>>();
    queryModelRooms->setQuery(parent_->session().find<database::tbl_rooms>().where("RecordDeleted = false"));
    queryModelRooms->addColumn("Description");
    queryModelRooms->sort(0);

    queryModelInventory = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_inventory>>>();
    queryModelInventory->setQuery(parent_->session().find<database::tbl_inventory>());
    queryModelInventory->addColumn("Description");
    queryModelInventory->sort(0);

    setupUI();
  }

  /// @brief Function called when the selection in the combo box is changed.
  /// @param[in] selectedItem: The newly selected item.
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryWidget::comboBoxChangedHouses(int selectedItem)
  {
    // Need to change the find on the model to get the relevant records only.

    try
    {
      Wt::Dbo::ptr<database::tbl_houses> houseID= queryModelHouses->resultRow(selectedItem);

      queryModelRooms->setQuery(parent_->session()
                                .find<database::tbl_rooms>()
                                .where("(RecordDeleted = false) AND (House_ID = ?)")
                                .bind(houseID), true);
      comboBoxRooms->setCurrentIndex(0);  // Set the current selection.
      comboBoxChangedRooms(0);            // Change the current search at the same time.
    }
    catch(Wt::Dbo::Exception &e)
    {
      std::cerr << e.what() << std::endl;
    };
  }

  /// @brief Function called when the selection in the combo box is changed.
  /// @param[in] selectedItem: The newly selected item.
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryWidget::comboBoxChangedRooms(int selectedItem)
  {
    try
    {
      Wt::Dbo::ptr<database::tbl_rooms> roomID = queryModelRooms->resultRow(selectedItem);
      queryModelInventory->setQuery(parent_->session()
                                    .find<database::tbl_inventory>()
                                    .where("Room_ID = ?")
                                    .bind(roomID.id()), true);
      tableViewInventory->refresh();
    }
    catch(Wt::Dbo::Exception &e)
    {
      std::cerr << e.what() << std::endl;
    };
  }

  /// @brief Function called by the tree view when a plant item selection changes.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryWidget::inventorySelectionChanged()
  {

    Wt::Dbo::ptr<database::tbl_inventory> inventoryItem =
        queryModelInventory->resultRow(tableViewInventory->selectedIndexes().begin()->row());
    selectionChanged_.emit(inventoryItem.id());
  }

  /// @brief Populates the plant item model
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryWidget::populateModel()
  {
    //plantRegisterModel->populateModel();
  }

  /// @brief Sets up the user interface.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryWidget::setupUI()
  {
    setMaximumSize(Wt::WLength::Auto, Wt::WLength::Auto);

    Wt::WGridLayout *gridLayout = setLayout(std::make_unique<Wt::WGridLayout>());

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Houses"), 0, 0);
    comboBoxHouses = gridLayout->addWidget(std::make_unique<Wt::WComboBox>(), 0, 1);
    comboBoxHouses->setNoSelectionEnabled(true);
    comboBoxHouses->setModel(queryModelHouses);
    comboBoxHouses->activated().connect(this, &CInventoryWidget::comboBoxChangedHouses);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Rooms"), 1, 0);
    comboBoxRooms = gridLayout->addWidget(std::make_unique<Wt::WComboBox>(), 1, 1);
    comboBoxRooms->setNoSelectionEnabled(true);
    comboBoxRooms->setModel(queryModelRooms);
    comboBoxRooms->activated().connect(this, &CInventoryWidget::comboBoxChangedRooms);

    tableViewInventory = gridLayout->addWidget(std::make_unique<Wt::WTableView>(), 2, 0, 1, 2);
    tableViewInventory->resize(width(), Wt::WLength::Auto);
    tableViewInventory->setModel(queryModelInventory);
    tableViewInventory->setSelectable(true);
    tableViewInventory->setAlternatingRowColors(true);
    tableViewInventory->setSelectionBehavior(Wt::SelectionBehavior::Rows);
    tableViewInventory->setSelectionMode(Wt::SelectionMode::Single);
    tableViewInventory->setColumnWidth(0, 200);
    tableViewInventory->selectionChanged().connect(this, &CInventoryWidget::inventorySelectionChanged);

    comboBoxHouses->setCurrentIndex(0);
    comboBoxChangedHouses(0);

    gridLayout->setRowStretch(2, 2);
    gridLayout->setColumnStretch(1, 2);

    setLayoutSizeAware(true);
  }
}
