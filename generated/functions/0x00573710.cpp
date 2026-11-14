// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573710 rf_renderer_set_cached_screen_dimensions
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Starts with requested width,height,bpp; bpp<8 uses prior bpp. Only backend102 can succeed: forces depth32 and calls always-true display-mode stub; encoded fallback depth16 cannot occur with this stub. Stores physical width/height, bpp and bytesPerPixel=(bpp+7)/8, resets full viewport and returns1. Other backends return0 without updating dimensions. No width/height validation or device Reset in this body; this function alone does not recreate the device.
char __cdecl rf_renderer_set_cached_screen_dimensions(int a1, int a2, int a3)
{
  char v4; // [esp+7h] [ebp-1h]

  if ( a3 < 8 )
    a3 = dword_187CCB0;
  v4 = 0;
  if ( dword_187CC9C == 102 )
  {
    a3 = 32;
    v4 = rf_d3d8_display_mode_check_stub_true();
    if ( !v4 )
    {
      a3 = 16;
      v4 = rf_d3d8_display_mode_check_stub_true();
    }
  }
  if ( !v4 )
    return 0;
  dword_187CC94 = a1;
  dword_187CC98 = a2;
  dword_187CCB0 = a3;
  unk_187CCB4 = (a3 + 7) / 8;
  rf_renderer_reset_viewport_full_screen();
  return 1;
}

