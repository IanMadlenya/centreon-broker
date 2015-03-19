/*
** Copyright 2014-2015 Merethis
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

#include "com/centreon/broker/bam/impact_values.hh"
#include "com/centreon/broker/bam/kpi_meta.hh"
#include "com/centreon/broker/bam/kpi_status.hh"
#include "com/centreon/broker/bam/meta_service.hh"
#include "com/centreon/broker/logging/logging.hh"

using namespace com::centreon::broker;
using namespace com::centreon::broker::bam;

/**
 *  Default constructor.
 */
kpi_meta::kpi_meta() {}

/**
 *  Copy constructor.
 *
 *  @param[in] other  Object to copy.
 */
kpi_meta::kpi_meta(kpi_meta const& other) : kpi(other) {
  _internal_copy(other);
}

/**
 *  Destructor.
 */
kpi_meta::~kpi_meta() {}

/**
 *  Assignment operator.
 *
 *  @param[in] other  Object to copy.
 *
 *  @return This object.
 */
kpi_meta& kpi_meta::operator=(kpi_meta const& other) {
  if (this != &other) {
    kpi::operator=(other);
    _internal_copy(other);
  }
  return (*this);
}

/**
 *  Base meta-service got updated.
 *
 *  @param[in]  child    Meta-service that got updated.
 *  @param[out] visitor  Receive events generated by this object.
 *
 *  @return True if the values of this object were modified.
 */
bool kpi_meta::child_has_update(
                 computable* child,
                 io::stream* visitor) {
  // It is useless to maintain a cache of meta-service values in this
  // class, as the meta_service class already cache most of them.
  if (child == _meta.data()) {
    // Logging.
    logging::debug(logging::low) << "BAM: meta-service KPI " << _id
      << " is getting notified of child update";

    // Generate status event.
    visit(visitor);
  }
  return (true);
}

/**
 *  Get the impact introduced by a CRITICAL state of the meta-service.
 *
 *  @return Impact if meta-service is CRITICAL.
 */
double kpi_meta::get_impact_critical() const {
  return (_impact_critical);
}

/**
 *  Get the impact introduced by a WARNING state of the meta-service.
 *
 *  @return Impact if meta-service is WARNING.
 */
double kpi_meta::get_impact_warning() const {
  return (_impact_warning);
}

/**
 *  Get the hard impact introduced by the meta-service.
 *
 *  @param[out] hard_impact  Hard impacts.
 */
void kpi_meta::impact_hard(impact_values& hard_impact) {
  _fill_impact(hard_impact);
  return ;
}

/**
 *  Get the soft impact introduced by the meta-service.
 *
 *  @param[out] soft_impact  Soft impacts.
 */
void kpi_meta::impact_soft(impact_values& soft_impact) {
  _fill_impact(soft_impact);
  return ;
}

/**
 *  Link the kpi_meta with a specific meta-service (class meta_service).
 *
 *  @param[in] my_meta  Linked meta-service.
 */
void kpi_meta::link_meta(misc::shared_ptr<meta_service>& my_meta) {
  _meta = my_meta;
  return ;
}

/**
 *  Set impact if meta-service is CRITICAL.
 *
 *  @param[in] impact  Impact if meta-service is CRITICAL.
 */
void kpi_meta::set_impact_critical(double impact) {
  _impact_critical = impact;
  return ;
}

/**
 *  Set impact if meta-service is WARNING.
 *
 *  @param[in] impact  Impact if meta-service is WARNING.
 */
void kpi_meta::set_impact_warning(double impact) {
  _impact_warning = impact;
  return ;
}

/**
 *  Unlink from meta-service.
 */
void kpi_meta::unlink_meta() {
  _meta.clear();
  return ;
}

/**
 *  Visit meta-service KPI.
 *
 *  @param[out] visitor  Object that will receive status and events.
 */
void kpi_meta::visit(io::stream* visitor) {
  if (visitor) {
    // Commit the initial events saved in the cache.
    commit_initial_events(visitor);

    // Get information (HARD and SOFT values are the same).
    impact_values values;
    impact_hard(values);
    short state(_meta->get_state());

    // Generate BI events.
    {
      // If no event was cached, create one.
      if (_event.isNull())
        _open_new_event(visitor, values.get_nominal(), state);
      // If state changed, close event and open a new one.
      else if (state != _event->status) {
        _event->end_time = ::time(NULL);
        visitor->write(_event.staticCast<io::data>());
        _event.clear();
        _open_new_event(visitor, values.get_nominal(), state);
      }
    }

    // Generate status event.
    {
      misc::shared_ptr<kpi_status> status(new kpi_status);
      status->kpi_id = _id;
      status->level_acknowledgement_hard = values.get_acknowledgement();
      status->level_acknowledgement_soft = values.get_acknowledgement();
      status->level_downtime_hard = values.get_downtime();
      status->level_downtime_soft = values.get_downtime();
      status->level_nominal_hard = values.get_nominal();
      status->level_nominal_soft = values.get_nominal();
      status->state_hard = state;
      status->state_soft = state;
      status->last_state_change = get_last_state_change();
      status->last_impact = values.get_nominal();
      visitor->write(status.staticCast<io::data>());
    }

  }
  return ;
}

/**
 *  Fill impact_values from base values.
 *
 *  @param[out] impact  Impact values.
 */
void kpi_meta::_fill_impact(impact_values& impact) {
  // Get nominal impact from state.
  short state(_meta->get_state());
  double nominal;
  if (0 == state)
    nominal = 0.0;
  else if (1 == state)
    nominal = _impact_warning;
  else
    nominal = _impact_critical;
  impact.set_nominal(nominal);
  impact.set_acknowledgement(0.0);
  impact.set_downtime(0.0);
  return ;
}

/**
 *  Copy internal data members.
 *
 *  @param[in] other  Object to copy.
 */
void kpi_meta::_internal_copy(kpi_meta const& other) {
  _meta = other._meta;
  _event = other._event;
  _impact_critical = other._impact_critical;
  _impact_warning = other._impact_warning;
  return ;
}

/**
 *  Open a new event for this KPI.
 *
 *  @param[out] visitor  Visitor that will receive events.
 *  @param[in]  impact   Current impact of this KPI.
 *  @param[in]  state    Meta-service state.
 */
void kpi_meta::_open_new_event(
                 io::stream* visitor,
                 int impact,
                 short state) {
  _event = new kpi_event;
  _event->kpi_id = _id;
  _event->impact_level = impact;
  _event->in_downtime = false;
  _event->output = _meta->get_output().c_str();
  _event->perfdata = _meta->get_perfdata().c_str();
  _event->start_time = time(NULL); // XXX _ba->get_last_service_update();
  _event->status = state;
  if (visitor) {
    misc::shared_ptr<io::data> ke(new kpi_event(*_event));
    visitor->write(ke);
  }
  return ;
}
