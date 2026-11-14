// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487360 rf_waypoint_list_count_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl no arguments. Returns raw DWORD700478 without mutation or validation. Neighboring registry initializer resets it; route caller40DCA0 uses returned count to bound
// waypoint-list index into524-byte records700480 before validating point count/cursor. Does not return current list point count or resolve an entity/route itself.
int rf_waypoint_list_count_get()
{
  return dword_700478;
}

