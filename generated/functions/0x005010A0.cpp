// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005010A0 rf_event_music_stop_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_music_stop forward, vtable0x63E2A8 slot+4. Convert stored float seconds+0x2B8 to trunc(seconds*1000+0.5) milliseconds and call0x446020. No nonnegative clamp in this callback.
int __thiscall rf_event_music_stop_forward(float *this)
{
  return rf_music_request_owned_fade((int)(*(this + 174) * 1000.0 + 0.5));
}

