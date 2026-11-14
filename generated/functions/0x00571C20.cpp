// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571C20 rf_renderer_reset_viewport_full_screen
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Calls set_viewport(0,0,physicalWidth187CC94,physicalHeight187CC98). Resets relative clip state and, for backend102, applies device viewport. Return follows setter.
int __cdecl rf_renderer_reset_viewport_full_screen()
{
  return rf_renderer_set_viewport_and_relative_clip(0, 0, dword_187CC94, dword_187CC98);
}

