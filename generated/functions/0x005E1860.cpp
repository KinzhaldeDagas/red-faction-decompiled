// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E1860 rf_d3d8_texture_cache_age_or_release_all
// UNREALRED VERIFIED [image-headers-20261028]: Unbinds both stage caches if device0x1DAEDC4 nonnull. Force byte nonzero: releases all entries with signed tilecount>0,sets handle-1,reference byte10=0,ageWORD6=0. Force0: resident age nonzero decremented and retained; zero age and zero reference releases tiles and handle. Lockcount not consulted before release. Ends device vtable+20 call argument0 and returns its result, not released count; this FINAL device call is unconditional even if device null. No array/null/count validation; entries with nonpositive signed tilecount skipped.
int __cdecl rf_d3d8_texture_cache_age_or_release_all(char a1)
{
  int v2; // [esp+0h] [ebp-Ch]
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+4h] [ebp-8h]
  int k; // [esp+4h] [ebp-8h]
  int v6; // [esp+8h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( dword_1DAEDC4 )
      rf_renderer_unbind_texture_stage(&unk_1E01550[6 * i]);
  }
  v6 = 0;
  v2 = 0;
  if ( a1 )
  {
    for ( j = 0; j < dword_663F14; ++j )
    {
      if ( *(__int16 *)(unk_1E01548 + 16 * j + 4) > 0 )
      {
        ++v6;
        rf_d3d8_texture_cache_release_tiles(unk_1E01548 + 16 * j);
        *(_DWORD *)(unk_1E01548 + 16 * j) = -1;
        *(_BYTE *)(unk_1E01548 + 16 * j + 10) = 0;
        *(_WORD *)(unk_1E01548 + 16 * j + 6) = 0;
      }
    }
  }
  else
  {
    for ( k = 0; k < dword_663F14; ++k )
    {
      if ( *(__int16 *)(unk_1E01548 + 16 * k + 4) > 0 )
      {
        if ( *(_WORD *)(unk_1E01548 + 16 * k + 6) )
        {
          ++v2;
          --*(_WORD *)(unk_1E01548 + 16 * k + 6);
        }
        else if ( !*(_BYTE *)(unk_1E01548 + 16 * k + 10) )
        {
          ++v6;
          rf_d3d8_texture_cache_release_tiles(unk_1E01548 + 16 * k);
          *(_DWORD *)(unk_1E01548 + 16 * k) = -1;
        }
      }
    }
  }
  return (*(int (__stdcall **)(int, _DWORD))(*(_DWORD *)dword_1DAEDC4 + 20))(dword_1DAEDC4, 0);
}

