// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A275 __findnext64i32
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Output layout: attrib DWORD+0 (padding+4 untouched), creation/access/write
// signed64+8/+16/+24, size DWORD+32, name char[260]+36. On success attrs EXACTLY128 becomes0, all other attribute DWORDs copied unchanged; time64_t_from_ft called for each timestamp
// and both halves stored, conversion failures NOT rejected; only nFileSizeLow copied, high discarded. strcpy_s(name,260,WIN32_FIND_DATA.cFileName) failure invokes Watson with five
// zero arguments. Output can be partially changed; no rollback or own FindClose, and security cookie checked on normal exit. Cdecl(handle,out), int0/-1. Reject handle EXACTLY-1 or
// NULLout via invalid(22)/-1; no other handle validation. FindNextFileA failure LastError2/3/18 ->errno2,8->12, all others including0->22; no dosmaperr/doserrno update. Success0;
// handle remains caller-owned.
int __cdecl _findnext64i32(intptr_t FindHandle, struct _finddata64i32_t *FindData)
{
  DWORD LastError; // eax
  __int64 v4; // rax
  struct _WIN32_FIND_DATAA FindFileData; // [esp+8h] [ebp-144h] BYREF

  if ( FindHandle == -1 || !FindData )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
  if ( !FindNextFileA((HANDLE)FindHandle, &FindFileData) )
  {
    LastError = GetLastError();
    if ( LastError >= 2 )
    {
      if ( LastError <= 3 )
        goto LABEL_12;
      if ( LastError == 8 )
      {
        *_errno() = 12;
        return -1;
      }
      if ( LastError == 18 )
      {
LABEL_12:
        *_errno() = 2;
        return -1;
      }
    }
    *_errno() = 22;
    return -1;
  }
  FindData->attrib = FindFileData.dwFileAttributes != 128 ? FindFileData.dwFileAttributes : 0;
  FindData->time_create = __time64_t_from_ft(&FindFileData.ftCreationTime);
  FindData->time_access = __time64_t_from_ft(&FindFileData.ftLastAccessTime);
  v4 = __time64_t_from_ft(&FindFileData.ftLastWriteTime);
  LODWORD(FindData->time_write) = v4;
  FindData->size = FindFileData.nFileSizeLow;
  HIDWORD(FindData->time_write) = HIDWORD(v4);
  if ( strcpy_s(FindData->name, 0x104u, FindFileData.cFileName) )
    _invoke_watson(nullptr, nullptr, nullptr, 0, 0);
  return 0;
}

