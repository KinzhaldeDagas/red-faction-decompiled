// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CB69 _fgets
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Cdecl(buffer,signedmax,FILE). Reject(bufferNULL ANDmax!=0),negative max
// orNULLFILE ->invalid/NULL. Max0 returnsNULL beforelock/descriptor/read (NULLbuffer allowed only this0 path). Lock/armSEH;unlessflag0x40 enforce descriptorencoding low7/fresh0x80
// zero,elseinvalid/NULL. Admitted max1 writes onlyNUL andreturnsbuffer. Looppredecrements max,thenDEC FILEcnt wrapped/sign test:negativefilbuf,elseunsignedbyte*ptr++. EOF(-1) BEFORE
// anybyte ->NULL WITHOUT writingNUL;EOFafterpartial orbyteLF stops andNUL-terminates,returnsoriginalbuffer. LF is included. Readerror afterpartial also returnsbuffer,not
// distinguishedfromEOF here. Finallyunlock. No actualcapacity discovery or reset of destination on invalid/earlyEOF. Unqualified invalid denotes errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
char *__cdecl fgets(char *Buffer, int MaxCount, FILE *Stream)
{
  int v4; // eax
  _BYTE *v5; // ecx
  char *v6; // eax
  char *v7; // edi
  int v9; // eax
  char *v10; // [esp+1Ch] [ebp-1Ch]

  v10 = Buffer;
  if ( !Buffer && MaxCount || MaxCount < 0 || !Stream )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
  if ( !MaxCount )
    return nullptr;
  _lock_file(Stream);
  if ( (Stream->_flag & 0x40) == 0 )
  {
    v4 = _fileno(Stream);
    if ( v4 == -1 || v4 == -2 )
      v5 = &unk_665C30;
    else
      v5 = (_BYTE *)(unk_2021E40[v4 >> 5] + ((v4 & 0x1F) << 6));
    if ( (v5[36] & 0x7F) != 0
      || (v4 == -1 || v4 == -2 ? (v6 = (char *)&unk_665C30) : (v6 = (char *)(unk_2021E40[v4 >> 5] + ((v4 & 0x1F) << 6))),
          v6[36] < 0) )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      v10 = nullptr;
    }
  }
  if ( v10 )
  {
    v7 = Buffer;
    do
    {
      if ( !--MaxCount )
        break;
      if ( --Stream->_cnt < 0 )
        v9 = _filbuf(Stream);
      else
        v9 = *(unsigned __int8 *)Stream->_ptr++;
      if ( v9 == -1 )
      {
        if ( v7 == Buffer )
        {
          v10 = nullptr;
          goto $done$29783;
        }
        break;
      }
      *v7++ = v9;
    }
    while ( (_BYTE)v9 != 10 );
    *v7 = 0;
  }
$done$29783:
  _unlock_file(Stream);
  return v10;
}

