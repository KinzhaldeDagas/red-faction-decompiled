// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF810 rf_alarm_rearm_shared_deadline
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Arm shared alarm deadline0x87FC20 for17000ms unconditionally. Does not set active, allocate a voice, or check current alarm state.
int rf_alarm_rearm_shared_deadline()
{
  return rf_replicator_arm_milliseconds(unk_87FC20, 17000);
}

