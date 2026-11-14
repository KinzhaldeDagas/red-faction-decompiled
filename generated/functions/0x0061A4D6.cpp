// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A4D6 __fullpath
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(buffer,path,unsignedCount), pointer/NULL. NULL or empty path delegates
// getcwd(buffer,count) BEFORE own buffer validation. Nonempty path+callerbuffer requires unsignedcount>0 else invalid22/NULL; does not preclear caller buffer. NULLbuffer first
// queries GetFullPathNameA(path,0,NULL,NULL);0 maps LastError/NULL; allocate calloc(max_UNSIGNED(count,required),1), allocationfailureerrno12/NULL. Native compare selected
// DWORD<=UINT_MAX always passes (dead invalid22 arm). Then GetFullPathNameA(path,capacity,working,&filepart). UNSIGNED result>=capacity: free ONLY owned buffer,errno34/NULL. result0:
// free ONLY owned buffer THEN GetLastError/dosmaperr/NULL (cleanup may affect last-error state). Otherwise return working pointer, caller owns allocation if inputbufferNULL. No
// retries/secondgrowth recovery, lock or callerbuffer clearing on error.
char *__cdecl _fullpath(char *Buffer, const char *Path, size_t BufferCount)
{
  size_t FullPathNameA; // eax
  DWORD LastError; // eax
  size_t v6; // edi
  CHAR *v7; // eax
  DWORD v8; // eax
  LPSTR FilePart; // [esp+Ch] [ebp-8h] BYREF
  LPSTR lpBuffer; // [esp+10h] [ebp-4h]

  if ( !Path || !*Path )
    return _getcwd(Buffer, BufferCount);
  if ( Buffer )
  {
    v6 = BufferCount;
    if ( !BufferCount )
    {
      *_errno() = 22;
      _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
      return nullptr;
    }
    lpBuffer = Buffer;
  }
  else
  {
    FullPathNameA = GetFullPathNameA(Path, 0, nullptr, nullptr);
    if ( !FullPathNameA )
    {
LABEL_5:
      LastError = GetLastError();
      _dosmaperr(LastError);
      return nullptr;
    }
    v6 = BufferCount;
    if ( BufferCount <= FullPathNameA )
      v6 = FullPathNameA;
    v7 = (CHAR *)calloc(v6, 1u);
    lpBuffer = v7;
    if ( !v7 )
    {
      *_errno() = 12;
      return nullptr;
    }
  }
  v8 = GetFullPathNameA(Path, v6, lpBuffer, &FilePart);
  if ( v8 >= v6 )
  {
    if ( !Buffer )
      free(lpBuffer);
    *_errno() = 34;
    return nullptr;
  }
  if ( !v8 )
  {
    if ( !Buffer )
      free(lpBuffer);
    goto LABEL_5;
  }
  return lpBuffer;
}

