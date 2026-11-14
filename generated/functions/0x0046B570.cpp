// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B570 rf_inline_dword_array35_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): ECX fixed inline DWORD array(count0,elements4),rawDWORD stack arg,RET4. Reject ONLY count==EXACT35 (23h) withEAX-1. Otherwise save oldcount,increment
// BEFORE write atthis+4+4*oldcount,return oldcount. Negative/>35 counts bypass guard;no allocation,NULL/ownership/dedup checks. Performance draw/focus lists use this
// specialization;append results ignored in builder.
int __thiscall rf_inline_dword_array35_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 35 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

