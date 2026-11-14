// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570F70 rf_renderer_get_physical_screen_height
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. Returns signed DWORD187CC98 throughEAX. Does not include viewport clipping or popup desktop-size expansion; no mutation/device query.
int __cdecl rf_renderer_get_physical_screen_height()
{
  return dword_187CC98;
}

