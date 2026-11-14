// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F85F0 rf_named_source_cache_find_exact_pair
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl(name,source). If enabledDWORD0x1F67110==0 returns0. Otherwise traverses circular cache from head0x1F67114 viaDWORDnext136,stops after next==head. Compares source record+144 to arg2 using strcmp,then record+0 to arg1 using strcmp,returns first exact matching record pointer or0. Case-sensitive,no copying,refcount update or NULL/malformed-cycle guard.
int __cdecl rf_named_source_cache_find_exact_pair(const char *a1, const char *a2)
{
  int v3; // [esp+28h] [ebp-8h]
  int i; // [esp+2Ch] [ebp-4h]

  if ( unk_1F67110 )
  {
    for ( i = unk_1F67114; i; i = v3 )
    {
      if ( !strcmp((const char *)(i + 144), a2) && !strcmp((const char *)i, a1) )
        return i;
      if ( *(_DWORD *)(i + 136) == unk_1F67114 )
        v3 = 0;
      else
        v3 = *(_DWORD *)(i + 136);
    }
  }
  return 0;
}

