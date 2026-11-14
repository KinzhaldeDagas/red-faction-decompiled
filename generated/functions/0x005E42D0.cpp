// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E42D0 rf_d3d8_bitmap_texture_release_reference
// UNREALRED VERIFIED [texture-upload-20261028]: EnsureswarmupbindingFIRST,thenresolvescacheentry,decrementsbyte+10withwrap. Onlywhennewbyte0,releasestiles0x5E1A30 andsets handle-1,WORD+6=0,refbyte+10=0. Returnsentrypointer. No underflow/ownershipcheck orbindingfailurehandling; ref0beforecallwraps255anddoesnotrelease.
char *__cdecl rf_d3d8_bitmap_texture_release_reference(unsigned int a1)
{
  char *result; // eax
  char *v2; // [esp+0h] [ebp-8h]

  rf_renderer_bind_texture_for_level_warmup(a1);
  v2 = (char *)dword_1E01548 + 16 * rf_bitmap_resolve_current_frame_slot(a1);
  --v2[10];
  result = v2;
  if ( !v2[10] )
  {
    rf_d3d8_texture_cache_release_tiles((int)v2);
    *(_DWORD *)v2 = -1;
    *((_WORD *)v2 + 3) = 0;
    v2[10] = 0;
    return v2;
  }
  return result;
}

