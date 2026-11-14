// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046D9E0 rf_inline_dword_array11_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): ECX fixed inline DWORD array count0/elements4,rawDWORD stack arg,RET4. Reject ONLY count==EXACT11 (0Bh) withEAX-1. Otherwise oldcount saved,count
// incremented BEFORE write atthis+4+4*oldcount,returnoldcount. Negative/>11 counts bypass;no allocation,NULL/dedup/ownership guard. Audio draw/focus lists6F88C4/6F88F4 use it;append
// failures ignored.
int __thiscall rf_inline_dword_array11_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 11 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

