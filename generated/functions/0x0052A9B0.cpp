// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A9B0 rf_renderer_disable_world_lighting
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No argsvoid. Write DWORD masterenabled663B14=0 andreturn; no active validity/count clear,serial increment,candidate flush,record/list free or receiver-coverage mutation. Existing builders return0 immediately while disabled but can leave older active list/count intact.
void rf_renderer_disable_world_lighting()
{
  rf_renderer_lights_enabled = 0;
}

