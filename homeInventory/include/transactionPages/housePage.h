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

#ifndef HOUSEPAGE_H
#define HOUSEPAGE_H

  // Standard C++ library header files

#include <memory>

  // Wt framework header files.

#include <Wt/WPushButton.h>
#include <Wt/WTableView.h>

  // SAMAP5 5header files.

#include "transactionPage.h"

namespace transactions
{
  class CHousePage: public CTransactionPage
  {
  private:
    Wt::WPushButton *pushButtonCreate = nullptr;
    Wt::WPushButton *pushButtonEdit = nullptr;
    Wt::WPushButton *pushButtonDelete = nullptr;
    Wt::WTableView *tableViewHouses = nullptr;

    void pushButtonCreateClicked();
    void pushButtonEditClicked();
    void pushButtonDeleteClicked();

    void tableViewHousesSelectionChanged();

  protected:
  public:
    CHousePage(CApplication *);

    virtual void createPage();

    void refreshTableView();

    static std::unique_ptr<CTransactionPage> createClass(CApplication *);  // Factory function.
  };

} // namespace transactions

#endif // HOUSEPAGE_H
