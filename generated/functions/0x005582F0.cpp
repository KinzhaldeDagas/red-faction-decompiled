// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005582F0 rf_render_pass_reset_counter_and_flags
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Called by solid debug draw and world rendering. Saves DWORD17F10A0, raises17F10A4 if saved count greater, writes byte17F109D=0, count17F10A0=0, byte17F109C=1, returns saved count. This evidence proves counter/flag reset, not semantic identity of cached records or vertex sharing.
int rf_render_pass_reset_counter_and_flags()
{
  int result; // eax

  result = dword_17F10A0;
  if ( dword_17F10A0 > dword_17F10A4 )
    dword_17F10A4 = dword_17F10A0;
  unk_17F109D = 0;
  dword_17F10A0 = 0;
  unk_17F109C = 1;
  return result;
}

