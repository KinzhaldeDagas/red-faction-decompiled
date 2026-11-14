// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046CD40 rf_inline_dword_array28_append
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): ECX fixed inline DWORD array count0/elements4,rawDWORD stack arg,RET4. Reject ONLY count==EXACT28 (1Ch),EAX-1. Else save oldcount,increment BEFORE
// write atthis+4+4*oldcount,returnoldcount. Negative/>28 bypass;no allocation,NULL/dedup/ownership checks. Gameplay draw/focus lists6F8320/6F8398 use this specialization;builder
// ignores results.
int __thiscall rf_inline_dword_array28_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 28 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

