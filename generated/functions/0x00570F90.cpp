// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570F90 rf_renderer_get_backend_selector
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. Returns context backend DWORD187CC9C directly;generic initializer normalizes original106 to102 before storing. No hardware/device query,ready gate or mutation.
int rf_renderer_get_backend_selector()
{
  return dword_187CC9C;
}

