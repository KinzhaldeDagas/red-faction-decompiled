// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CF64 __unlock_file2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl signedindex,FILE. Signedindex<20 clearsFILEflags0x8000
// BEFOREunlock(index+16);index>=20 LeaveCriticalSection(FILE+32). Negativeindices notclamped, pointer/index relationship unchecked; no independently tracked lockcount.
void __cdecl _unlock_file2(int a1, int a2)
{
  if ( a1 >= 20 )
  {
    LeaveCriticalSection((LPCRITICAL_SECTION)(a2 + 32));
  }
  else
  {
    *(_DWORD *)(a2 + 12) &= ~0x8000u;
    _unlock(a1 + 16);
  }
}

