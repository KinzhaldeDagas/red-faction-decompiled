// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608B47 __fseek_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(stream,offset,origin),NO own NULLguard. Requireflags&0x83
// elseerrno22/-1 withoutinvalidhandler. Clear EOFmask0x10 FIRST. origin==1:ADD ftell_nolock result to offset wrapped,forceorigin0,NO check for tell=-1. Callflush and IGNORE status.
// Update-mode0x80 clearsbits0/1; otherwise readbit1 plusownedbuf8 andno0x400 setsbufsiz512. Calllseek(fileno,offset,origin); exact -1 ->-1,ANY other32-bit value ->0. Direct callers
// originnot1 is passed unchanged, no0..2 validation. No rollback of EOF/header/flush failure; successfulseek can still return0 after failedflush.
int __cdecl _fseek_nolock(FILE *Stream, int Offset, int Origin)
{
  int flag; // eax
  int v5; // eax
  int v6; // eax

  flag = Stream->_flag;
  if ( (flag & 0x83) != 0 )
  {
    Stream->_flag = flag & 0xFFFFFFEF;
    if ( Origin == 1 )
    {
      Offset += _ftell_nolock(Stream);
      Origin = 0;
    }
    _flush(Stream);
    v5 = Stream->_flag;
    if ( (v5 & 0x80u) == 0 )
    {
      if ( (v5 & 1) != 0 && (v5 & 8) != 0 && (v5 & 0x400) == 0 )
        Stream->_bufsiz = 512;
    }
    else
    {
      Stream->_flag = v5 & 0xFFFFFFFC;
    }
    v6 = _fileno(Stream);
    return (_lseek(v6, Offset, Origin) != -1) - 1;
  }
  else
  {
    *_errno() = 22;
    return -1;
  }
}

