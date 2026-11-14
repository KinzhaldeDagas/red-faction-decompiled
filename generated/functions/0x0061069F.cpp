// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061069F __flsbuf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(character,stream),no own NULLguard; fileno result replaces caller
// stream SLOT as fd whileESI preservesreceiver. If !(flags&0x82):errno9,errorbit0x20,-1; flags&0x40:errno34,errorbit,-1. Existing readbit1 clearscnt; without EOFbit0x10 sets
// error/-1, with EOF resets ptrbase and clears readbit. ClearEOF,setwrite2,cnt0. If no flags0x10C, allocate buffer unless receiver is table+32/+64 AND isatty(fd) nonzero. Buffered
// flags0x108: compute pending=ptr-base,ADVANCE ptr=base+1 andcnt=bufsiz-1 BEFORE I/O. Positive pending ->write(fd,base,pending),save result; nonpositivepending checks descriptor+4
// appendmask0x20 (fd-1/-2 use dummy665C30),lseeki64(fd,0,2),reject only64-bit -1. Unless seek failed, STORE new characterbyte atbase even if preceding write short/failed. Unbuffered
// path write(fd,&character,1),expected1. Require written==expected pending/1,else errorbit/-1; success unsignedcharacter0..255. Header/character writes are not rolled back on error;
// no lock or retry in body. False variadic table getter caused call-analysis failure; corrected zero-arg pointer ABI repairs it.
int __cdecl _flsbuf(int Ch, FILE *File)
{
  FILE *v2; // esi
  int flag; // eax
  unsigned int v5; // eax
  char *base; // eax
  char *ptr; // edi
  signed int v8; // edi
  _BYTE *v9; // eax
  __int64 v10; // rax
  int v11; // [esp+4h] [ebp-4h]

  v2 = File;
  File = (FILE *)_fileno(File);
  flag = v2->_flag;
  if ( (flag & 0x82) == 0 )
  {
    *_errno() = 9;
LABEL_3:
    v2->_flag |= 0x20u;
    return -1;
  }
  if ( (flag & 0x40) != 0 )
  {
    *_errno() = 34;
    goto LABEL_3;
  }
  if ( (flag & 1) != 0 )
  {
    v2->_cnt = 0;
    if ( (flag & 0x10) == 0 )
    {
      v2->_flag = flag | 0x20;
      return -1;
    }
    v2->_ptr = v2->_base;
    v2->_flag = flag & 0xFFFFFFFE;
  }
  v5 = v2->_flag & 0xFFFFFFED | 2;
  v2->_flag = v5;
  v2->_cnt = 0;
  v11 = 0;
  if ( (v5 & 0x10C) == 0
    && (v2 != (FILE *)((char *)crt_return_static_address_00664de0() + 32)
     && v2 != (FILE *)((char *)crt_return_static_address_00664de0() + 64)
     || !_isatty((int)File)) )
  {
    _getbuf(v2);
  }
  if ( (v2->_flag & 0x108) != 0 )
  {
    base = v2->_base;
    ptr = v2->_ptr;
    v2->_ptr = base + 1;
    v8 = ptr - base;
    v2->_cnt = v2->_bufsiz - 1;
    if ( v8 <= 0 )
    {
      if ( File == (FILE *)-1 || File == (FILE *)-2 )
        v9 = &unk_665C30;
      else
        v9 = (_BYTE *)(unk_2021E40[(int)File >> 5] + (((unsigned __int8)File & 0x1F) << 6));
      if ( (v9[4] & 0x20) != 0 )
      {
        v10 = _lseeki64((int)File, 0, 2);
        if ( (HIDWORD(v10) & (unsigned int)v10) == 0xFFFFFFFF )
          goto LABEL_27;
      }
    }
    else
    {
      v11 = _write((int)File, base, v8);
    }
    *v2->_base = Ch;
  }
  else
  {
    v8 = 1;
    v11 = _write((int)File, &Ch, 1u);
  }
  if ( v11 != v8 )
  {
LABEL_27:
    v2->_flag |= 0x20u;
    return -1;
  }
  return (unsigned __int8)Ch;
}

