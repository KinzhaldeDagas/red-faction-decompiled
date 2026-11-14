// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460580 rf_inline_dword_array20_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): ECX fixed inline DWORD array(count0,elements4),rawDWORD stack arg,RET4. Reject ONLY count==EXACT20 withEAX-1;otherwise save oldcount,increment BEFORE write
// atthis+4+4*oldcount,returnoldcount. Negative/>20 counts not rejected;no allocation,ownership,NULL/dedup guard. Menu hit-list6F49A8 uses it;physical structure is inline elements,not
// a heap backing-pointer field.
int __thiscall rf_inline_dword_array20_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 20 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

