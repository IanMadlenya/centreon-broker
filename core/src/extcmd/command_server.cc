/*
** Copyright 2015 Merethis
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

#include <QLocalSocket>
#include "com/centreon/broker/exceptions/msg.hh"
#include "com/centreon/broker/extcmd/command_client.hh"
#include "com/centreon/broker/extcmd/command_request.hh"
#include "com/centreon/broker/extcmd/command_result.hh"
#include "com/centreon/broker/extcmd/command_server.hh"
#include "com/centreon/broker/extcmd/server_socket.hh"
#include "com/centreon/broker/logging/logging.hh"
#include "com/centreon/broker/processing/feeder.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::extcmd;

/**
 *  Constructor.
 *
 *  @param[in] socket_file  Socket file.
 */
command_server::command_server(std::string const& socket_file)
  : io::endpoint(true), _socket_file(socket_file) {}

/**
 *  Destructor.
 */
command_server::~command_server() {}

/**
 *  Clone endpoint.
 */
io::endpoint* command_server::clone() const {
  return (new command_server(_socket_file));
}

/**
 *  Close endpoint.
 */
void command_server::close() {
  return ;
}

/**
 *  Wait for a new connection to local socket.
 *
 *  @return New client object if available, null pointer otherwise.
 */
misc::shared_ptr<io::stream> command_server::open() {
  // Initialization.
  if (!_socket.get()) {
    // Listen on socket.
    ::remove(_socket_file.c_str());
    _socket.reset(new server_socket(_socket_file));

    // Create command listener.
    _listener = new command_listener;
  }

  // Wait for incoming connections.
  logging::debug(logging::medium)
    << "command: waiting for new connection";
  if (!_socket->has_pending_connections()) {
    bool timedout(false);
    _socket->wait_for_new_connection(1000, &timedout);
    if (!_socket->has_pending_connections()) {
      if (timedout)
        return (misc::shared_ptr<io::stream>());
      else
        throw (exceptions::msg()
               << "command: error while waiting on client on file '"
               << _socket_file << "': " << _socket->error_string());
    }
  }

  // Accept new client.
  int incoming(_socket->next_pending_connection());
  if (incoming < 0)
    throw (exceptions::msg() << "command: could not accept client: "
           << _socket->error_string());
  logging::info(logging::medium) << "command: new client connected";
  misc::shared_ptr<io::stream>
    new_client(new command_client(incoming, _listener.data()));
  return (new_client);
}

/**
 *  Open.
 *
 *  @param[in] id  Unused.
 */
misc::shared_ptr<io::stream> command_server::open(QString const& id) {
  (void)id;
  return (open());
}
