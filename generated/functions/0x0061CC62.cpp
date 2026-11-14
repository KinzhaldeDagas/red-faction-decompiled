// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061CC62 __set_abort_behavior
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl flags/mask. Snapshot oldDWORD666050 intoEAX. Store (flags&mask)|(old&~mask),return OLD value,not new. No
// validation/encoding/callback/lock/atomicRMW;32-bit bitmask update preserves unselected bits from same snapshot.
unsigned int __cdecl _set_abort_behavior(unsigned int Flags, unsigned int Mask)
{
  unsigned int result; // eax

  result = dword_666050;
  dword_666050 = Mask & Flags | dword_666050 & ~Mask;
  return result;
}

