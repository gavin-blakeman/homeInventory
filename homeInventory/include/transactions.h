//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                transactions.h
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

#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <cstdint>

typedef std::int16_t transaction_t;

namespace TC
{
  transaction_t const IP000   = 1000;
  transaction_t const IP050   = 1050;
  transaction_t const IP100   = 1100;
  transaction_t const IP200   = 1200;
  transaction_t const IP210   = 1210;
  transaction_t const IP290   = 1290;
  transaction_t const IP900   = 1900;
  transaction_t const IP910   = 1910;
  transaction_t const IP920   = 1920;
  transaction_t const MS000   = 2000;
  transaction_t const MS001   = 2100;
  transaction_t const MS900   = 2900;
  transaction_t const MS901   = 2910;
  transaction_t const RS000   = 3000;
  transaction_t const RS100   = 3100;
  transaction_t const RS200   = 3200;
  transaction_t const MT000   = 4000;
  transaction_t const MT100   = 4100;
  transaction_t const MT900   = 4900;
  transaction_t const GS000   = 5000;
  transaction_t const SM000   = 6000;
  transaction_t const MD000   = 7000;
  transaction_t const UD000   =   7100;
  transaction_t const CD001   =   7200;
  transaction_t const PH000   =   7300;
  transaction_t const PH100   =     7310;
  transaction_t const PH200   =     7320;
  transaction_t const PH300   =     7330;
  transaction_t const PH400   =     7340;
  transaction_t const BD000   =   7400;
  transaction_t const BD001   =     7410;
  transaction_t const BD002   =     7420;
  transaction_t const AS000   =   7500;
  transaction_t const AS001   =     7510;
  transaction_t const AS002   =     7520;
  transaction_t const AS003   =     7530;
  transaction_t const AS004   =     7540;
  transaction_t const OT000   =   7600;
  transaction_t const OT010   =     7610;
  transaction_t const AD000   = 8000;
  transaction_t const AD010   = 8010;
  transaction_t const AD020   = 8020;
  transaction_t const AD030   = 8030;
  transaction_t const AD040   = 8040;
  transaction_t const AD050   = 8050;
  transaction_t const AD100   =   8100;
  transaction_t const AD110   =     8110;
  transaction_t const AD120   =     8120;
}

#endif // TRANSACTIONS_H
