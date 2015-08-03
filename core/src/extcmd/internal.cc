/*
** Copyright 2013,2015 Merethis
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

#include "com/centreon/broker/extcmd/command_request.hh"
#include "com/centreon/broker/extcmd/command_result.hh"
#include "com/centreon/broker/extcmd/internal.hh"
#include "com/centreon/broker/extcmd/factory.hh"
#include "com/centreon/broker/io/events.hh"
#include "com/centreon/broker/io/protocols.hh"
#include "com/centreon/broker/logging/logging.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::extcmd;


/**************************************
*                                     *
*           Global Objects            *
*                                     *
**************************************/

/**
 *  @brief Command file initialization routine.
 *
 *  Initialize the command file endpoint.
 */
void extcmd::load() {
  io::events& e(io::events::instance());

  // Register extcmd protocol.
  io::protocols::instance().reg(
                              "extcmd",
                              extcmd::factory(),
                              1,
                              7);

  // Register event.
  std::set<unsigned int> elements;
  elements.insert(command_request::static_type());
  elements.insert(command_result::static_type());
  e.reg("extcmd", elements);

  return ;
}

/**
 *  @brief Command file cleanup routine.
 *
 *  Delete the command file endpoint.
 */
void extcmd::unload() {
  // Unregister events.
  io::events::instance().unreg("extcmd");

  // Unregister protocol.
  io::protocols::instance().unreg("extcmd");

  return ;
}
