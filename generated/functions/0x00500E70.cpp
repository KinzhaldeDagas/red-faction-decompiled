// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500E70 rf_event_fog_state_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_fog_state forward, vtable0x63E2F8 slot+4. Copy global float0x6FC350 into0x6FC34C unconditionally. No event-field/target lookup or renderer call in this callback; global field meanings outside this two-value transition are not inferred here.
void rf_event_fog_state_forward()
{
  unk_6FC34C = unk_6FC350;
}

