// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CEB5 __lock_file
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE pointer. UNSIGNED address within INCLUSIVE664DE0..665040
// (last static32-byte FILE START) selects lockindex16+ARITHMETIC((ptr-base)>>5);calllock,THENORFILEflags0x8000. Noalignment test,sointerioraddresses withinrange admitted. Outside
// range callEnterCriticalSection(FILE+32),no flagbitupdate. No NULL/owner/initialization guard, statusresult or owncriticalsectionallocation.
void __cdecl _lock_file(FILE *Stream)
{
  if ( Stream < (FILE *)&off_664DE0 || Stream > &stru_665040 )
  {
    EnterCriticalSection((LPCRITICAL_SECTION)&Stream[1]);
  }
  else
  {
    _lock((((char *)Stream - (char *)&off_664DE0) >> 5) + 16);
    Stream->_flag |= 0x8000u;
  }
}

