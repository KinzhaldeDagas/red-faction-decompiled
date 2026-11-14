// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CBB0 rf_inline_dword_array32_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): ECX inline DWORD array count0/elements4,rawDWORD stack arg,RET4. Reject ONLY count==EXACT32 returning-1. Otherwise save oldcount,increment count BEFORE write
// atthis+4+4*oldcount,return oldcount. Negative/>32 counts bypass guard. No allocation,NULL/dedup/ownership checks;browser draw/focus lists6F5B90/6F5C60 use this capacity32
// specialization.
int __thiscall rf_inline_dword_array32_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 32 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

