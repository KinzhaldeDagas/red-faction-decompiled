// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573900 rf_renderer_resume_backend_dispatch_and_present
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Recovered no-argument routine. Restores current backend from182AB90 unconditionally and invokes present_with_full_viewport. No initialized/saved-value guard or counter. Old false thiscall prototype on present wrapper produced an uninitialized-ECX pseudocode argument; actual caller passes no arguments.
void __cdecl rf_renderer_resume_backend_dispatch_and_present()
{
  dword_187CC9C = dword_182AB90;
  rf_renderer_present_with_full_viewport();
}

