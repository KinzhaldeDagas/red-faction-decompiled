// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571F50 rf_bitmap_mark_renderer_dirty_backend_dispatch
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: If backend selector0x187CC9C==102, delegates bitmap handle to0x5E3D60, setting dirty and invalidating matching texture-stage bindings. Other backends return selector unchanged without marking. Return not a reliable boolean.
int __cdecl rf_bitmap_mark_renderer_dirty_backend_dispatch(unsigned int a1)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_d3d8_bitmap_mark_dirty_invalidate_stage_bindings(a1);
  return result;
}

