//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                roomPage.h
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

#include "include/transactionPages/roomPage.h".h"

  // Standard C++ library header files

#include <utility>

  // Wt framework header files.

#include <Wt/WGridLayout.h>
#include <Wt/WTableView.h>
#include <Wt/WToolBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>

  // homeInventory header files

#include "../../include/application.h"

namespace transactions
{

  /// @brief Constructor for the class.
  /// @param[in] parent: The parent object.
  /// @version 2019-12-27/GGB - Function created.

  CRoomPage::CRoomPage(CApplication *p) : CTransactionPage(p)
  {
    queryModelHouses = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>>();
    queryModelHouses->setQuery(parent()->session().find<database::tbl_houses>().where("RecordDeleted = false"));
    queryModelHouses->addColumn("Description");

    queryModelRooms = std::make_shared<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_rooms>>>();
    queryModelRooms->setQuery(parent()->session().find<database::tbl_rooms>().where("(House_ID = 0) AND (RecordDeleted = false)"));
    queryModelRooms->addColumn("Description");
    queryModelRooms->addColumn("RecordDeleted");
    queryModelRooms->sort(0);
  }

  /// @brief Function called when the selection in the combo box is changed.
  /// @param[in] selectedItem: The newly selected item.
  /// @version 2019-12-27/GGB - Function created.

  void CRoomPage::comboBoxChanged(int selectedItem)
  {

      // Need to change the find on the model to get the relevant records only.

    try
    {
      Wt::Dbo::ptr<database::tbl_houses> house = queryModelHouses->resultRow(selectedItem);
      queryModelRooms->setQuery(parent()->session().find<database::tbl_rooms>().where("(House_ID = ?) AND (RecordDeleted = false)").
                                bind(house), true);
    }
    catch(Wt::Dbo::Exception &e)
    {
      std::cerr << e.what() << std::endl;
    };
  }

  /// @brief Factory function for the class.
  /// @param[in] parent: The application that owns the class.
  /// @throws std::bad_alloc
  /// @version 2019-12-27/GGB - Function created.

  std::unique_ptr<CTransactionPage> CRoomPage::createClass(CApplication *parent)
  {
    return std::make_unique<CRoomPage>(parent);
  }

  /// @brief Creates the UI for the operating unit view transaction.
  /// @version 2019-12-27/GGB - Function created.

  void CRoomPage::createPage()
  {
    try
    {
      Wt::WContainerWidget *container = parent()->getRightContainer();

      std::unique_ptr<Wt::WGridLayout> layout = std::make_unique<Wt::WGridLayout>();

      Wt::WToolBar *toolbar = layout->addWidget(std::make_unique<Wt::WToolBar>(), 0, 0, 1, 2);
      toolbar->addButton(std::make_unique<Wt::WPushButton>("Edit"));
      toolbar->addButton(std::make_unique<Wt::WPushButton>("Create"));
      toolbar->addButton(std::make_unique<Wt::WPushButton>("Delete"));
      toolbar->addButton(std::make_unique<Wt::WPushButton>("Upload"));
      toolbar->setOrientation(Wt::Orientation::Horizontal);

        // Create the combobox and assign the model to the combo box.

      auto text = layout->addWidget(std::make_unique<Wt::WText>("Houses"), 1, 0);
      text->setStyleClass("Wt-outset");
      comboBoxHouses = layout->addWidget(std::make_unique<Wt::WComboBox>(), 1, 1);
      comboBoxHouses->setNoSelectionEnabled(true);
      comboBoxHouses->setWidth(50);
      comboBoxHouses->setModel(queryModelHouses);
      comboBoxHouses->activated().connect(this, &CRoomPage::comboBoxChanged);

        // Create the table view.

      tableViewRooms = layout->addWidget(std::make_unique<Wt::WTableView>(), 2, 0, 1, 2);
      tableViewRooms->resize(Wt::WLength::Auto, Wt::WLength::Auto);
      tableViewRooms->setModel(queryModelRooms);
      tableViewRooms->setAlternatingRowColors(true);
      tableViewRooms->setSelectionMode(Wt::SelectionMode::Single);
      tableViewRooms->setSelectionBehavior(Wt::SelectionBehavior::Rows);
      tableViewRooms->setSortingEnabled(false);

      layout->setRowStretch(2, 2);
      layout->setColumnStretch(2, 2);

      container->setLayout(std::move(layout));
    }
    catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    };

  }

} // namespace transactions
