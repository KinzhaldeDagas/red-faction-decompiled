// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057EA20 rf_renderer_stretched_diamond_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Backend102 forwards twoDWORDs,float,and stateDWORD to textured stretched-diamond renderer. Unsupported backend returns backend integer,no draw. Nominal integer result not uniform success status.
int __cdecl rf_renderer_stretched_diamond_backend_wrapper(int a1, int a2, float a3, int a4)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_draw_textured_stretched_diamond(a1, a2, a3, a4);
  return result;
}

