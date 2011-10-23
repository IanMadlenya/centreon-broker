/*
** Copyright 2011 Merethis
**
** This file is part of Centreon Broker.
**
** Centreon Broker is free software: you can redistribute it and/or
** modify it under the terms of the GNU General Public License version 2
** as published by the Free Software Foundation.
**
** Centreon Broker is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Centreon Broker. If not, see
** <http://www.gnu.org/licenses/>.
*/

#include <string.h>
#include "com/centreon/broker/misc/stringifier.hh"

using namespace com::centreon::broker;

/**
 *  Check that long long integer insertion works properly.
 *
 *  @return 0 on success.
 */
int main () {
  // Return value.
  int retval(0);

  // First insertion.
  misc::stringifier s;
  s << 741258963123ll;
  retval |= strcmp(s.data(), "741258963123");

  // Second insertions.
  s << -12345675989ll << 3214569874110ll;
  retval |= strcmp(s.data(), "741258963123-123456759893214569874110");

  // Return test result.
  return (retval);
}
