//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                main.cpp
// SUBSYSTEM:           File containing the main() function.
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
// OVERVIEW:						main() function.
//
// HISTORY:             2019-12-27/GGB - File Created.
//
//**********************************************************************************************************************************

  // Standard C++ library header files

#include <exception>
#include <memory>

  // Wt++ framework header files.

#include <Wt/WServer.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/Dbo/SqlConnectionPool.h>
#include <Wt/Dbo/backend/MySQL.h>

  // homeInventory application header files.

#include <include/application.h>
#include <include/database/session.h>

/// @brief Creates a connection pool for further use. Has 10 connections in the connection pool.
/// @throws None.
/// @version 2019-12-27/GGB - Function created.

std::unique_ptr<Wt::Dbo::SqlConnectionPool> createConnectionPool()
{
  auto connection = std::make_unique<Wt::Dbo::backend::MySQL>("homeInventory",
                                                              "homeInventory",
                                                              "homeInventory",
                                                              "192.168.8.19",3306);
  connection->setProperty("show-queries", "true");
  //connection->setDateTimeStorage(Wt::Dbo::SqlDateTimeType::DateTime, Wt::Dbo::backend::DateTimeStorage::PseudoISO8601AsText);
  return std::make_unique<Wt::Dbo::FixedSqlConnectionPool>(std::move(connection), 10);
}

/// @brief Main function for the application.
/// @param[in] argc: Number of command line arguments.
/// @param[in] argv: Command line arguments.
/// @returns 0: Normal exit.
/// @version 2019-12-27/GGB - Function created.

int main(int argc, char **argv)
{
  try
  {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);
    std::unique_ptr<Wt::Dbo::SqlConnectionPool> connectionPool = createConnectionPool();

    server.addEntryPoint(Wt::EntryPointType::Application, std::bind(&createApplication, std::placeholders::_1,
                                                                    connectionPool.get()),
                         "", "css/wt/favicon.ico");
    database::CSession::configureAuthorisation();

    server.run();
  }
  catch (Wt::WServer::Exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
  catch (Wt::Dbo::Exception &e)
  {
    std::cerr << "Dbo exception: " << e.what() << std::endl;
  }
  catch (std::exception &e)
  {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
