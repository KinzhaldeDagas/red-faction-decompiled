// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525A70 rf_world_bind_registered_extra_textures
// UNREALRED VERIFIED [level-lifecycle-20261028]: Traverses circular list from0xA7051C, binds each record dword+60 via0x571C60, uses next+224 and stops when next returns to initial head. Null head yields no calls. Does not free list or release handles; return incidental traversal value.
int rf_world_bind_registered_extra_textures()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = unk_A7051C;
  for ( i = unk_A7051C; i; i = v1 )
  {
    rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(i + 60));
    result = i;
    if ( *(_DWORD *)(i + 224) == unk_A7051C )
    {
      v1 = 0;
    }
    else
    {
      result = *(_DWORD *)(i + 224);
      v1 = result;
    }
  }
  return result;
}

