// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB4C0 rf_rfa_register_preloaded_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Gets/creates clip byname. Existing nonNULL raw pointer causes CRT free(Block) on NEW supplied buffer and returnsNULL, even if ownership of supplied pointer was not separately checked; no replacement. Empty entry stores supplied byte count+104,pointer+120,ownership byte+108=1 and returns entry. Does not validate buffer/header/count, increment registration/action refs or ensure supplied buffer is nonNULL. No image xrefs observed in current database.
char *__cdecl rf_rfa_register_preloaded_buffer(char *a1, void *Block, int a3)
{
  char *v4; // [esp+0h] [ebp-4h]

  v4 = rf_animation_clip_pool_get_or_create(a1);
  if ( *((_DWORD *)v4 + 30) )
  {
    free(Block);
    return nullptr;
  }
  else
  {
    *((_DWORD *)v4 + 26) = a3;
    *((_DWORD *)v4 + 30) = Block;
    v4[108] = 1;
    return v4;
  }
}

