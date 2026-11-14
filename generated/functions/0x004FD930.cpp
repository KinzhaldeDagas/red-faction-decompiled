// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD930 rf_event_alarm_siren_forward
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_alarm_siren forward callback, RTTI/vtable 0x63E2BC slot +4. If active byte +0x2B8 !=1, play positional sound event 28 from owner+0x40 at gain1, store returned handle at +0x2BC, explicitly forward targets(-1,-1,1), then set active=1. Allocation failure does not prevent forwarding or active publication. Already-active call does nothing.
int __thiscall rf_event_alarm_siren_forward(int this)
{
  int result; // eax

  result = this;
  if ( *(_BYTE *)(this + 696) != 1 )
  {
    *(_DWORD *)(this + 700) = rf_gamesound_play_positional_event(28, (float *)(this + 64), 1.0, (int)flt_17F10B0, 0);
    result = rf_mission_event_forward_targets(this, -1, -1, 1);
    *(_BYTE *)(this + 696) = 1;
  }
  return result;
}

