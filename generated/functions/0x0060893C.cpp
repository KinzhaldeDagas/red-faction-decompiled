// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060893C __ftell_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl stream,NULL ->invalid/-1. fileno; negativecnt repaired0;
// lseek(fd,0,1),ANY signednegative offset ->-1. Withoutflags0x108 returnoffset-cnt wrapped. Buffered delta=ptr-base; ifflags&3 and descriptorbyte+4 mask0x80,add one per LF in
// base..<ptr using unsignedaddresscomparisons. If noflags3 and lowbyteflag notnegative (no0x80),errno22/-1 WITHOUT invalidhandler. Physicaloffset0 returnsdelta. Nonread mode returns
// offset+delta. Readmode,cnt0 returnsphysicaloffset alone. Otherwise extent=cnt+ptr-base; binarydescriptor subtractextent andadddelta. Textdescriptor probes lseek(fd,0,2):
// ifend==savedoffset,count LF over ORIGINAL base..<base+extent and add1 whenFILEflags0x2000. Otherresult (including-1) attemptsrestore lseek(fd,savedoffset,0); signednegative restore
// ->-1. Restored nonEOF branch uses extent512 iff originalextent<=512unsigned,FILEflag8 set andflag0x400clear,elseFILEbufsiz; add1 on descriptorbyte+4 mask4. Return
// savedoffset-adjustedextent+delta with32-bit wrap. No own lock/fd-range/NULLdescriptor/base<=ptr validation; read-only tell may perform seek/restore and may leave changed
// physicalposition on restorefailure. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or
// no-handler paths retain their separately described policy.
int __cdecl _ftell_nolock(FILE *Stream)
{
  int v3; // eax
  int v4; // eax
  int flag; // edx
  char *ptr; // eax
  char *base; // ecx
  char *v8; // edx
  int cnt; // edx
  int v10; // esi
  char *v11; // eax
  char *v12; // ecx
  bool v13; // zf
  int bufsiz; // eax
  int v15; // ecx
  char *v16; // [esp+8h] [ebp-Ch]
  int Offset; // [esp+Ch] [ebp-8h]
  int FileHandle; // [esp+10h] [ebp-4h]
  int Streama; // [esp+1Ch] [ebp+8h]

  if ( !Stream )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  v3 = _fileno(Stream);
  FileHandle = v3;
  if ( Stream->_cnt < 0 )
    Stream->_cnt = 0;
  v4 = _lseek(v3, 0, 1);
  Offset = v4;
  if ( v4 < 0 )
    return -1;
  flag = Stream->_flag;
  if ( (flag & 0x108) == 0 )
    return v4 - Stream->_cnt;
  ptr = Stream->_ptr;
  base = Stream->_base;
  v16 = (char *)(Stream->_ptr - base);
  if ( (flag & 3) != 0 )
  {
    if ( *(char *)(unk_2021E40[FileHandle >> 5] + ((FileHandle & 0x1F) << 6) + 4) < 0 )
    {
      v8 = Stream->_base;
      if ( base < ptr )
      {
        do
        {
          if ( *v8 == 10 )
            ++v16;
          ++v8;
        }
        while ( v8 < ptr );
      }
    }
  }
  else if ( (flag & 0x80u) == 0 )
  {
    *_errno() = 22;
    return -1;
  }
  if ( !Offset )
    return (int)v16;
  if ( (Stream->_flag & 1) == 0 )
    return (int)&v16[Offset];
  cnt = Stream->_cnt;
  if ( cnt )
  {
    Streama = cnt + ptr - base;
    v10 = (FileHandle & 0x1F) << 6;
    if ( *(char *)(unk_2021E40[FileHandle >> 5] + v10 + 4) >= 0 )
    {
LABEL_39:
      Offset -= Streama;
      return (int)&v16[Offset];
    }
    if ( _lseek(FileHandle, 0, 2) == Offset )
    {
      v11 = Stream->_base;
      v12 = &v11[Streama];
      while ( v11 < v12 )
      {
        if ( *v11 == 10 )
          ++Streama;
        ++v11;
      }
      v13 = (Stream->_flag & 0x2000) == 0;
LABEL_37:
      if ( !v13 )
        ++Streama;
      goto LABEL_39;
    }
    if ( _lseek(FileHandle, Offset, 0) >= 0 )
    {
      bufsiz = 512;
      if ( (unsigned int)Streama > 0x200 || (v15 = Stream->_flag, (v15 & 8) == 0) || (v15 & 0x400) != 0 )
        bufsiz = Stream->_bufsiz;
      Streama = bufsiz;
      v13 = (*(_BYTE *)(unk_2021E40[FileHandle >> 5] + v10 + 4) & 4) == 0;
      goto LABEL_37;
    }
    return -1;
  }
  v16 = nullptr;
  return (int)&v16[Offset];
}

