// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CEF6 __lock_file2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl signedindex,FILE. SIGNEDindex<20
// ->lock(index+16),thenORFILEflags0x8000; index>=20 ->EnterCriticalSection(FILE+32). Negativeindex isNOTrejected,wrappedindex+16 passedunchanged. No crosscheck
// pointermatchesstaticindex, NULL/initialization guard or allocation.
void __cdecl _lock_file2(int a1, int a2)
{
  if ( a1 >= 20 )
  {
    EnterCriticalSection((LPCRITICAL_SECTION)(a2 + 32));
  }
  else
  {
    _lock(a1 + 16);
    *(_DWORD *)(a2 + 12) |= 0x8000u;
  }
}

