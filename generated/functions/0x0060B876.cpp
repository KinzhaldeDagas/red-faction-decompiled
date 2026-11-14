// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B876 __stat64i32
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) means errno=E then
// invalid_parameter(NULL,NULL,NULL,0,0); any stated subsequent return requires that handler to return. Cdecl(filename,statout),0/-1. NULL filename/output clearsdoserrno then
// invalid22/-1. Wildcard scan literal "?*" ->errno2/dos2/-1. Reads filename[1] without length precheck; bare nonempty X: rejected errno2/dos2. Colon form
// drive=mbctolower(SIGN-EXTENDED first byte)-96 without alpha/range validation; otherwise getdrive(). FindFirstFileA success: mtime zero FILETIME ->0LL; nonzero converts local
// FILETIME/SYSTEMTIME then loctotime64_t(...,-1). Zero atime/ctime inherit mtime, otherwise same conversion. API conversion failure captures LastError/dosmaperr, FindClose, -1; prior
// output fields retained. loctotime64_t -1 NOT rejected. FindFirst failure root fallback only if original path contains any literal "./\": fullpath_helper(stack260,path,260,&owned),
// require resolved path nonNULL and (strlen==3 OR ESI-IsRootUNCName) and UNSIGNED GetDriveTypeA>1. Free owned retry allocation on fallback validation success/failure. Any fallback
// rejection forceserrno2/dos2, overwriting prior API/allocation error. Accepted root synthesizes DIRECTORY16, size0 and all timestamps loctotime64_t(1980,1,1,0,0,0,-1), result
// unchecked. Successful search closes handle before final header writes, Close BOOL ignored. Final: WORDmode+6=dtoxmode(attrs,ORIGINAL filename),WORDnlink+8=1;
// DWORDsize+20=nFileSizeLow only; WORDino+4/uid+10/gid+12=0; DWORDdev+0/rdev+16=drive-1. Times atime+24/mtime+32/ctime+40, padding+14..15 untouched. No full high-size support,
// rollback or exception-finally close.
int __cdecl _stat64i32(const char *FileName, struct _stat64i32 *Stat)
{
  char *dwHighDateTime; // esi
  int v3; // eax
  char *v4; // eax
  char *v5; // esi
  __time64_t v6; // rax
  DWORD LastError; // eax
  int v9; // [esp+Ch] [ebp-268h]
  struct _FILETIME LocalFileTime; // [esp+10h] [ebp-264h] BYREF
  struct _SYSTEMTIME SystemTime; // [esp+18h] [ebp-25Ch] BYREF
  HANDLE hFindFile; // [esp+28h] [ebp-24Ch] BYREF
  struct _WIN32_FIND_DATAA FindFileData; // [esp+2Ch] [ebp-248h] BYREF
  char Buffer[260]; // [esp+16Ch] [ebp-108h] BYREF

  dwHighDateTime = (char *)FileName;
  LocalFileTime.dwHighDateTime = (DWORD)FileName;
  if ( FileName && Stat )
  {
    if ( _mbspbrk((const unsigned __int8 *)FileName, &Control) )
    {
LABEL_5:
      *_errno() = 2;
      *__doserrno() = 2;
      return -1;
    }
    if ( FileName[1] == 58 )
    {
      if ( *FileName && !FileName[2] )
        goto LABEL_5;
      v3 = _mbctolower(*FileName) - 96;
    }
    else
    {
      v3 = _getdrive();
    }
    v9 = v3;
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
    {
      hFindFile = nullptr;
      if ( !_mbspbrk((const unsigned __int8 *)FileName, &off_648F68) )
        goto LABEL_5;
      v4 = _fullpath_helper(Buffer, (char *)FileName, 0x104u, (char **)&hFindFile);
      v5 = v4;
      if ( !v4 || strlen(v4) != 3 && !IsRootUNCName(v5) || GetDriveTypeA(v5) <= 1 )
      {
        if ( hFindFile )
          free(hFindFile);
        goto LABEL_5;
      }
      if ( hFindFile )
        free(hFindFile);
      FindFileData.dwFileAttributes = 16;
      FindFileData.nFileSizeHigh = 0;
      FindFileData.nFileSizeLow = 0;
      FindFileData.cFileName[0] = 0;
      v6 = __loctotime64_t(1980, 1, 1, 0, 0, 0, -1);
      dwHighDateTime = (char *)LocalFileTime.dwHighDateTime;
      Stat->st_mtime = v6;
      Stat->st_atime = v6;
      Stat->st_ctime = v6;
LABEL_41:
      Stat->st_mode = __dtoxmode(FindFileData.dwFileAttributes, (unsigned __int8 *)dwHighDateTime);
      Stat->st_nlink = 1;
      Stat->st_size = FindFileData.nFileSizeLow;
      Stat->st_ino = 0;
      Stat->st_gid = 0;
      Stat->st_uid = 0;
      Stat->st_dev = v9 - 1;
      Stat->st_rdev = v9 - 1;
      return 0;
    }
    if ( FindFileData.ftLastWriteTime.dwLowDateTime || FindFileData.ftLastWriteTime.dwHighDateTime )
    {
      if ( !FileTimeToLocalFileTime(&FindFileData.ftLastWriteTime, &LocalFileTime)
        || !FileTimeToSystemTime(&LocalFileTime, &SystemTime) )
      {
        goto LABEL_42;
      }
      Stat->st_mtime = __loctotime64_t(
                         SystemTime.wYear,
                         SystemTime.wMonth,
                         SystemTime.wDay,
                         SystemTime.wHour,
                         SystemTime.wMinute,
                         SystemTime.wSecond,
                         -1);
    }
    else
    {
      Stat->st_mtime = 0;
    }
    if ( FindFileData.ftLastAccessTime.dwLowDateTime || FindFileData.ftLastAccessTime.dwHighDateTime )
    {
      if ( !FileTimeToLocalFileTime(&FindFileData.ftLastAccessTime, &LocalFileTime)
        || !FileTimeToSystemTime(&LocalFileTime, &SystemTime) )
      {
        goto LABEL_42;
      }
      Stat->st_atime = __loctotime64_t(
                         SystemTime.wYear,
                         SystemTime.wMonth,
                         SystemTime.wDay,
                         SystemTime.wHour,
                         SystemTime.wMinute,
                         SystemTime.wSecond,
                         -1);
    }
    else
    {
      Stat->st_atime = Stat->st_mtime;
    }
    if ( !FindFileData.ftCreationTime.dwLowDateTime && !FindFileData.ftCreationTime.dwHighDateTime )
    {
      Stat->st_ctime = Stat->st_mtime;
LABEL_40:
      FindClose(hFindFile);
      goto LABEL_41;
    }
    if ( FileTimeToLocalFileTime(&FindFileData.ftCreationTime, &LocalFileTime)
      && FileTimeToSystemTime(&LocalFileTime, &SystemTime) )
    {
      Stat->st_ctime = __loctotime64_t(
                         SystemTime.wYear,
                         SystemTime.wMonth,
                         SystemTime.wDay,
                         SystemTime.wHour,
                         SystemTime.wMinute,
                         SystemTime.wSecond,
                         -1);
      goto LABEL_40;
    }
LABEL_42:
    LastError = GetLastError();
    _dosmaperr(LastError);
    FindClose(hFindFile);
    return -1;
  }
  *__doserrno() = 0;
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return -1;
}

