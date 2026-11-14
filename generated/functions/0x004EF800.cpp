// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF800 rf_alarm_get_shared_active
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Return raw shared alarm byte0x87FC00. This is the admitted alarm flag, not a query of voice-handle validity or backend playback.
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: Returns raw87FC00 only. A source/current session owner may expose this independently of audio/model success and without synchronizing resource indexes. Unknown owner is unavailable, not false. Actual normal-level reset is448190(!a1)->4EF150, initialized voice/deadline from4EEFF0.
char rf_alarm_get_shared_active()
{
  return unk_87FC00;
}

