// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060BF6E __chdir
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(path),0/-1, NO own lock. NULLpath clearsdos then invalid22/-1.
// SetCurrentDirectoryA FIRST; all later failures leave OS cwd changed. Query current directory capacity261 stack; SIGNED result>260 calloc_crt(result+1,1), second query, no second
// growth validation. Allocation NULL or API0 maps GetLastError/-1; stale LastError can overwrite allocator error. Returned path starts EXACT double-backslash OR double-forwardslash
// ->skip environment update; mixed separators do NOT skip. Otherwise SetEnvironmentVariableA(name="="+lowBYTE(mbctoupper(unsigned firstbyte))+":",value=currentPath); false maps
// LastError/-1. Free owned path normally. No rollback, own CRT environ-array update or exception-finally free.
int __cdecl _chdir(const char *Path)
{
  char *v1; // esi
  signed int CurrentDirectoryA; // eax
  DWORD v4; // edi
  CHAR *v5; // eax
  CHAR v6; // al
  DWORD LastError; // eax
  int v8; // [esp+8h] [ebp-118h]
  int v9; // [esp+Ch] [ebp-114h]
  CHAR Name[2]; // [esp+10h] [ebp-110h] BYREF
  char v11[266]; // [esp+12h] [ebp-10Eh] BYREF

  v9 = -1;
  v1 = &v11[2];
  v8 = 0;
  if ( !Path )
  {
    *__doserrno() = 0;
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( !SetCurrentDirectoryA(Path) )
    goto LABEL_14;
  CurrentDirectoryA = GetCurrentDirectoryA(0x105u, &v11[2]);
  v4 = CurrentDirectoryA;
  if ( CurrentDirectoryA > 260 )
  {
    v5 = (CHAR *)_calloc_crt(CurrentDirectoryA + 1, 1);
    v1 = v5;
    if ( !v5 || (v8 = 1, !v4) )
    {
LABEL_14:
      LastError = GetLastError();
      _dosmaperr(LastError);
      goto LABEL_15;
    }
    v4 = GetCurrentDirectoryA(v4 + 1, v5);
  }
  if ( !v4 )
    goto LABEL_14;
  if ( (v6 = *v1, *v1 != 92) && v6 != 47 || v6 != v1[1] )
  {
    Name[0] = 61;
    Name[1] = _mbctoupper((unsigned __int8)*v1);
    strcpy(v11, ":");
    if ( !SetEnvironmentVariableA(Name, v1) )
      goto LABEL_14;
  }
  v9 = 0;
LABEL_15:
  if ( v8 )
    free(v1);
  return v9;
}

