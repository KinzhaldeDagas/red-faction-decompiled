// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500070 rf_event_switch_forward
// UNREALRED VERIFIED [event-lifecycle-20261028]: Delegates to rf_event_switch_apply_targets(this,1) and returns its result. No independent target iteration or state stores in this wrapper.
int __thiscall rf_event_switch_forward(int *this)
{
  return rf_event_switch_apply_targets(this, 1);
}

