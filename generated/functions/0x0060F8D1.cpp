// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F8D1 __callnewh
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl sizeDWORD. Decode LIVE global20216F0 handler. NULL decoded ->return0. Otherwise cdecl handler(size),reclaim4 bytes; raw handler0->0,ANY
// nonzero->canonical1. No allocation/retry/free in wrapper, old handler state update or prevalidation ofsize. Encoding provider may identity-fallback per verified decoder; handler
// exceptions delegated.
int __cdecl _callnewh(size_t Size)
{
  int (__cdecl *v1)(size_t); // eax

  v1 = (int (__cdecl *)(size_t))_decode_pointer(unk_20216F0);
  return v1 && v1(Size);
}

