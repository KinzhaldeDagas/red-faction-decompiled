// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045DEC0 rf_inline_dword_array25_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX fixed inline DWORD array {count0,elements4},one rawDWORD stack argument,RET4. Only count==EXACT25 rejects withEAX-1 and no write;no signed-negative or count>25
// bound. Otherwise save oldcount,increment count BEFORE writing element[oldcount]=argument,return oldcount. No allocation,ownership/reference management,deduplication or NULL
// admission. Used by setup draw-control list6F3788;does not itself initialize count or enforce a dynamic capacity field.
int __thiscall rf_inline_dword_array25_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 25 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

