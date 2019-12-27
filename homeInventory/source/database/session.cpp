//**********************************************************************************************************************************
//
// PROJECT:             Home Inventory System
// FILE:                session.h
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

#include "../../include/database/session.h"

  // Wt framework header files

#include <Wt/Auth/Dbo/AuthInfo.h>
#include "Wt/Auth/HashFunction.h"
#include "Wt/Auth/PasswordStrengthValidator.h"
#include "Wt/Auth/PasswordVerifier.h"
#include "Wt/Auth/GoogleService.h"
#include "Wt/Auth/FacebookService.h"

  // homeInventory application header files.

#include <include/database/database>

namespace database
{

  Wt::Auth::AuthService CSession::authService;
  Wt::Auth::PasswordService CSession::passwordService(CSession::authService);

  /// @brief Class constructor.
  /// @version 2019-12-27/GGB - Function created.

  CSession::CSession(Wt::Dbo::SqlConnectionPool *connectionPool)
  {
    setConnectionPool(*connectionPool);
    mapSQLClasses();
  }

  /// @brief Configure the authentication methods.
  /// @version 2019-12-27/GGB - Function created.

  void CSession::configureAuthorisation()
  {
    authService.setAuthTokensEnabled(true, "logincookie");
    authService.setAuthTokenValidity(40320);  // 4 weeks.
    authService.setIdentityPolicy(Wt::Auth::IdentityPolicy::EmailAddress);

    std::unique_ptr<Wt::Auth::PasswordVerifier> verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
    verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(7));
    passwordService.setVerifier(std::move(verifier));
    passwordService.setAttemptThrottlingEnabled(true);
    passwordService.setStrengthValidator(std::make_unique<Wt::Auth::PasswordStrengthValidator>());
  }

  /// @brief Maps the SQL classes that are to be used.
  /// @throws
  /// @version 2019-12-27/GGB - Function created.

  void CSession::mapSQLClasses()
  {
    try
    {
      mapClass<tbl_houses>("tbl_houses");
      mapClass<tbl_rooms>("tbl_rooms");
      mapClass<tbl_inventory>("tbl_inventory");
      mapClass<tbl_users>("tbl_users");
      mapClass<tbl_documents>("tbl_documents");
      mapClass<Wt::Auth::Dbo::AuthInfo<database::tbl_users>>("tbl_authInfo");
      mapClass<Wt::Auth::Dbo::AuthInfo<database::tbl_users>::AuthIdentityType>("tbl_authIdentity");
      mapClass<Wt::Auth::Dbo::AuthInfo<database::tbl_users>::AuthTokenType>("tbl_authToken");

      users_ = std::make_unique<Wt::Auth::Dbo::UserDatabase<Wt::Auth::Dbo::AuthInfo<database::tbl_users>>>(*this);
    }
    catch (Wt::Dbo::Exception &e)
    {
      std::cout << e.what() << std::endl;
    }
  }

  Wt::Auth::AbstractUserDatabase& CSession::users()
  {
    return *users_;
  }

  const Wt::Auth::AuthService& CSession::auth()
  {
    return authService;
  }

  const Wt::Auth::PasswordService& CSession::passwordAuth()
  {
    return passwordService;
  }

}
