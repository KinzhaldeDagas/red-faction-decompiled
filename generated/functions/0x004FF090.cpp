// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FF090 rf_event_cyclic_timer_reverse
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_cyclic_timer reverse, vtable0x63E12C slot+8: writes enabled byte+0x2B8=0 only. Leaves deadline and accumulated count intact, so forward later resumes existing state rather than starting a new timer in these callbacks.
_BYTE *__thiscall rf_event_cyclic_timer_reverse(_BYTE *this)
{
  *(this + 696) = 0;
  return this;
}

