// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7BA0 rf_object_liquid_state_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): One required common-object pointer. Reads cached room pointer from object DWORD+0 through thiscall486DE0. If nonnull, calls liquid-room point
// predicate with ECX=room and one stack pointer object+60; tests only AL, any nonzero admits. Sets common DWORD+124 bit0x80000 on admission; otherwise clears that bit, preserving
// every other bit. Returns the updated flags in EAX. No object null guard or independent liquid-height calculation.
unsigned int __cdecl rf_object_liquid_state_update(_DWORD *a1)
{
  unsigned int result; // eax
  int first_dword; // [esp+0h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(a1);
  if ( first_dword && rf_liquid_room_contains_point(first_dword, (int)(a1 + 15)) )
  {
    result = a1[31] | 0x80000;
    a1[31] = result;
  }
  else
  {
    result = a1[31] & 0xFFF7FFFF;
    a1[31] = result;
  }
  return result;
}

