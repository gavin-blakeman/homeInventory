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

#ifndef ROOMPAGE_H
#define ROOMPAGE_H

  // Standard C++ library header files

#include <memory>

  // Wt framework header files.

#include <Wt/WString.h>
#include <Wt/Dbo/QueryModel.h>

  // Reliability Manager header files.

#include "transactionPage.h"
#include <include/database/database>

namespace transactions
{
  class CRoomPage: public CTransactionPage
  {
  private:
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_houses>>> queryModelHouses;
    std::shared_ptr<Wt::Dbo::QueryModel<Wt::Dbo::ptr<database::tbl_rooms>>> queryModelRooms;
    Wt::WComboBox *comboBoxHouses = nullptr;
    Wt::WTableView *tableViewRooms = nullptr;

    void comboBoxChanged(int);

  protected:
  public:
    CRoomPage(CApplication *);

    virtual void createPage();

    static std::unique_ptr<CTransactionPage> createClass(CApplication *);  // Factory function.
  };

} //namespace transactions

#endif // ROOMPAGE_H
