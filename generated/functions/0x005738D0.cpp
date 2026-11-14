// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005738D0 rf_renderer_suspend_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Recovered no-argument routine. When current backend187CC9C!=0, saves it at182AB90 then sets current backend0, disabling dispatch. Repeated suspension while already0 leaves saved code intact. No device release or nesting counter.
void __cdecl rf_renderer_suspend_backend_dispatch()
{
  if ( dword_187CC9C )
  {
    dword_182AB90 = dword_187CC9C;
    dword_187CC9C = 0;
  }
}

