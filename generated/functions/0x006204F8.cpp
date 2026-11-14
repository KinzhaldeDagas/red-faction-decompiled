// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006204F8 __ungetc_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): FILE32 offsets
// ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28; dynamic critical section+32. Descriptor record R=DWORD[2021E40+4*ARITHMETIC(fd>>5)]+64*(fd&31); handle DWORD+0, flags
// BYTE+4, lookahead BYTE+5, lock-init DWORD+8, critical section+12, encoding BYTE+36; fd limit DWORD2021E20. Invalid(E) means errno E plus invalid_parameter(NULL,NULL,NULL,0,0);
// stated status follows only if that handler returns. Cdecl(character,FILE), no ownNULLcheck/lock. UnlessFILEflag0x40, derivefd viafileno,fd-1/-2 use dummy665C30; require
// descriptor+36 low7bits0 and separatelyreadbit0x80clear,elseinvalid(22)/-1. Encodingcheck PRECEDES character==-1 test. Exactcharacter-1 returns-1; otherints truncateonlyatbytewrite.
// Admit ifreadflag1 OR(update80 ANDNOTwrite2),else-1 noownerrno. BaseNULLcallsgetbuf. Ifptr==base: cntnonzero ->-1, cnt0 firstINCREMENTptr. ThenDECREMENTptr. Stringflag40:
// requireexistingbyte==lowcharacter; mismatchINCREMENTptr undoingonlydecrement,return-1 (earlierempty-baseincrement remains). Nonstringsstorelowbyte. Success
// cnt++wrapped,clearEOF0x10,setread1,retainotherflagsincludingerror20,returnunsignedcharacter. No actualcapacity/boundscheck, OSseek or one-byte-only ownership record.
int __cdecl _ungetc_nolock(int Character, FILE *Stream)
{
  int v2; // eax
  _BYTE *v3; // ecx
  char *v4; // eax
  int flag; // eax
  char *v7; // eax
  int v8; // eax

  if ( (Stream->_flag & 0x40) == 0 )
  {
    v2 = _fileno(Stream);
    if ( v2 == -1 || v2 == -2 )
      v3 = &unk_665C30;
    else
      v3 = (_BYTE *)(unk_2021E40[v2 >> 5] + ((v2 & 0x1F) << 6));
    if ( (v3[36] & 0x7F) != 0
      || (v2 == -1 || v2 == -2 ? (v4 = (char *)&unk_665C30) : (v4 = (char *)(unk_2021E40[v2 >> 5] + ((v2 & 0x1F) << 6))),
          v4[36] < 0) )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return -1;
    }
  }
  if ( Character == -1 )
    return -1;
  flag = Stream->_flag;
  if ( (flag & 1) == 0 && ((flag & 0x80u) == 0 || (flag & 2) != 0) )
    return -1;
  if ( !Stream->_base )
    _getbuf(Stream);
  if ( Stream->_ptr == Stream->_base )
  {
    if ( Stream->_cnt )
      return -1;
    ++Stream->_ptr;
  }
  v7 = --Stream->_ptr;
  if ( (Stream->_flag & 0x40) != 0 )
  {
    if ( *v7 != (_BYTE)Character )
    {
      Stream->_ptr = v7 + 1;
      return -1;
    }
  }
  else
  {
    *v7 = Character;
  }
  v8 = Stream->_flag;
  ++Stream->_cnt;
  Stream->_flag = v8 & 0xFFFFFFEE | 1;
  return (unsigned __int8)Character;
}

