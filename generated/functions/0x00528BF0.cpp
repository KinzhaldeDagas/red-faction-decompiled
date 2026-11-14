// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00528BF0 rf_light_clear_active_world_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No args void. Store validityBYTE D035FC=0 then countDWORD D035E8=0. Does not clear pointer array contents, light records,candidate caches,serial,master flag or diagnostics. Same effects as distinct address528C20.
void rf_light_clear_active_world_list()
{
  unk_D035FC = 0;
  rf_light_active_world_count = 0;
}

