//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                housePage.h
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

#include "include/transactionPages/housePage.h"

  // Standard C++ library header files

#include <utility>

  // Wt framework header files.

#include <Wt/WAbstractItemModel.h>
#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WMessageBox.h>
#include <Wt/WRegExpValidator.h>
#include <Wt/WText.h>
#include <Wt/WEnvironment.h>
#include <Wt/WToolBar.h>
#include <Wt/Dbo/QueryModel.h>
#include <Wt/WContainerWidget.h>

  // homeInventory header files

#include <include/database/database>
#include "../../include/application.h"
//#include "../../include/dialogs/dialogBusinessUnit.h"

namespace transactions
{

  /// @brief Constructor for the class.
  /// @param[in] parent: The parent object.
  /// @version 2019-12-27/GGB - Function created.

  CHousePage::CHousePage(CApplication *parent) : CTransactionPage(parent)
  {

  }

  /// @brief Factory function for the class.
  /// @param[in] parent: The application that owns the class.
  /// @throws std::bad_alloc
  /// @version 2019-12-27/GGB - Function created.

  std::unique_ptr<CTransactionPage> CHousePage::createClass(CApplication *parent)
  {
    return std::make_unique<CHousePage>(parent);
  }

  /// @brief Creates the UI for the business unit view transaction.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CHousePage::createPage()
  {
    std::unique_ptr<Wt::WPushButton> newButton;

    Wt::WContainerWidget *container = parent()->getRightContainer();

    Wt::WToolBar *toolbar = container->addNew<Wt::WToolBar>();

      // Create push button.

    newButton = std::make_unique<Wt::WPushButton>("Create");
    newButton->setToolTip("Create a new House Record.");
    pushButtonCreate = newButton.get();
    pushButtonCreate->clicked().connect(this, &CHousePage::pushButtonCreateClicked);
    toolbar->addButton(std::move(newButton));

      // Edit push button.

    newButton = std::make_unique<Wt::WPushButton>("Edit");
    newButton->setEnabled(false);
    newButton->setToolTip("Edit the selected House Record");
    pushButtonEdit = newButton.get();
    toolbar->addButton(std::move(newButton));

      // Delete push button

    newButton = std::make_unique<Wt::WPushButton>("Delete");
    newButton->setEnabled(false);
    newButton->setToolTip("Delete an the selected House Record");
    pushButtonDelete = newButton.get();
    pushButtonDelete->clicked().connect(this, &CHousePage::pushButtonDeleteClicked);
    toolbar->addButton(std::move(newButton));

    toolbar->setOrientation(Wt::Orientation::Horizontal);

    try
    {
      auto queryModel = std::make_unique<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>>();
      queryModel->setQuery(parent()->session().find<database::tbl_houses>());
      queryModel->addColumn("Description");
      queryModel->addColumn("Address");

      std::unique_ptr<Wt::WTableView> tableView = std::make_unique<Wt::WTableView>();
      tableView->resize(Wt::WLength::Auto, Wt::WLength::Auto);
      tableView->setModel(std::move(queryModel));
      tableView->setAlternatingRowColors(true);
      tableView->setSelectionMode(Wt::SelectionMode::Single);
      tableView->setSelectionBehavior(Wt::SelectionBehavior::Rows);
      tableView->setSortingEnabled(false);
      tableView->selectionChanged().connect(this, &CHousePage::tableViewHousesSelectionChanged);
      tableViewHouses = tableView.get();

      container->addWidget(std::move(tableView));
    }
    catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    };
  }

  /// @brief Responds to the create push button being pressed. Opens the dialog to create.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CHousePage::pushButtonCreateClicked()
  {
    //addChild(std::make_unique<dialogs::CBusinessUnit>(parent_, this, dialogUsage));
  }

  /// @brief Handles the deletion button press.
  /// @version 2019-12-27/GGB - Function created.

  void CHousePage::pushButtonDeleteClicked()
  {
    Wt::WModelIndexSet selectedRow = tableViewHouses->selectedIndexes();    // Only 1 value should be returned.

    auto messageBox = addChild(std::make_unique<Wt::WMessageBox>("Confirm Delete",
                                                                 "<p>Delete the Business Unit</p>",
                                                                 Wt::Icon::Information,
                                                                 Wt::StandardButton::Yes | Wt::StandardButton::No));
    messageBox->setModal(true);

    messageBox->buttonClicked().connect([=]
    {
      if (messageBox->buttonResult() == Wt::StandardButton::Yes)
      {
        Wt::Dbo::Transaction transaction{parent_->session()};

        Wt::Dbo::ptr<database::tbl_houses> toDelete =
            std::dynamic_pointer_cast<Wt::Dbo::QueryModel<
            Wt::Dbo::ptr<database::tbl_houses>>>(tableViewHouses->model())->resultRow(selectedRow.begin()->row());

        toDelete.remove();
        refreshTableView();
      };
      removeChild(messageBox);
    });

    messageBox->show();
  }

  /// @brief Responds to a selection change.
  /// @version 2019-12-27/GGB - Function created.

  void CHousePage::tableViewHousesSelectionChanged()
  {
    if (!tableViewHouses->selectedIndexes().empty())
    {
      pushButtonEdit->setEnabled(true);
      pushButtonDelete->setEnabled(true);
    }
    else
    {
      pushButtonEdit->setEnabled(false);
      pushButtonDelete->setEnabled(false);
    };
  }

  /// @brief Function called to refresh the data in the table view after a change.
  /// @version 2019-12-27/GGB - Function created.

  void CHousePage::refreshTableView()
  {
    std::dynamic_pointer_cast<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>>(tableViewHouses->model())->reload();
    tableViewHouses->refresh();
  }

} // namespace transactions
