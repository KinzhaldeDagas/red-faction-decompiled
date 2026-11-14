// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CC00 rf_inline_dword8_append_unless_exact_full
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Thiscall inline DWORD list, one DWORD value, RET4. Reject ONLY current DWORD count==EXACT8 with EAX-1 and no
// write. Otherwise snapshot old count, store wrapped count+1 FIRST, write raw value to receiver+4+4*oldCount, return old countEAX. Negative and>8 counts are not rejected; count-1
// aliases the count DWORD, so final count becomes supplied value. No allocation, generic bounded-container admission, rollback or input validation.
int __thiscall rf_inline_dword8_append_unless_exact_full(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 8 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

