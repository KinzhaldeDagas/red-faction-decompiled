// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00455FB0 rf_inline_dword_array10_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): ECX fixed inline DWORD array(count0,elements4),rawDWORD stack arg,RET4. EXACT count10 ->EAX-1,no mutation;all other count values save oldcount,increment then write
// elements[oldcount]=arg,returnoldcount. No count>=10,negative,overflow,NULL,allocation or ownership guard. Used by advanced rule focus-array6F4358;does not dynamically grow or check
// a separate capacity field.
int __thiscall rf_inline_dword_array10_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 10 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

