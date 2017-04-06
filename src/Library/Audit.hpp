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
#pragma once

#include <Rule.hpp>
#include <Device.hpp>
#include <Policy.hpp>
#include <DeviceManager.hpp>
#include <Typedefs.hpp>

#include <string>

#include <unistd.h>
#include <sys/types.h>

namespace usbguard
{
  class DLL_PUBLIC AuditIdentity
  {
    public:
      AuditIdentity();
      AuditIdentity(uid_t uid, pid_t pid);

      std::string toString() const;
    private:
      uid_t _uid;
      pid_t _pid;
  };

  class DLL_PUBLIC Audit
  {
    public:
      Audit(const AuditIdentity& identity);

      void policyEvent(Pointer<Rule> rule, Policy::EventType event);
      void policyEvent(Pointer<Rule> new_rule, Pointer<Rule> old_rule);
      void policyEvent(Pointer<Device> device, Policy::EventType event);
      void policyEvent(Pointer<Device> device, Rule::Target old_target, Rule::Target new_target);

      void deviceEvent(Pointer<Device> device, DeviceManager::EventType event);
      void deviceEvent(Pointer<Device> new_device, Pointer<Device> old_device);

      /*
       * Audit policy changes:
       *   - rule append
       *   - rule remove
       *   - rule update
       *   - policy parameter change
       *
       * Audit data:
       *   - who: uid + pid
       *   - when: time
       *   - what: append, remove, update
       *   - update: old, new
       */
      static void policyEvent(const AuditIdentity& identity, Pointer<Rule> rule, Policy::EventType event);
      static void policyEvent(const AuditIdentity& identity, Pointer<Rule> new_rule, Pointer<Rule> old_rule);
      static void policyEvent(const AuditIdentity& identity, Pointer<Device> device, Policy::EventType event);
      static void policyEvent(const AuditIdentity& identity, Pointer<Device> device, Rule::Target old_target, Rule::Target new_target);

      /*
       * Audit device changes:
       *   - device insertion
       *   - device removal
       *   - device authorization target change
       *
       * Audit data:
       *   - who: uid + pid
       *   - when: time
       *   - what: insert, remove, authorization target
       *   - change: old, new
       */
      static void deviceEvent(const AuditIdentity& identity, Pointer<Device> device, DeviceManager::EventType event);
      static void deviceEvent(const AuditIdentity& identity, Pointer<Device> new_device, Pointer<Device> old_device);

    private:
      AuditIdentity _identity;
  };
} /* namespace usbguard */
