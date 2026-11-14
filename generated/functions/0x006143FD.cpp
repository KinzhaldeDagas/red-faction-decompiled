// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006143FD __filbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. CdeclFILE,NULL ->invalid/-1. Inactive!(flags&0x83) ORstringflag0x40
// returns-1 WITHOUTownerrno/errorbit;writebit2 ->errorbit20/-1. Setreadbit1;existingbufferflag0x10C resets ptrbase,elsegetbuf. read(fileno,base,bufsiz),storecnt. Exact0
// ->EOFbit10,cnt0,-1;exact-1 ->errorbit20,cnt0,-1. Anyother result retained ascount; if!(FILEflags&0x82),REPEATEDfileno calls derivefdrecord (fd-1/-2 dummy) anddescriptorbyte+4
// mask0x82==0x82 setsFILEbit0x2000. Ifbufsiz512 ANDowned8 AND!0x400,expanddeclaredbufsiz4096. DECcnt,returnunsignedbyte*ptr,ptr++. No ownlock,read-size-resultsanity, bufferallocation
// statuscheck orcaller count rollback. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or
// no-handler paths retain their separately described policy.
int __cdecl _filbuf(FILE *File)
{
  int flag; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  _DWORD *v5; // edi
  _BYTE *v6; // eax
  int v7; // eax
  char *ptr; // ecx
  int result; // eax
  char *base; // [esp-8h] [ebp-10h]
  unsigned int bufsiz; // [esp-4h] [ebp-Ch]

  if ( !File )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  flag = File->_flag;
  if ( (flag & 0x83) == 0 || (flag & 0x40) != 0 )
    return -1;
  if ( (flag & 2) != 0 )
  {
    File->_flag = flag | 0x20;
    return -1;
  }
  v2 = flag | 1;
  File->_flag = v2;
  if ( (v2 & 0x10C) != 0 )
    File->_ptr = File->_base;
  else
    _getbuf(File);
  bufsiz = File->_bufsiz;
  base = File->_base;
  v3 = _fileno(File);
  v4 = _read(v3, base, bufsiz);
  File->_cnt = v4;
  if ( !v4 || v4 == -1 )
  {
    File->_flag |= v4 != 0 ? 32 : 16;
    File->_cnt = 0;
    return -1;
  }
  if ( (File->_flag & 0x82) == 0 )
  {
    if ( _fileno(File) == -1 || _fileno(File) == -2 )
    {
      v6 = &unk_665C30;
    }
    else
    {
      v5 = (_DWORD *)(4 * (_fileno(File) >> 5) + 33693248);
      v6 = (_BYTE *)(*v5 + ((_fileno(File) & 0x1F) << 6));
    }
    if ( (v6[4] & 0x82) == 0x82 )
      File->_flag |= 0x2000u;
  }
  if ( File->_bufsiz == 512 )
  {
    v7 = File->_flag;
    if ( (v7 & 8) != 0 && (v7 & 0x400) == 0 )
      File->_bufsiz = 4096;
  }
  ptr = File->_ptr;
  --File->_cnt;
  result = (unsigned __int8)*ptr;
  File->_ptr = ptr + 1;
  return result;
}

