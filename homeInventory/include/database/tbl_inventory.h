//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:
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

#ifndef TBL_INVENTORY_H
#define TBL_INVENTORY_H

// Standard C++ library headers

#include <stdint.h>
#include <string>

// Wt framework header files

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <Wt/WGlobal.h>

namespace database
{

  class tbl_inventory
  {
  public:
    std::string description;
    std::string purchaseDate;
    std::int32_t quantity;
    float purchasePrice;
    std::string manufacturer;
    std::string serialNumber;
    std::string supplier;
    std::string modelNumber;
    std::string invoiceNumber;
    std::string comments;
    bool recordDeleted;
    std::string deleteDate;
    std::string deleteComments;

    template<class Action>
    void persist(Action & a)
    {
      Wt::Dbo::field(a, description, "Description");
      Wt::Dbo::field(a, purchaseDate, "PurchaseDate");
      Wt::Dbo::field(a, quantity, "Quantity");
      Wt::Dbo::field(a, purchasePrice, "PurchasePrice");
      Wt::Dbo::field(a, manufacturer, "Manufacturer");
      Wt::Dbo::field(a, serialNumber, "SerialNumber");
      Wt::Dbo::field(a, supplier, "Supplier");
      Wt::Dbo::field(a, modelNumber, "ModelNumber");
      Wt::Dbo::field(a, invoiceNumber, "InvoiceNumber");
      Wt::Dbo::field(a, comments, "Comments");

      Wt::Dbo::field(a, recordDeleted, "RecordDeleted");
    }
  };

} // namespace database

#endif // TBL_INVENTORY_H
