// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00454570 rf_inline_dword_array5_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): ECX fixed inline DWORD array count0/elements4,rawDWORD stack arg,RET4. Reject ONLY count==EXACT5 with-1. Else save oldcount,increment beforewrite
// atthis+4+4*oldcount,returnoldcount. No count>=5/negative/overflow guard,allocation,dedup,ownership or NULL checks. Profile focus-list6F5028 uses it;does not maintain a heap data
// pointer.
int __thiscall rf_inline_dword_array5_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 5 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

