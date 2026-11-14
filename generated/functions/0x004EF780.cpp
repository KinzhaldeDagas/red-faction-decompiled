// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF780 rf_alarm_enable_shared
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] If byte0x87FC00 is zero, play common sound event51(group0,offset0,gain1), store returned handle at0x87FC18, arm deadline0x87FC20 for17000ms, then set active byte1. Playback allocation failure does not prevent active/deadline publication. Already-active enable does nothing and does not refresh deadline.
int rf_alarm_enable_shared()
{
  int result; // eax

  result = unk_87FC00;
  if ( !unk_87FC00 )
  {
    unk_87FC18 = rf_gamesound_play_event(51, 0, 0.0, 1.0);
    result = rf_replicator_arm_milliseconds(unk_87FC20, 17000);
    unk_87FC00 = 1;
  }
  return result;
}

