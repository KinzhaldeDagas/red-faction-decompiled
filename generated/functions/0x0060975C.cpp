// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060975C __flush
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE,NO NULLguard/lock. Initiallystatus0. Only flags low2==2
// ANDflags0x108 andsigned(ptr-base)>0 callswrite(fileno,base,pending). Exactfull write clearswritebit2 ONLY whenupdateflag0x80; short/failedwrite setsFILEerror0x20 andstatus-1.
// Nonpositivepending andinactive modes performnoIO. ALWAYS finallycnt0,ptr=base even onwritefailure,discarding pending-byte headerstate without rollback; nofree/commit/retry.
// Returns0/-1.
int __cdecl _flush(FILE *Stream)
{
  int flag; // eax
  int v2; // ebx
  char *base; // eax
  char *v4; // edi
  int v5; // eax
  int v6; // eax
  char *v7; // eax
  char *v9; // [esp-Ch] [ebp-14h]
  char *v10; // [esp-8h] [ebp-10h]

  flag = Stream->_flag;
  v2 = 0;
  if ( (flag & 3) == 2 && (flag & 0x108) != 0 )
  {
    base = Stream->_base;
    v4 = (char *)(Stream->_ptr - base);
    if ( (int)v4 > 0 )
    {
      v10 = (char *)(Stream->_ptr - base);
      v9 = Stream->_base;
      v5 = _fileno(Stream);
      if ( (char *)_write(v5, v9, (unsigned int)v10) == v4 )
      {
        v6 = Stream->_flag;
        if ( (v6 & 0x80u) != 0 )
          Stream->_flag = v6 & 0xFFFFFFFD;
      }
      else
      {
        Stream->_flag |= 0x20u;
        v2 = -1;
      }
    }
  }
  v7 = Stream->_base;
  Stream->_cnt = 0;
  Stream->_ptr = v7;
  return v2;
}

