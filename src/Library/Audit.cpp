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
// Authors: Daniel Kopecek <dkopecek@redhat.com>
//

#include "Audit.hpp"

#include <Common/Utility.hpp>
#include <Exception.hpp>
#include <Logger.hpp>

namespace usbguard
{

  AuditIdentity::AuditIdentity()
  {
    _uid = getuid();
    _pid = getpid();
  }

  AuditIdentity::AuditIdentity(uid_t uid, pid_t pid)
  {
    _uid = uid;
    _pid = pid;
  }

  std::string AuditIdentity::toString() const
  {
    std::string identity_string;

    identity_string.append("{ uid=");
    identity_string.append(numberToString(_uid));
    identity_string.append(" pid=");
    identity_string.append(numberToString(_pid));
    identity_string.append(" }");

    return identity_string;
  }

  Audit::Audit(const AuditIdentity& identity)
    : _identity(identity)
  {

  }

  void Audit::policyEvent(Pointer<Rule> rule, Policy::EventType event)
  {
    policyEvent(_identity, rule, event);
  }
  
  void Audit::policyEvent(Pointer<Rule> new_rule, Pointer<Rule> old_rule)
  {
    policyEvent(_identity, new_rule, old_rule);
  }

  void Audit::policyEvent(Pointer<Device> device, Policy::EventType event)
  {
    policyEvent(_identity, device, event);
  }

  void Audit::policyEvent(Pointer<Device> device, Rule::Target old_target, Rule::Target new_target)
  {
    policyEvent(_identity, device, old_target, new_target);
  }

  void Audit::deviceEvent(Pointer<Device> device, DeviceManager::EventType event)
  {
    deviceEvent(_identity, device, event);
  }
  
  void Audit::deviceEvent(Pointer<Device> new_device, Pointer<Device> old_device)
  {
    deviceEvent(_identity, new_device, old_device);
  }

  void Audit::policyEvent(const AuditIdentity& identity, Pointer<Rule> rule, Policy::EventType event)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " POLICY EVENT:" \
      << " type=" << Policy::eventTypeToString(event) \
      << " rule='" << rule->toString() << "'";
  }

  void Audit::policyEvent(const AuditIdentity& identity, Pointer<Rule> new_rule, Pointer<Rule> old_rule)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " POLICY EVENT:" \
      << " type=" << Policy::eventTypeToString(Policy::EventType::Update) \
      << " old_rule='" << old_rule->toString() << "'" \
      << " new_rule='" << new_rule->toString() << "'";
  }

  void Audit::policyEvent(const AuditIdentity& identity, Pointer<Device> device, Policy::EventType event)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " POLICY EVENT:" \
      << " type=" << Policy::eventTypeToString(event) \
      << " target=" << Rule::targetToString(device->getTarget()) \
      << " device='" << device->getDeviceRule()->toString() << "'";
  }

  void Audit::policyEvent(const AuditIdentity& identity, Pointer<Device> device, Rule::Target old_target, Rule::Target new_target)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " POLICY EVENT:" \
      << " type=" << Policy::eventTypeToString(Policy::EventType::Update) \
      << " old_target=" << Rule::targetToString(old_target) \
      << " new_target=" << Rule::targetToString(new_target) \
      << " device='" << device->getDeviceRule()->toString() << "'"; 
  }

  void Audit::deviceEvent(const AuditIdentity& identity, Pointer<Device> device, DeviceManager::EventType event)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " DEVICE EVENT:" \
      << " type=" << DeviceManager::eventTypeToString(event) \
      << " device='" << device->getDeviceRule()->toString() << "'";
  }

  void Audit::deviceEvent(const AuditIdentity& identity, Pointer<Device> new_device, Pointer<Device> old_device)
  {
    const std::string identity_string = identity.toString();

    USBGUARD_LOG(Audit) << "identity=" << identity.toString() \
      << " DEVICE EVENT:" \
      << " type=" << DeviceManager::eventTypeToString(DeviceManager::EventType::Update) \
      << " old_device='" << old_device->getDeviceRule()->toString() << "'"\
      << " new_device='" << new_device->getDeviceRule()->toString() << "'";
  }
} /* namespace usbguard */
