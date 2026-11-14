// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500DC0 rf_event_set_liquid_depth_reverse_disabled
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_set_liquid_depth reverse, vtable0x63E26C slot+8. UNCONDITIONAL JMP0x500DC9 to epilogue0x500E49 skips dormant room-depth-query/restore loop0x500DCB-0x500E47. No query or liquid mutation is reachable from entry in matched RF.exe bytes.
void rf_event_set_liquid_depth_reverse_disabled()
{
  ;
}

