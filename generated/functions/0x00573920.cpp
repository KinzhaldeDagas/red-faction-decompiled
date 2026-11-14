// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573920 rf_bitmap_capture_backbuffer_into_bitmap
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Arguments x,y,width,height,destinationBitmap. Backend102 gets destination dimensions, locks tile0 mode2, allocates4*bitmapWidth*bitmapHeight bytes, and calls readback with (x,y,x+width,y+height,temp), despite decoded callee expecting width/height rather than end coordinates. For returned RF format7 sets alpha255 over width*height pixels, converts the ENTIRE bitmap area into locked destination format, frees temp and unlocks. No malloc, readback-status, area consistency or overflow checks. Other backends lock destination, write return0 from readback dispatcher into lock format field and unlock. Return byte is lock/unlock result, not confirmed capture success.
char __cdecl rf_bitmap_capture_backbuffer_into_bitmap(int a1, int a2, int a3, int a4, unsigned int a5)
{
  char result; // al
  int v6; // [esp+4h] [ebp-5Ch] BYREF
  unsigned int v7[8]; // [esp+8h] [ebp-58h] BYREF
  int v8; // [esp+28h] [ebp-38h] BYREF
  int i; // [esp+2Ch] [ebp-34h]
  void *Block; // [esp+30h] [ebp-30h]
  int backbuffer_rectangle_dispatch; // [esp+34h] [ebp-2Ch]
  int v12; // [esp+38h] [ebp-28h] BYREF
  unsigned int v13[8]; // [esp+3Ch] [ebp-24h] BYREF
  int v14; // [esp+5Ch] [ebp-4h] BYREF

  if ( dword_187CC9C == 102 )
  {
    rf_bitmap_get_resolved_dimensions(a5, &v12, &v14);
    result = rf_bitmap_lock_pixels_backend_dispatch(a5, 0, v13, 2u);
    if ( result )
    {
      Block = malloc(4 * v14 * v12);
      backbuffer_rectangle_dispatch = rf_renderer_read_backbuffer_rectangle_dispatch(a1, a2, a3 + a1, a4 + a2, Block);
      if ( backbuffer_rectangle_dispatch == 7 )
      {
        for ( i = 0; i < 4 * a4 * a3; i += 4 )
          *((_BYTE *)Block + i + 3) = -1;
      }
      rf_bitmap_convert_pixel_run_selected_formats(
        (void *)v13[3],
        (void *)v13[2],
        (unsigned __int8 *)Block,
        (void *)backbuffer_rectangle_dispatch,
        v14 * v12);
      free(Block);
      return rf_bitmap_unlock_pixels_backend_dispatch(v13);
    }
  }
  else
  {
    rf_bitmap_get_resolved_dimensions(a5, &v6, &v8);
    result = rf_bitmap_lock_pixels_backend_dispatch(a5, 0, v7, 2u);
    if ( result )
    {
      v7[2] = rf_renderer_read_backbuffer_rectangle_dispatch(a1, a2, a3 + a1, a4 + a2, (void *)v7[3]);
      return rf_bitmap_unlock_pixels_backend_dispatch(v7);
    }
  }
  return result;
}

