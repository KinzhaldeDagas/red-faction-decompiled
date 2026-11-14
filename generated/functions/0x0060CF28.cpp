// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CF28 __unlock_file
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE. Same unsigned INCLUSIVEstaticaddress
// test664DE0..665040,withoutalignmentvalidation. Staticroute FIRSTclearflags0x8000 thenunlock(16+ARITHMETIC((ptr-base)>>5));dynamicrouteLeaveCriticalSection(FILE+32),no bitclear.
// NoNULL/owner/held-state validation or normalizedresult.
void __cdecl _unlock_file(FILE *Stream)
{
  if ( Stream < (FILE *)&off_664DE0 || Stream > &stru_665040 )
  {
    LeaveCriticalSection((LPCRITICAL_SECTION)&Stream[1]);
  }
  else
  {
    Stream->_flag &= ~0x8000u;
    _unlock((((char *)Stream - (char *)&off_664DE0) >> 5) + 16);
  }
}

