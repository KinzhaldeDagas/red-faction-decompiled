// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DBE0 rf_corpse_find_oldest_evictable
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): First calls full evictable count and returns0 if empty; otherwise walks list again with same retiring/protection filters. First eligible becomes candidate; replacement requires candidate creation float+660 ORDERED > incoming creation float. Equal times preserve first insertion-order candidate; NaN comparison does not replace, so first eligible NaN remains sticky. Returns pointer/0; no sorting, mutation, finite guard or whole-list snapshot.
int rf_corpse_find_oldest_evictable()
{
  int v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( !rf_corpse_count_evictable() )
    return 0;
  v1 = 0;
  for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
  {
    if ( !(unsigned __int8)rf_corpse_is_retiring(i) && !rf_corpse_is_eviction_protected(i) )
    {
      if ( v1 )
      {
        if ( *(float *)(v1 + 660) > (double)*(float *)(i + 660) )
          v1 = i;
      }
      else
      {
        v1 = i;
      }
    }
  }
  return v1;
}

