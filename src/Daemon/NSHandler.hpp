//
// Copyright (C) 2017 Red Hat, Inc.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Authors: Radovan Sroka <rsroka@redhat.com>
//
#pragma once
#ifdef HAVE_BUILD_CONFIG_H
  #include <build-config.h>
#endif

#include <string>
#include <vector>

#include "usbguard/KeyValueParser.hpp"
#include "usbguard/RuleSet.hpp"
#include "usbguard/MemoryRuleSet.hpp"
#include "usbguard/Typedefs.hpp"

#ifdef HAVE_LDAP
  #include "LDAPHandler.hpp"
#endif

namespace usbguard
{
  class Interface;
  class DLL_PUBLIC NSHandler
  {
  public:

    enum class SourceType {
      LOCAL,
#ifdef HAVE_LDAP
      LDAP,
#endif
      //SSSD
    };

    NSHandler();
    ~NSHandler();

    void setRulesPath(const std::string& path);
    std::string& getRulesPath();
    std::shared_ptr<RuleSet> getRuleSet(Interface* const interface_ptr);
    void parseNSSwitch();

    void setNSSwitchPath(const std::string& path);

    std::string getSourceInfo();

#ifdef HAVE_LDAP
    std::shared_ptr<LDAPHandler> getLDAPHandler();
#endif

    static NSHandler& getRef();

  private:
    KeyValueParser _parser;
    std::map<std::string, std::string> _parsedOptions;

    std::string _nsswitch_path;
    SourceType _source;
    std::string _rulesPath;

#ifdef HAVE_LDAP
    std::shared_ptr<LDAPHandler> _ldap = nullptr;
#endif

    static NSHandler* _self;
  };
} /* namespace usbguard */

/* vim: set ts=2 sw=2 et */
