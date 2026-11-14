// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CA5D _fputc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(character,FILE),NULL ->invalid/-1. LockFILE/armSEH;unlessflag0x40
// reject low7 encodingbits orfresh0x80 atdescriptor+36 (specialfd-1/-2 dummy),errno22/handler/-1. Admitted DEC FILEcnt BEFORE sign test; nonnegative wrapped result writes
// lowcharacterbyte atptr,incrementsptr,returnsunsignedbyte0..255; negative ->flsbuf(originalfullcharacter,FILE),returndelegate. INT_MIN decrement wraps positive andbypassesrefill.
// Finallyunlock normal/unwind; no inputcharEOFspecialcase, receiver rollback orcapacity validation. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0),
// with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl fputc(int Character, FILE *Stream)
{
  int v3; // eax
  _BYTE *v4; // ecx
  char *v5; // eax
  int v7; // eax
  int v8; // [esp+10h] [ebp-1Ch]

  v8 = 0;
  if ( Stream )
  {
    _lock_file(Stream);
    if ( (Stream->_flag & 0x40) == 0 )
    {
      v3 = _fileno(Stream);
      if ( v3 == -1 || v3 == -2 )
        v4 = &unk_665C30;
      else
        v4 = (_BYTE *)(unk_2021E40[v3 >> 5] + ((v3 & 0x1F) << 6));
      if ( (v4[36] & 0x7F) != 0
        || (v3 == -1 || v3 == -2
          ? (v5 = (char *)&unk_665C30)
          : (v5 = (char *)(unk_2021E40[v3 >> 5] + ((v3 & 0x1F) << 6))),
            v5[36] < 0) )
      {
        *_errno() = 22;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        v8 = -1;
      }
    }
    if ( !v8 )
    {
      if ( --Stream->_cnt < 0 )
      {
        v7 = _flsbuf(Character, Stream);
      }
      else
      {
        *Stream->_ptr = Character;
        v7 = (unsigned __int8)Character;
        ++Stream->_ptr;
      }
      v8 = v7;
    }
    _unlock_file(Stream);
    return v8;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

