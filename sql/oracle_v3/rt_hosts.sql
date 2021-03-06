--
-- Monitored hosts.
--
CREATE TABLE rt_hosts (
  host_id int NOT NULL,
  name varchar(255) NOT NULL,
  instance_id int NOT NULL,

  acknowledged char(1) default NULL,
  acknowledgement_type smallint default NULL,
  active_checks char(1) default NULL,
  address varchar(75) default NULL,
  alias varchar(100) default NULL,
  check_attempt smallint default NULL,
  check_command clob default NULL,
  check_freshness char(1) default NULL,
  check_interval double precision default NULL,
  check_period varchar(75) default NULL,
  check_type smallint default NULL,
  checked char(1) default NULL,
  command_line clob default NULL,
  default_active_checks char(1) default NULL,
  default_event_handler_enabled char(1) default NULL,
  default_flap_detection char(1) default NULL,
  default_notify char(1) default NULL,
  enabled char(1) default 1 NOT NULL,
  event_handler varchar(255) default NULL,
  event_handler_enabled char(1) default NULL,
  execution_time double precision default NULL,
  first_notification_delay double precision default NULL,
  flap_detection char(1) default NULL,
  flap_detection_on_down char(1) default NULL,
  flap_detection_on_unreachable char(1) default NULL,
  flap_detection_on_up char(1) default NULL,
  flapping char(1) default NULL,
  freshness_threshold double precision default NULL,
  high_flap_threshold double precision default NULL,
  last_check int default NULL,
  last_hard_state smallint default NULL,
  last_hard_state_change int default NULL,
  last_notification int default NULL,
  last_state_change int default NULL,
  last_time_down int default NULL,
  last_time_unreachable int default NULL,
  last_time_up int default NULL,
  last_update int default NULL,
  latency double precision default NULL,
  low_flap_threshold double precision default NULL,
  max_check_attempts smallint default NULL,
  next_check int default NULL,
  next_host_notification int default NULL,
  no_more_notifications char(1) default NULL,
  notification_interval double precision default NULL,
  notification_number smallint default NULL,
  notification_period varchar(75) default NULL,
  notify char(1) default NULL,
  notify_on_down char(1) default NULL,
  notify_on_downtime char(1) default NULL,
  notify_on_flapping char(1) default NULL,
  notify_on_recovery char(1) default NULL,
  notify_on_unreachable char(1) default NULL,
  obsess_over_host char(1) default NULL,
  output clob default NULL,
  percent_state_change double precision default NULL,
  perfdata clob default NULL,
  real_state smallint default NULL,
  retry_interval double precision default NULL,
  scheduled_downtime_depth smallint NOT NULL default 0,
  should_be_scheduled char(1) default NULL,
  stalk_on_down char(1) default NULL,
  stalk_on_unreachable char(1) default NULL,
  stalk_on_up char(1) default NULL,
  state smallint default NULL,
  state_type smallint default NULL,

  UNIQUE (host_id),
  INDEX (instance_id),
  INDEX (name),
  FOREIGN KEY (instance_id) REFERENCES rt_instances (instance_id)
    ON DELETE CASCADE
);
