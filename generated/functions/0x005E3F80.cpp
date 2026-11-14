// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3F80 rf_d3d8_bitmap_unlock_tile_pixels
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Resolves descriptorhandle again through0x574B80,decrements16-bit rendererlockcount+8 BEFORE textureunlock,then calls tiletexture vtable+68 level0. NegativeHRESULT converted0; nonnegativeHRESULT returnedunchanged,so usualsuccess0 is indistinguishable fromfailure byreturnalone. No underflow,tileindex,descriptorownership or lockmatching guard; animatedhandle can resolve again.
int __cdecl rf_d3d8_bitmap_unlock_tile_pixels(unsigned int *a1)
{
  int result; // eax
  char *v2; // [esp+4h] [ebp-8h]

  v2 = (char *)dword_1E01548 + 16 * rf_bitmap_resolve_current_frame_slot(*a1);
  --*((_WORD *)v2 + 4);
  result = (*(int (__stdcall **)(_DWORD, _DWORD))(**(_DWORD **)(32 * a1[1] + *((_DWORD *)v2 + 3)) + 68))(
             *(_DWORD *)(32 * a1[1] + *((_DWORD *)v2 + 3)),
             0);
  if ( result < 0 )
    return 0;
  return result;
}

