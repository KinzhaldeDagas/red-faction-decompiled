// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A9E0 rf_renderer_world_lighting_enabled
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, light handle/pool lifecycle,cache generations,active-list filters and trig extent,original ECX/stack flow and PE bytes): No args, return normalizedALbool from DWORDmasterenabled663B14!=0. Does not consult suppression663B0C,categoryallow663B10, activecount or validity. No sideeffects.
bool rf_renderer_world_lighting_enabled()
{
  return rf_renderer_lights_enabled != 0;
}

