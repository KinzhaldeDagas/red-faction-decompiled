// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608558 __fclose_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl stream,initial result-1. NULL ->invalid/-1. NonNULL with
// flags&0x83: save flush result,freebuf regardlessflushstatus,fileno/close. Negative close return forces result-1 and leaves tmpname untouched; nonnegative close frees nonNULL
// tmpname then clears it, retaining savedflushresult. ALWAYS clear flags0 for nonNULL receiver,including inactiveflags and close failure. Does not free FILEallocation or lock;
// ignores freebuf result and does not roll back failedclose/flushed state. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if
// handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl _fclose_nolock(FILE *Stream)
{
  int v1; // ebx
  int v3; // eax

  v1 = -1;
  if ( Stream )
  {
    if ( (Stream->_flag & 0x83) != 0 )
    {
      v1 = _flush(Stream);
      _freebuf((int)Stream);
      v3 = _fileno(Stream);
      if ( _close(v3) >= 0 )
      {
        if ( Stream->_tmpfname )
        {
          free(Stream->_tmpfname);
          Stream->_tmpfname = nullptr;
        }
      }
      else
      {
        v1 = -1;
      }
    }
    Stream->_flag = 0;
    return v1;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

