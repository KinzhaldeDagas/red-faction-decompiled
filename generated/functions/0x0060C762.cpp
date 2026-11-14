// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C762 _fprintf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Variadic fprintf(FILE,format,...). Requirebothnonnull elseinvalid/-1.
// LockFILE BEFORE encodingvalidation;armSEH. Unlessflags0x40,fd-1/-2 dummy665C30 elseindexedrecord; reject low7 encodingbits+36 orseparately-read0x80
// ->errno22/invalidhandler,status-1 whilelockheld. Admitted stbuf,output_l(FILE,format,NULLlocale,&callerVarargs),save result,ftbuf(temp,FILE) ignoringresult. Finallyunlock
// normal/unwind; return savedformatterstatus. Temp-buffer cleanup normal-only,not SEHfinally; no own formatparser or sourcecount bound. Unqualified invalid denotes errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int fprintf(FILE *const Stream, const char *const Format, ...)
{
  int v3; // eax
  _BYTE *v4; // ecx
  char *v5; // eax
  int v6; // edi
  int v7; // [esp+10h] [ebp-1Ch]
  va_list va; // [esp+3Ch] [ebp+10h] BYREF

  va_start(va, Format);
  v7 = 0;
  if ( Stream && Format )
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
        v7 = -1;
      }
    }
    if ( !v7 )
    {
      v6 = _stbuf(Stream);
      v7 = _output_l(Stream, Format, nullptr, va);
      _ftbuf(v6, Stream);
    }
    _unlock_file(Stream);
    return v7;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

