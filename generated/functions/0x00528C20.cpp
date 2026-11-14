// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528C20 rf_light_invalidate_active_world_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No args void, plainRET. WriteBYTE D035FC=0 thenDWORD activeCountD035E8=0; leave active pointers beyond count untouched. No serial bump or candidate cache eviction. Allocation and every release call this; setters in this batch generally change serial/coverage without this call. Separate identical body528BF0 retained.
void rf_light_invalidate_active_world_list()
{
  unk_D035FC = 0;
  rf_light_active_world_count = 0;
}

