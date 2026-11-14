// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576450 rf_bitmap_get_resolved_dimensions
// UNREALRED VERIFIED [renderer-polygons-20261028]: Resolves bitmap/frame through0x574B80. Index-1 writes width=height=0 and returns-1. Otherwise reads unsigned16 width/height at108-byte bitmap record0x1897344+108*index offsets44/46,writes both,and returns height. Does not otherwise validate index or output pointers. Resolving animation may mutate global/frame state.
int __cdecl rf_bitmap_get_resolved_dimensions(unsigned int a1, _DWORD *a2, int *a3)
{
  int result; // eax

  result = rf_bitmap_resolve_current_frame_slot(a1);
  if ( result == -1 )
  {
    *a3 = 0;
    *a2 = 0;
  }
  else
  {
    *a2 = *(unsigned __int16 *)(dword_1897344 + 108 * result + 44);
    result = *(unsigned __int16 *)(dword_1897344 + 108 * result + 46);
    *a3 = result;
  }
  return result;
}

