// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F950 rf_inline_dword_array30_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX fixed inline DWORD array(count0,elements4),rawDWORD stack arg,RET4. Reject ONLY count==EXACT30 withEAX-1. Else save oldcount,increment BEFORE element write
// atthis+4+4*oldcount,returnoldcount. Negative or >30 counts not rejected;no allocation,dedup,ownership or NULL check. Advanced rule draw-list6F4298 uses it;initializer does not
// check each append result.
int __thiscall rf_inline_dword_array30_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 30 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

