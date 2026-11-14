// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573CC0 rf_renderer_set_mip_filter_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): If active renderer backend code187CC9C==102, calls D3D mip-filter setter5C5890 with selector. Other backends perform no device update and return the backend code. Inferred return is not a uniform success boolean.
int __cdecl rf_renderer_set_mip_filter_backend_dispatch(int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_set_stage0_mip_filter(a1);
  return result;
}

