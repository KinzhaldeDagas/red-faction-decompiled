// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6120 rf_exception_report_writef
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Cdecl variadic helper (HANDLE, format, ...). Uses wvsprintfA into a roughly 2 KB stack buffer, obtains lstrlenA, and calls WriteFile synchronously with that byte count. Returns the BOOL from WriteFile; does not verify NumberOfBytesWritten equals requested length, append a terminator to the file, or retry a short write. Formatter has no explicit destination-capacity argument.
BOOL rf_exception_report_writef(HANDLE hFile, LPCSTR a2, ...)
{
  DWORD v2; // eax
  CHAR String[2004]; // [esp+0h] [ebp-7E0h] BYREF
  DWORD NumberOfBytesWritten; // [esp+7D8h] [ebp-8h] BYREF
  va_list arglist; // [esp+7DCh] [ebp-4h]
  va_list va; // [esp+7F0h] [ebp+10h] BYREF

  va_start(va, a2);
  va_copy(arglist, va);
  wvsprintfA(String, a2, va);
  arglist = nullptr;
  v2 = lstrlenA(String);
  return WriteFile(hFile, String, v2, &NumberOfBytesWritten, nullptr);
}

