// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3DC0 rf_d3d8_bitmap_lock_tile_pixels
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Resolves bitmap/frame0x574B80 into16-byte rendererdescriptor0x1E01548. If signedtilecount+4<1 or cachedhandle+0 differs,ensures texture through0x5E3AB0; failure returns0. Locks tile GPUtexture level0 via vtable+64,flags0,wholerectangle; negativeHRESULT returns0. Increments16-bit lockcount+8,queries leveldescriptor vtable+56. Writes caller32-byte lockdescriptor: handle+0,tile+4,internalpixelformat+8,pixels+12,width+16,height+20,pitchbytes+24; leaves caller mode+28 intact. GPUformat numeric20->internal6,21/22->7,23->3,24/25->5,26/30->4; unknown callsfataldiagnostic at gr_direct3d_texture.cpp1440. Returns1 after setup. No tileindex/resolverbounds or levelqueryresult check; lockcount not rolledback on laterfatalpath.
char __cdecl rf_d3d8_bitmap_lock_tile_pixels(unsigned int a1, unsigned int a2, unsigned int *a3)
{
  char *v4; // [esp+4h] [ebp-34h]
  _DWORD v5[8]; // [esp+Ch] [ebp-2Ch] BYREF
  int v6; // [esp+2Ch] [ebp-Ch]
  _DWORD v7[2]; // [esp+30h] [ebp-8h] BYREF

  v6 = rf_bitmap_resolve_current_frame_slot(a1);
  v4 = (char *)dword_1E01548 + 16 * v6;
  if ( (*((__int16 *)v4 + 2) < 1 || *(_DWORD *)v4 != a1) && !rf_d3d8_texture_cache_rebuild_from_bitmap(a1, (int)v4) )
    return 0;
  if ( (*(int (__stdcall **)(_DWORD, _DWORD, _DWORD *, _DWORD, _DWORD))(**(_DWORD **)(32 * a2 + *((_DWORD *)v4 + 3)) + 64))(
         *(_DWORD *)(32 * a2 + *((_DWORD *)v4 + 3)),
         0,
         v7,
         0,
         0) < 0 )
    return 0;
  ++*((_WORD *)v4 + 4);
  (*(void (__stdcall **)(_DWORD, _DWORD, _DWORD *))(**(_DWORD **)(32 * a2 + *((_DWORD *)v4 + 3)) + 56))(
    *(_DWORD *)(32 * a2 + *((_DWORD *)v4 + 3)),
    0,
    v5);
  *a3 = a1;
  a3[3] = v7[1];
  a3[5] = v5[7];
  a3[4] = v5[6];
  a3[1] = a2;
  a3[6] = v7[0];
  switch ( v5[0] )
  {
    case 0x14:
      a3[2] = 6;
      break;
    case 0x15:
    case 0x16:
      a3[2] = 7;
      break;
    case 0x17:
      a3[2] = 3;
      break;
    case 0x18:
    case 0x19:
      a3[2] = 5;
      break;
    case 0x1A:
    case 0x1E:
      a3[2] = 4;
      break;
    default:
      rf_fatal_error_show_message_and_exit(
        "D:\\projects\\rf_pc\\vsdk\\gr\\directx\\gr_direct3d_texture.cpp",
        1440,
        "Bad pixel format in gr_direct3d_lock call!");
  }
  return 1;
}

