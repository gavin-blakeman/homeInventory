//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                inventory.cpp
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

#include "include/transactionPages/inventoryPage.h"

  // Standard C++ library header files

#include <algorithm>
#include <map>
#include <utility>

  // Wt framework header files.

#include <Wt/WGridLayout.h>
#include <Wt/WLabel.h>
#include <Wt/WTableView.h>
#include <Wt/WToolBar.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/Transaction.h>

  // homeInventory Manager header files

#include "../../include/application.h"

namespace transactions
{

  /// @brief Constructor for the class.
  /// @param[in] parent: The parent object.
  /// @version 2019-12-27/GGB - Function created.

  CInventoryPage::CInventoryPage(CApplication *parent) : CTransactionPage(parent)
  {

  }

  /// @brief Creates the UI for the operating unit view transaction.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryPage::createPage()
  {
    std::unique_ptr<Wt::WPushButton> newButton;

    try
    {
      Wt::WContainerWidget *container = parent()->getRightContainer();

      std::unique_ptr<Wt::WGridLayout> gridLayout = std::make_unique<Wt::WGridLayout>();

      inventoryWidget = gridLayout->addWidget(std::make_unique<widgets::CInventoryWidget>(parent_), 0, 0, 10, 1);
      inventoryWidget->selectionChanged().connect(this, &CInventoryPage::inventoryItemChanged);

      Wt::WToolBar *toolbar = gridLayout->addWidget(std::make_unique<Wt::WToolBar>(), 0, 1);

        // Edit button.

      newButton = std::make_unique<Wt::WPushButton>("Edit");
      newButton->clicked().connect(this, &CInventoryPage::pushButtonEditClicked);
      newButton->setEnabled(false);
      pushButtonEdit = newButton.get();
      toolbar->addButton(std::move(newButton));

        // Create button.

      newButton = std::make_unique<Wt::WPushButton>("Create");
      newButton->setEnabled(false);
      pushButtonCreate = newButton.get();
      toolbar->addButton(std::move(newButton));

        // Delete button.

      newButton = std::make_unique<Wt::WPushButton>("Delete");
      newButton->clicked().connect(this, &CInventoryPage::pushButtonDeleteClicked);
      newButton->setEnabled(false);
      pushButtonDelete = newButton.get();
      toolbar->addButton(std::move(newButton));

        // Upload button.

      newButton = std::make_unique<Wt::WPushButton>("Upload");
      newButton->setEnabled(false);
      toolbar->addButton(std::move(newButton));

        // Audit Button

      newButton = std::make_unique<Wt::WPushButton>("Audit");
      newButton->setEnabled(false);
      toolbar->addButton(std::move(newButton));

      toolbar->setOrientation(Wt::Orientation::Horizontal);

      gridLayout->addWidget(createRecordContainer(), 1, 1);

      gridLayout->setRowStretch(1, 2);
      gridLayout->setColumnStretch(1, 2);
      gridLayout->setColumnResizable(0);

      container->setLayout(std::move(gridLayout));
    }
    catch (std::exception &e)
    {
      std::cerr << "exception: " << e.what() << std::endl;
    };
  }

  /// @brief Responds to an item selection in the tree being changed.
  /// @details Lookup the required information based on the plantRegisterID that is being passed to this function.
  ///          initially all data is in a display only state.
  /// @throws
  /// @version 2019-12-27/GGB - Function created

  void CInventoryPage::inventoryItemChanged(std::int32_t inventoryID)
  {
      // Capture the information from the tbl_inventory

    {
      Wt::Dbo::Transaction transaction {parent()->session() };

      Wt::Dbo::ptr<database::tbl_inventory> inventoryItem = parent()->session()
                                                            .find<database::tbl_inventory>()
                                                            .where("ID = ?").bind(inventoryID);
      lineEditDescription ->setText(inventoryItem->description);
      dateEditPurchaseDate->setValueText(inventoryItem->purchaseDate);
      spinBoxQuantity->setValue(inventoryItem->quantity);
      //lineEditPurchasePrice->setText(inventoryItem->purchasePrice);
      lineEditManufacturer->setText(inventoryItem->manufacturer);
      lineEditSerialNumber->setText(inventoryItem->serialNumber);
      lineEditSupplier->setText(inventoryItem->supplier);
      lineEditModelNumber->setText(inventoryItem->modelNumber);
      lineEditInvoiceNumber->setText(inventoryItem->invoiceNumber);
      textAreaComments->setText(inventoryItem->comments);
    };

    inventoryID_ = inventoryID;
  }

  /// @brief Responds to the delete push button being clicked.
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryPage::pushButtonDeleteClicked()
  {
  }

  /// @brief Responds to the edit push button being clicked.
  /// @version 2019-12-27/GGB - Function created.

  void CInventoryPage::pushButtonEditClicked()
  {
  }

  /// @brief Creates the record area of the UI.
  /// @throws std::bad_alloc
  /// @version 2019-12-27/GGB - Function created.

  std::unique_ptr<Wt::WContainerWidget> CInventoryPage::createRecordContainer()
  {
    int row = 0;

    std::unique_ptr<Wt::WContainerWidget> containerWidget = std::make_unique<Wt::WContainerWidget>();
    Wt::WGridLayout *gridLayout = containerWidget->setLayout(std::make_unique<Wt::WGridLayout>());

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Description"), row, 0);
    lineEditDescription = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 1);
    lineEditDescription->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Purchase Date"), row, 2);
    dateEditPurchaseDate = gridLayout->addWidget(std::make_unique<Wt::WDateEdit>(), row, 3);
    dateEditPurchaseDate->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Quantity"), ++row, 0);
    spinBoxQuantity = gridLayout->addWidget(std::make_unique<Wt::WSpinBox>(), row, 1);
    spinBoxQuantity->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Purchase Price"), row, 2);
    lineEditPurchasePrice = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 3);
    lineEditPurchasePrice->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Manufacturer"), ++row, 0);
    lineEditManufacturer = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 1);
    lineEditManufacturer->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Serial Number"), row, 2);
    lineEditSerialNumber = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 3);
    lineEditSerialNumber->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Supplier"), ++row, 0);
    lineEditSupplier = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 1);
    lineEditSupplier->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Model Number"), row, 2);
    lineEditModelNumber = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 3);
    lineEditModelNumber->setEnabled(false);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Invoice Number"), ++row, 0);
    lineEditInvoiceNumber = gridLayout->addWidget(std::make_unique<Wt::WLineEdit>(), row, 1);
    lineEditInvoiceNumber->setEnabled(false);
    pushButtonInvoice = gridLayout->addWidget(std::make_unique<Wt::WPushButton>("Invoice"), row, 2);

    gridLayout->addWidget(std::make_unique<Wt::WLabel>("Comments"), ++row, 0);
    textAreaComments = gridLayout->addWidget(std::make_unique<Wt::WTextArea>(), row, 1, 1, 3);
    textAreaComments->setEnabled(false);

    gridLayout->setRowStretch(row, 2);
    gridLayout->setColumnStretch(4, 2);

    return std::move(containerWidget);
  }


} // namespace transactions
