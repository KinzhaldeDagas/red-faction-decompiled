// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6500 rf_exception_report_write_system_info
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Appends current time in local DOS-date formatting, executable path, user name, processor count/type and physical memory rounded up to MiB via (dwTotalPhys+0xFFFFF)>>20. Gets username into a 200-byte buffer, substitutes "Unknown" for path/name query failure. Uses GlobalMemoryStatus with dwLength=32 and 32-bit physical-memory arithmetic. Returns the final formatted-write BOOL, not an aggregate status for earlier lines.
BOOL __cdecl rf_exception_report_write_system_info(HANDLE hFile)
{
  CHAR Buffer[200]; // [esp+0h] [ebp-290h] BYREF
  struct _FILETIME SystemTimeAsFileTime; // [esp+C8h] [ebp-1C8h] BYREF
  struct _MEMORYSTATUS v4; // [esp+D0h] [ebp-1C0h] BYREF
  CHAR Filename[264]; // [esp+F0h] [ebp-1A0h] BYREF
  CHAR v6[108]; // [esp+1F8h] [ebp-98h] BYREF
  DWORD pcbBuffer; // [esp+268h] [ebp-28h] BYREF
  struct _SYSTEM_INFO SystemInfo; // [esp+26Ch] [ebp-24h] BYREF

  GetSystemTimeAsFileTime(&SystemTimeAsFileTime);
  rf_exception_format_local_filetime(v6, SystemTimeAsFileTime);
  rf_exception_report_writef(hFile, "Error occurred at %s.\r\n", v6);
  if ( !GetModuleFileNameA(nullptr, Filename, 0x104u) )
    lstrcpyA(Filename, "Unknown");
  pcbBuffer = 200;
  if ( !GetUserNameA(Buffer, &pcbBuffer) )
    lstrcpyA(Buffer, "Unknown");
  rf_exception_report_writef(hFile, "%s, run by %s.\r\n", Filename, Buffer);
  GetSystemInfo(&SystemInfo);
  rf_exception_report_writef(
    hFile,
    "%d processor(s), type %d.\r\n",
    SystemInfo.dwNumberOfProcessors,
    SystemInfo.dwProcessorType);
  v4.dwLength = 32;
  GlobalMemoryStatus(&v4);
  return rf_exception_report_writef(hFile, "%d MBytes physical memory.\r\n", (v4.dwTotalPhys + 0xFFFFF) >> 20);
}

