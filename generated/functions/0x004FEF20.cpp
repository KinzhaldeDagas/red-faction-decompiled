// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FEF20 rf_event_cyclic_timer_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_cyclic_timer forward, vtable0x63E12C slot+4: writes enabled byte event+0x2B8=1 only. Does not arm deadline+0x2C8, reset count+0x2CC, or immediately dispatch targets.
_BYTE *__thiscall rf_event_cyclic_timer_forward(_BYTE *this)
{
  *(this + 696) = 1;
  return this;
}

