// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005731E0 rf_renderer_texture_mode_supported_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Backend102 queries rf_d3d8_texture_mode_supported(descriptor). Backend104 unconditionally returns true; all other backends return false. No descriptor mutation.
char __cdecl rf_renderer_texture_mode_supported_dispatch(int a1)
{
  if ( dword_187CC9C == 102 )
    return rf_d3d8_texture_mode_supported(a1);
  else
    return dword_187CC9C == 104;
}

