// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500E90 rf_event_fog_state_reverse
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_fog_state reverse, vtable0x63E2F8 slot+8. For finite float0x6FC34C!=-1.0, copy it into0x6FC350 then write-1.0f to0x6FC34C. Sentinel equality returns unchanged. Does not read event parameters or restore an event-local snapshot.
void rf_event_fog_state_reverse()
{
  if ( unk_6FC34C != -1.0 )
  {
    unk_6FC350 = unk_6FC34C;
    unk_6FC34C = -1.0;
  }
}

