/*
** Copyright 2014 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#ifndef CCB_BAM_DIMENSION_KPI_EVENT_HH
#  define CCB_BAM_DIMENSION_KPI_EVENT_HH

#  include <QString>
#  include "com/centreon/broker/io/data.hh"
#  include "com/centreon/broker/namespace.hh"
#  include "com/centreon/broker/timestamp.hh"
#  include "com/centreon/broker/io/event_info.hh"
#  include "com/centreon/broker/mapping/entry.hh"

CCB_BEGIN()

namespace                bam {
  /**
   *  @class dimension_kpi_event dimension_kpi_event.hh "com/centreon/broker/bam/dimension_kpi_event.hh"
   *  @brief Dimension Kpi event
   *
   */
  class                  dimension_kpi_event : public io::data {
  public:
                         dimension_kpi_event();
                         dimension_kpi_event(
                           dimension_kpi_event const& other);
                         ~dimension_kpi_event();
    dimension_kpi_event& operator=(dimension_kpi_event const& other);
    bool                 operator==(
                           dimension_kpi_event const& other) const;
    unsigned int         type() const;
    static unsigned int  static_type();

    unsigned             kpi_id;
    unsigned int         ba_id;
    QString              ba_name;
    unsigned int         host_id;
    QString              host_name;
    unsigned int         service_id;
    QString              service_description;
    unsigned int         kpi_ba_id;
    QString              kpi_ba_name;
    unsigned int         meta_service_id;
    QString              meta_service_name;
    unsigned int         boolean_id;
    QString              boolean_name;
    double               impact_warning;
    double               impact_critical;
    double               impact_unknown;

    static mapping::entry const
                         entries[];
    static io::event_info::event_operations const
                         operations;

  private:
    void                 _internal_copy(
                           dimension_kpi_event const& other);
  };
}

CCB_END()

#endif // !CCB_BAM_DIMENSION_KPI_EVENT_HH
