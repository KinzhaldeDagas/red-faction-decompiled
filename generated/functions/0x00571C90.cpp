// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571C90 rf_renderer_present_with_full_viewport
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Calls legacy no-op5738C0, resets viewport to full physical screen, then dispatches backend102 to present/recovery5C22C0. Other backends leave backend code in EAX. No ECX/this input is read; inherited thiscall prototype was false and caused a fake uninitialized argument in resume caller573900. Retains incidental int return inference while correcting ABI to no-argument cdecl.
int __cdecl rf_renderer_present_with_full_viewport()
{
  int result; // eax

  rf_renderer_reserved_noop_5738C0();
  rf_renderer_reset_viewport_full_screen();
  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_present_and_recover_device();
  return result;
}

