// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005078C0 sub_5078C0
// UNREALRED VERIFIED [combat-particle-vbm-20261104]: Lazy VBM load resolves definition filename+0x0C via5763A0 into handle+0x14, framecount+0x18, FPS+0x1C, then warms each drawableframe. Invalidhandle-1 is not a synthetic one-frame image. Caller506E20 subsequently skips unavailable VBM while continuing independent representations.
char *__cdecl sub_5078C0(int a1)
{
  char *result; // eax
  char *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  char *v4; // [esp+4h] [ebp-4h]

  result = (char *)&unk_90DC80 + 224 * a1;
  v4 = result;
  if ( *((_DWORD *)result + 5) == -1 )
  {
    v2 = (char *)rf_string_object_c_str_or_empty(result + 12);
    result = (char *)rf_bitmap_vbm_sequence_load(v2, (_DWORD *)v4 + 6, (_DWORD *)v4 + 7);
    *((_DWORD *)v4 + 5) = result;
    if ( *((_DWORD *)v4 + 5) != -1 )
    {
      for ( i = 0; i < *((_DWORD *)v4 + 6); ++i )
      {
        rf_renderer_bind_texture_for_level_warmup(i + *((_DWORD *)v4 + 5));
        result = (char *)(i + 1);
      }
    }
  }
  return result;
}

