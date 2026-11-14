// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00501070 rf_event_music_start_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_music_start forward, vtable0x63E294 slot+4. Pass filename string event+0x2B8 and byte+0x2C0 to0x446050; event body does not iterate targets or interpret helper result.
bool __thiscall rf_event_music_start_forward(char *this)
{
  const char *v1; // eax
  char v3; // [esp-4h] [ebp-8h]

  v3 = *(this + 704);
  v1 = rf_string_object_c_str_or_empty(this + 696);
  return rf_music_request_owned_filename((int)v1, v3);
}

