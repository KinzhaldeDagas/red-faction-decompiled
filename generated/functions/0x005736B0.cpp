// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005736B0 rf_bitmap_sample_wrapped_uv_rgba_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Backend102 forwards bitmap, float U/V and output RGBA pointer to tile0 wrapped-UV sampler. Other backends write opaque white (255,255,255,255) to output via color helper. Returns output/helper pointer; no NULL check.
_BYTE *__cdecl rf_bitmap_sample_wrapped_uv_rgba_dispatch(unsigned int a1, float a2, float a3, _BYTE *a4)
{
  if ( dword_187CC9C == 102 )
    return rf_d3d8_sample_bitmap_tile0_wrapped_uv_rgba(a1, a2, a3, a4);
  else
    return rf_color4_set_bytes_return_destination(a4, 255, 255, 255, 255);
}

