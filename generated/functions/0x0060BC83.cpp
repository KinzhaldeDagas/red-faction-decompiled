// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BC83 __getdcwd_nolock
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(drive,buffer,SIGNEDcount), pointer/NULL, NO own lock. Nonzero drive must
// pass validdrive else dos15/invalid13/NULL; zero drive calls getdrive, which may remain0 for UNC. NonNULL buffer requires count>0 else invalid22/NULL without dos reset; then
// buffer[0]=0. NULL buffer has no count validation and first API capacity0. Build lowBYTE(drive+64)+":"+"." for nonzero drive, otherwise "."; GetFullPathNameA. First API0 maps
// LastError/NULL. Caller buffer: SIGNED result<count returns same buffer, otherwise errno34,buffer[0]=0,NULL. NULL buffer: choose SIGNED max(first required size,caller
// count),calloc(count,1); failureerrno12/dos8/NULL. Second API nonzero AND SIGNED result<count returns allocation. Otherwise map LastError/NULL WITHOUT freeing allocation, including
// second growth. No retry, rollback or overflow protection.
LPSTR __cdecl _getdcwd_nolock(DWORD nBufferLength, LPSTR lpBuffer, signed int Count)
{
  int v4; // eax
  LPSTR v5; // edi
  signed int FullPathNameA; // eax
  CHAR *v7; // eax
  signed int v8; // eax
  DWORD LastError; // eax
  LPSTR FilePart; // [esp+4h] [ebp-8h] BYREF
  CHAR FileName; // [esp+8h] [ebp-4h] BYREF
  char v12[3]; // [esp+9h] [ebp-3h] BYREF
  signed int nBufferLengtha; // [esp+14h] [ebp+8h]

  if ( nBufferLength )
  {
    if ( !_validdrive(nBufferLength) )
    {
      *__doserrno() = 15;
      *_errno() = 13;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return nullptr;
    }
    v4 = nBufferLength;
  }
  else
  {
    v4 = _getdrive();
  }
  v5 = lpBuffer;
  if ( lpBuffer )
  {
    if ( Count <= 0 )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return nullptr;
    }
    nBufferLengtha = Count;
    *lpBuffer = 0;
  }
  else
  {
    nBufferLengtha = 0;
  }
  if ( v4 )
  {
    FileName = v4 + 64;
    strcpy(v12, ":.");
  }
  else
  {
    FileName = 46;
    v12[0] = 0;
  }
  FullPathNameA = GetFullPathNameA(&FileName, nBufferLengtha, lpBuffer, &FilePart);
  if ( !FullPathNameA )
    goto LABEL_25;
  if ( !lpBuffer )
  {
    if ( FullPathNameA > Count )
      Count = FullPathNameA;
    v7 = (CHAR *)calloc(Count, 1u);
    v5 = v7;
    if ( !v7 )
    {
      *_errno() = 12;
      *__doserrno() = 8;
      return nullptr;
    }
    v8 = GetFullPathNameA(&FileName, Count, v7, &FilePart);
    if ( v8 && v8 < Count )
      return v5;
LABEL_25:
    LastError = GetLastError();
    _dosmaperr(LastError);
    return nullptr;
  }
  if ( FullPathNameA < nBufferLengtha )
    return v5;
  *_errno() = 34;
  *lpBuffer = 0;
  return nullptr;
}

