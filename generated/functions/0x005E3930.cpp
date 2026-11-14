// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E3930 rf_renderer_bind_texture_handle
// UNREALRED VERIFIED [general-gap-20260830]: Resolves and binds a renderer texture handle, ensuring its cache entry is resident and optionally selecting a subimage. A negative handle unbinds the requested stage and returns success.
int __cdecl rf_renderer_bind_texture_handle(int a1, int a2, int a3, float *a4, float *a5, char a6)
{
  int *v7; // [esp+0h] [ebp-8h]
  int v8; // [esp+4h] [ebp-4h]

  if ( a2 >= 0 )
  {
    v8 = rf_bitmap_resolve_current_frame_slot(a2);
    if ( rf_d3d8_texture_stage_cache_matches((int)&unk_1E01550[6 * a1], v8, a3, a4, a5) )
    {
      if ( !unk_1E014E5 && !unk_1E014E6 )
        rf_renderer_begin_immediate_buffers(4, 3);
      return 1;
    }
    else
    {
      if ( !unk_1E014E6 )
        rf_renderer_begin_immediate_buffers(4, 3);
      v7 = (int *)((char *)dword_1E01548 + 16 * v8);
      if ( *v7 < 0 || *v7 != a2 )
      {
        if ( !rf_d3d8_texture_cache_rebuild_from_bitmap(a2, (int)v7) )
          return 0;
        *((_BYTE *)v7 + 11) = 0;
      }
      if ( !*((_BYTE *)v7 + 11) || rf_d3d8_texture_cache_rebuild_from_bitmap(a2, (int)v7) )
      {
        if ( a6 )
        {
          if ( a3 >= 0 && a3 < *((__int16 *)v7 + 2) )
          {
            rf_d3d8_texture_stage_bind_cached_tile((int)&unk_1E01550[6 * a1], (int)v7, a3, a4, a5);
            return 1;
          }
          else
          {
            return 0;
          }
        }
        else
        {
          return 1;
        }
      }
      else
      {
        return 0;
      }
    }
  }
  else
  {
    if ( !unk_1E014E6 )
      rf_renderer_begin_immediate_buffers(4, 3);
    rf_renderer_unbind_texture_stage(&unk_1E01550[6 * a1]);
    return 1;
  }
}

