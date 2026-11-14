// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DB30 rf_corpse_count_evictable
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Walks corpse list in next+652 order until sentinel681AF8. Counts only records not retiring(flags668 mask1) AND not protected(flags668 masks2/0x40 OR common124 mask0x4000). Ignores total global count; no mutation, list consistency/null guard or cached-next protection.
int rf_corpse_count_evictable()
{
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = 0;
  for ( i = rf_corpse_list_head; (_UNKNOWN *)i != &unk_681AF8; i = *(_DWORD *)(i + 652) )
  {
    if ( !(unsigned __int8)rf_corpse_is_retiring(i) && !rf_corpse_is_eviction_protected(i) )
      ++v2;
  }
  return v2;
}

