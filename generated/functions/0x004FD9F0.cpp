// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD9F0 rf_event_alarm_siren_reverse
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_alarm_siren reverse callback, vtable 0x63E2BC slot +8. Only non--1 voice +0x2BC triggers common stop, handle=-1 and active byte +0x2B8=0. If handle already -1, leaves active unchanged; therefore an active siren whose allocation failed can still retry from its update after this reverse call. No explicit target forwarding in this body.
int __thiscall rf_event_alarm_siren_reverse(int this)
{
  int result; // eax

  result = this;
  if ( *(_DWORD *)(this + 700) != -1 )
  {
    rf_gamesound_stop_voice_handle(*(_DWORD *)(this + 700));
    *(_DWORD *)(this + 700) = -1;
    *(_BYTE *)(this + 696) = 0;
    return this;
  }
  return result;
}

