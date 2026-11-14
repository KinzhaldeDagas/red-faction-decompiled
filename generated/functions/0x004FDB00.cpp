// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDB00 rf_event_alarm_reverse
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] event_alarm reverse callback, vtable0x63E2D0 slot+8. Calls shared alarm disable0x4EF7D0 only; does not walk or restore target AI states, reset the shared deadline, or reverse entity reactivation.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] Reverse local callback only sharedDisable; ordinary outer auto-forward policy still applies to Alarm46. Do not restore target AI modes/deadlines/reactivation or suppress generic reverse completion merely because local body has no target walk.
int *rf_event_alarm_reverse()
{
  return rf_alarm_disable_shared();
}

