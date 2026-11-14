// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416F20 rf_inline_dword_array4_append_unchecked
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): ECX inline array header(count0,entries4..16) plus stackDWORD,RET4. EXACT count==4 returns-1 unchanged. Otherwise index=oldcount;increments count;storesvalue atreceiver+4+4*index,returnsindex. No >=/negative/count/NULL/duplicate/ownership check,allocation or resize. Corrupt count>4 is not safely rejected.
int __thiscall rf_inline_dword_array4_append_unchecked(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 4 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

