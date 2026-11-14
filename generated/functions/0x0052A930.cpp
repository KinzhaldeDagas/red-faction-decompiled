// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A930 rf_renderer_get_light_change_serial
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Returns global renderer_light_change_serial DWORD; no increment or cache invalidation. Solid debug draw compares it with Solid884.
unsigned int rf_renderer_get_light_change_serial()
{
  return rf_renderer_light_change_serial;
}

