//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                inventory.h
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

#ifndef INVENTORYPAGE_H
#define INVENTORYPAGE_H

  // Standard C++ library header files

#include <memory>

  // Wt framework header files.

#include <Wt/WComboBox.h>
#include <Wt/WDateEdit.h>
#include <Wt/WLineEdit.h>
#include <Wt/WSpinBox.h>
#include <Wt/WStandardItemModel.h>
#include <Wt/WString.h>
#include <Wt/WTableView.h>
#include <Wt/Dbo/Dbo.h>

  // homeInventory Manager header files.

#include <include/database/database>
#include "transactionPage.h"
#include "include/widgets/inventoryWidget.h"

namespace transactions
{

  class CInventoryPage: public CTransactionPage
  {
  private:
    std::int32_t inventoryID_ = 0;

    widgets::CInventoryWidget *inventoryWidget = nullptr;

    Wt::WLineEdit *lineEditDescription = nullptr;
    Wt::WDateEdit *dateEditPurchaseDate = nullptr;
    Wt::WSpinBox *spinBoxQuantity = nullptr;
    Wt::WLineEdit *lineEditPurchasePrice = nullptr;
    Wt::WLineEdit *lineEditManufacturer = nullptr;
    Wt::WLineEdit *lineEditSerialNumber = nullptr;
    Wt::WLineEdit *lineEditSupplier = nullptr;
    Wt::WLineEdit *lineEditModelNumber = nullptr;
    Wt::WLineEdit *lineEditInvoiceNumber = nullptr;
    Wt::WPushButton *pushButtonInvoice = nullptr;
    Wt::WTextArea *textAreaComments = nullptr;

    Wt::WPushButton *pushButtonAuditHistory = nullptr;
    Wt::WPushButton *pushButtonEdit = nullptr;
    Wt::WPushButton *pushButtonCreate = nullptr;
    Wt::WPushButton *pushButtonDelete = nullptr;
    Wt::WPushButton *pushButtonUpload = nullptr;

    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>> queryModelHouses;
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_rooms>>> queryModelRooms;
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_inventory>>> queryModelInventory;

    void pushButtonEditClicked();
    void pushButtonCreateClicked();
    void pushButtonDeleteClicked();
    void pushButtonUploadClicked();

    void comboBoxChangedEquipmentClass(int);
    void comboBoxChangedEquipmentModel(int);

    std::unique_ptr<Wt::WContainerWidget> createRecordContainer();
    std::unique_ptr<Wt::WToolBar> createToolBar();

    void inventoryItemChanged(std::int32_t);
    void populateAspectsModel(std::int32_t);

  public:
    CInventoryPage(CApplication *);

    virtual void createPage();

    static std::unique_ptr<CTransactionPage> createClass(CApplication *parent)
    {
      return std::make_unique<CInventoryPage>(parent);
    }
  };

} // namespace transactions

#endif // INVENTORYPAGE_H
