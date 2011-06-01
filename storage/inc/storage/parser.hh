/*
** Copyright 2011 Merethis
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

#ifndef CCB_STORAGE_PARSER_HH_
# define CCB_STORAGE_PARSER_HH_

# include <list>
# include <QString>

namespace         com {
  namespace       centreon {
    namespace     broker {
      namespace   storage {
        // Forward declaration.
        class     perfdata;

        /**
         *  @class parser parser.hh "storage/parser.hh"
         *  @brief Parse raw perfdatas.
         *
         *  Parse perfdata as given by plugins output and convert them to a
         *  perfdata structure.
         */
        class     parser {
         private:
                  parser(parser const& p);
          parser& operator=(parser const& p);

         public:
                  parser();
                  ~parser();
          void    parse_perfdata(QString const& str,
                    std::list<perfdata>& pd);
        };
      }
    }
  }
}

#endif /* !CCB_STORAGE_PARSER_HH_ */
