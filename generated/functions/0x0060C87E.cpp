// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C87E _vfscanf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal scanner dispatch uses FIVE cdecl slots(callback,FILE*,format,locale,vaList),not public vfscanf three-slot type. Require nonNULL FILE
// andformat;otherwise errno22,five-zero invalid_parameter,return-1 ifhandlerreturns. Lock FILE,armSEH finally. If FILE BYTE+12 &0x40 clear,getfileno; -1/-2 use staticdummy665C30,else
// derive record via arithmeticfd>>5 and(fd&31)*64. Reject nonzero low7 bits atrecord+36 or separately-read bit0x80; rejection sets errno22/calls invalidhandler/status-1. Admitted
// callback invoked as cdecl(FILE,format,locale,vaList),ADD16,store result. Normal and abnormal finally paths60C97D/60C980 call unlock_file;normal returns storedresult. Callback
// itself notNULL-checked; no FILE capacity/fd-range/locale/vaList validation, destination-size checks or input parsing directly. Corrected callback-first prototype fixes shifted
// FILE/format pseudocode; originalSEH prolog/epilog and scope record65EA30 preserved.
int __cdecl vfscanf(
        int (__cdecl *scanner)(void *, const char *, void *, char *),
        void *stream,
        const char *format,
        void *locale,
        char *arguments)
{
  int v6; // eax
  _BYTE *v7; // ecx
  char *v8; // eax
  int v9; // [esp+10h] [ebp-1Ch]

  v9 = 0;
  if ( stream && format )
  {
    _lock_file((FILE *)stream);
    if ( (*((_BYTE *)stream + 12) & 0x40) == 0 )
    {
      v6 = _fileno((FILE *)stream);
      if ( v6 == -1 || v6 == -2 )
        v7 = &unk_665C30;
      else
        v7 = (_BYTE *)(unk_2021E40[v6 >> 5] + ((v6 & 0x1F) << 6));
      if ( (v7[36] & 0x7F) != 0
        || (v6 == -1 || v6 == -2
          ? (v8 = (char *)&unk_665C30)
          : (v8 = (char *)(unk_2021E40[v6 >> 5] + ((v6 & 0x1F) << 6))),
            v8[36] < 0) )
      {
        *_errno() = 22;
        _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
        v9 = -1;
      }
    }
    if ( !v9 )
      v9 = scanner(stream, format, locale, arguments);
    _unlock_file((FILE *)stream);
    return v9;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

