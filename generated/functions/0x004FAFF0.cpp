// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAFF0 rf_event_mover_pause_create
// UNREALRED VERIFIED [mission-mover-events-20261020] Builds type72 Mover_Pause with no additional event-specific generic parameters. Its two vtable handlers at0x63E3AC +4/+8 are0x501580 pause and0x5015F0 resume.
int __cdecl rf_event_mover_pause_create(float *a1)
{
  return rf_mission_event_create_at_position(a1, 0x48u);
}

