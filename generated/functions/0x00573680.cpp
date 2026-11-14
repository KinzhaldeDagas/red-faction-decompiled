// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573680 rf_bitmap_unlock_pixels_backend_dispatch
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Backendselector0x187CC9C==102 delegates lockdescriptor to0x5E3F80. Otherbackends return selectorunchanged,possiblynonzero despite no unlock. Caller must not interpret zero uniformlyasfailure: successful deviceunlock can return0.
int __cdecl rf_bitmap_unlock_pixels_backend_dispatch(unsigned int *a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_bitmap_unlock_tile_pixels(a1);
  return result;
}

