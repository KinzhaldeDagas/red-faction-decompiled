// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006097C4 __fflush_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE. NULL ->flsall(mode0). NonNULL flush;nonzero ->-1,skipcommit.
// Flush0 andnoFILEflag0x4000 ->0;flagset ->commit(fileno),mapANY nonzero commitresult to-1 else0 viaNEG/SBB. No own lock, errorhandler, pointervalidation or retry; OSdurability
// policy delegated.
int __cdecl _fflush_nolock(FILE *Stream)
{
  int v2; // eax

  if ( !Stream )
    return flsall(0);
  if ( _flush(Stream) )
    return -1;
  if ( (Stream->_flag & 0x4000) == 0 )
    return 0;
  v2 = _fileno(Stream);
  return -(_commit(v2) != 0);
}

