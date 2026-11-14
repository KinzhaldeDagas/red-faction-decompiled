// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060DC04 __initp_misc_cfltcvt_tab
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Iterate EXACT10 DWORD slots665060..665084 in ascending4-byte order; for each load current pointer, encode_pointer it, write encodedEAX back to
// same slot. Returns last encoding EAX. No once flag, lock, NULL skip, original-copy table or double-encoding prevention. Reinvocation encodes already-stored values; helper
// provider/fallback controls transformation.
int (*_initp_misc_cfltcvt_tab())()
{
  unsigned int i; // edi
  int (**v1)(); // esi
  int (*result)(); // eax

  for ( i = 0; i < 10; ++i )
  {
    v1 = &off_665060[i];
    result = (int (*)())_encode_pointer(off_665060[i]);
    *v1 = result;
  }
  return result;
}

