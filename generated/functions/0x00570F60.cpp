// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570F60 rf_renderer_get_physical_screen_width
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. Returns signed DWORD187CC94 throughEAX. Physical requested screen width,not current effective viewport/clip widthCCC4; no clamp/device query or initialization.
int rf_renderer_get_physical_screen_width()
{
  return dword_187CC94;
}

