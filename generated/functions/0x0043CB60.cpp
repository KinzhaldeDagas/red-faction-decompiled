// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CB60 rf_inline_dword2_append_unless_exact_full
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall inline DWORD list, one DWORD value, RET4. Reject ONLY when current DWORD count==EXACT2, returning
// EAX-1 with no write. Every other count, including negative or>2, is accepted: snapshot old count, store count+1 with32-bit wrap FIRST, write value at receiver+4+4*oldCount, return
// old countEAX. No greater-than/negative/capacity/allocation check. With count-1, element store aliases count at receiver0 and replaces the increment with input value;
// partial/corrupt counts preserve native address arithmetic.
int __thiscall rf_inline_dword2_append_unless_exact_full(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 2 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

