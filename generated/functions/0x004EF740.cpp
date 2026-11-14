// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF740 rf_alarm_update_shared_deadline
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Check shared deadline0x87FC20 regardless of active byte. If elapsed result equals1, call shared alarm disable0x4EF7D0 and disarm deadline via rf_replicator_reset. No voice-playing query or playback retry in this body.
_DWORD *rf_alarm_update_shared_deadline()
{
  _DWORD *result; // eax

  result = (_DWORD *)rf_replicator_has_elapsed(unk_87FC20);
  if ( (unsigned __int8)result == 1 )
  {
    rf_alarm_disable_shared();
    return rf_replicator_reset(unk_87FC20);
  }
  return result;
}

