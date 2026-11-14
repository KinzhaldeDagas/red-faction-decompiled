// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528CB0 rf_light_get_active_world_count
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No args, load rawDWORD D035E8 intoEAX andreturn. No check of validityBYTE D035FC, masterenable or suppression; can report stale count after a gated active-list builder returned0 without clearing state.
unsigned int rf_light_get_active_world_count()
{
  return rf_light_active_world_count;
}

