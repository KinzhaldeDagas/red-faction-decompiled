// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF7D0 rf_alarm_disable_shared
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Unconditionally pass stored0x87FC18 handle to common stop helper, then write handle=-1 and active byte0x87FC00=0. Does not reset shared deadline0x87FC20; repeated stops and a later expired-deadline update still reach common stop.
int *rf_alarm_disable_shared()
{
  int *result; // eax

  result = rf_gamesound_stop_voice_handle(dword_87FC18);
  dword_87FC18 = -1;
  unk_87FC00 = 0;
  return result;
}

