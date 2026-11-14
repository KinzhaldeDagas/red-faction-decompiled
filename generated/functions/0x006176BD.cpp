// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006176BD __initp_misc_winsig
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl one rawDWORD. Copy SAME incoming value to globals2021C7C,2021C80,2021C84,2021C88 in that exact order,return new valueEAX. No old-value read, per-slot
// encoding/decoding, callback dispatch, once/lock or specialNULL handling; caller owns representation.
int __cdecl _initp_misc_winsig(int a1)
{
  dword_2021C7C = a1;
  dword_2021C80 = a1;
  dword_2021C84 = a1;
  dword_2021C88[0] = a1;
  return a1;
}

