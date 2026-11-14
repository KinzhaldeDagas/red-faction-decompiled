// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006163A6 __ftbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(tempFlag,FILE). Tempflag0 skips withEAXunchanged. Nonzero
// butFILEflag0x1000clear alsoskips withoutassignedresult. Admitted flush(FILE),thenALWAYSclearflags0x1100,bufsiz0,ptrNULL,baseNULL,evenflushfailure; cnt wasresetbyflush.
// EAXrawflushresult survivesANDmemoryoperations. Doesnotfreepersistent tempcache orFILE,restoreoldbuffer ornormalize skipreturns.
int __cdecl _ftbuf(int a1, FILE *Stream)
{
  int result; // eax

  if ( a1 )
  {
    if ( (Stream->_flag & 0x1000) != 0 )
    {
      result = _flush(Stream);
      Stream->_flag &= 0xFFFFEEFF;
      Stream->_bufsiz = 0;
      Stream->_ptr = nullptr;
      Stream->_base = nullptr;
    }
  }
  return result;
}

