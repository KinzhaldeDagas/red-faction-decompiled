// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6260 rf_exception_report_write_module
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): SEH-protected module inspection. Gets module filename, requires DOS MZ and NT PE signatures using e_lfanew, then opens the file read-only with FILE_SHARE_READ/OPEN_EXISTING. Captures low-DWORD file size and optional last-write time formatted in local time, closes the file, and writes filename, loaded base, decimal file size, PE FileHeader.TimeDateStamp, and optional file-date text. Invalid module/signature paths emit no line. Open failure still permits a line with size 0 and no file-date suffix. Inferred HMODULE return is incidental and varies by path.
HMODULE __cdecl rf_exception_report_write_module(HANDLE a1, HMODULE hModule)
{
  HMODULE result; // eax
  int v3; // eax
  struct _FILETIME v4; // [esp-8h] [ebp-1C4h]
  struct _FILETIME LastWriteTime; // [esp+10h] [ebp-1ACh] BYREF
  HMODULE v6; // [esp+18h] [ebp-1A4h]
  DWORD FileSize; // [esp+1Ch] [ebp-1A0h]
  HANDLE hFile; // [esp+20h] [ebp-19Ch]
  CHAR String[108]; // [esp+24h] [ebp-198h] BYREF
  HMODULE v10; // [esp+90h] [ebp-12Ch]
  CHAR Filename[268]; // [esp+94h] [ebp-128h] BYREF
  CPPEH_RECORD ms_exc; // [esp+1A4h] [ebp-18h]

  ms_exc.registration.TryLevel = 0;
  result = (HMODULE)GetModuleFileNameA(hModule, Filename, 0x104u);
  if ( result )
  {
    v6 = hModule;
    result = hModule;
    if ( *(_WORD *)hModule == 23117 )
    {
      result = (HMODULE)((char *)v6 + *((_DWORD *)v6 + 15));
      v10 = result;
      if ( *(_DWORD *)result == 17744 )
      {
        hFile = CreateFileA(Filename, 0x80000000, 1u, nullptr, 3u, 0x80u, nullptr);
        memset(String, 0, 100);
        FileSize = 0;
        if ( hFile != (HANDLE)-1 )
        {
          FileSize = GetFileSize(hFile, nullptr);
          if ( GetFileTime(hFile, nullptr, nullptr, &LastWriteTime) )
          {
            wsprintfA(String, " - file date is ");
            v4 = LastWriteTime;
            v3 = lstrlenA(String);
            rf_exception_format_local_filetime(&String[v3], v4);
          }
          CloseHandle(hFile);
        }
        return (HMODULE)rf_exception_report_writef(
                          a1,
                          "%s, loaded at 0x%08x - %d bytes - %08x%s\r\n",
                          Filename,
                          hModule,
                          FileSize,
                          *((_DWORD *)v10 + 2),
                          String);
      }
      else
      {
        ms_exc.registration.TryLevel = -2;
      }
    }
    else
    {
      ms_exc.registration.TryLevel = -2;
    }
  }
  return result;
}

