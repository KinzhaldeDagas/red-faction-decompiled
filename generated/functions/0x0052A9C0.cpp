// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A9C0 rf_renderer_enable_world_lighting
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No argsvoid, write DWORD masterenabled663B14=1 only. No runtime argument setup despite inherited ___setargv_0 label. No cache invalidation,serial increment,list allocation or active rebuild.
void rf_renderer_enable_world_lighting()
{
  rf_renderer_lights_enabled = 1;
}

