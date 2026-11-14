// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD990 rf_event_alarm_siren_update
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_alarm_siren update callback, vtable 0x63E2BC slot +0xC. Run common delayed/special update, then retry positional event28 only when active byte +0x2B8==1 and stored voice +0x2BC==-1. Does not query backend completion for non--1 handles, refresh source position, clear active on allocation failure, or forward targets on retry.
int __thiscall rf_event_alarm_siren_update(int this)
{
  int result; // eax

  rf_mission_event_update_delayed_and_special((char *)this);
  result = this;
  if ( *(_BYTE *)(this + 696) == 1 && *(_DWORD *)(this + 700) == -1 )
  {
    result = rf_gamesound_play_positional_event(28, (float *)(this + 64), 1.0, (int)flt_17F10B0, 0);
    *(_DWORD *)(this + 700) = result;
  }
  return result;
}

