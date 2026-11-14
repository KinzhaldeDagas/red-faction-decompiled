// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5A10 rf_exception_write_errorlog_report
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Called from the WinMain exception path with EXCEPTION_POINTERS and a handler-context string. Sets byte 1DAEE4C as a one-shot/reentrancy latch and never clears it, including on file-open failure. Derives executable basename without extension for the report title, replaces its filename component with errorlog.txt, opens with OPEN_ALWAYS/no sharing/write-through, seeks to end, and appends the report. Records exception description, module containing EIP, CS:EIP, handler context, system info, access-violation read/write address when present, x86 registers/segments, 16 instruction bytes, stack DWORDs and module list. Each instruction-byte read has an SEH fallback writing "?? ". Stack read loop is SEH guarded and stops at min(TEB.StackBase, savedESP+8192), formatting eight DWORDs per line
// and flushing its 1000-byte buffer past a 950-byte threshold. Closes file and returns 0, also on duplicate/error paths; it is an exception filter result, not a success indicator. Apparent String1[4] is a split 260-byte stack buffer (first two DWORDs initialize "Unknown"); Filename is a separate path buffer. Filename copies/formatting are unbounded, and latch is not synchronized.
int __cdecl rf_exception_write_errorlog_report(int **a1, const char *a2)
{
  const char *v3; // eax
  int v4; // eax
  int v5; // eax
  const char *v6; // [esp-Ch] [ebp-B88h]
  int v7; // [esp-8h] [ebp-B84h]
  int v8; // [esp-4h] [ebp-B80h]
  const char *v9; // [esp+10h] [ebp-B6Ch]
  char v10[1004]; // [esp+14h] [ebp-B68h] BYREF
  int v11; // [esp+400h] [ebp-77Ch]
  _DWORD *v12; // [esp+404h] [ebp-778h]
  char *v13; // [esp+408h] [ebp-774h]
  _DWORD *StackBase; // [esp+40Ch] [ebp-770h]
  int v15; // [esp+410h] [ebp-76Ch]
  LPSTR v16; // [esp+414h] [ebp-768h]
  int i; // [esp+418h] [ebp-764h]
  CHAR v18[1004]; // [esp+41Ch] [ebp-760h] BYREF
  const char *v19; // [esp+808h] [ebp-374h]
  struct _MEMORY_BASIC_INFORMATION Buffer; // [esp+80Ch] [ebp-370h] BYREF
  char *last_char_wrapper; // [esp+828h] [ebp-354h]
  CHAR Filename[264]; // [esp+82Ch] [ebp-350h] BYREF
  int *v23; // [esp+934h] [ebp-248h]
  char *v24; // [esp+938h] [ebp-244h]
  CHAR String1[4]; // [esp+93Ch] [ebp-240h] BYREF
  void *v26; // [esp+940h] [ebp-23Ch]
  _BYTE v27[252]; // [esp+944h] [ebp-238h] BYREF
  LPCSTR lpString2; // [esp+A44h] [ebp-138h]
  int v29; // [esp+A48h] [ebp-134h]
  int *v30; // [esp+A4Ch] [ebp-130h]
  HANDLE hFile; // [esp+A50h] [ebp-12Ch]
  CHAR Str[268]; // [esp+A54h] [ebp-128h] BYREF
  CPPEH_RECORD ms_exc; // [esp+B64h] [ebp-18h]

  if ( unk_1DAEE4C )
    return 0;
  unk_1DAEE4C = 1;
  *(_DWORD *)String1 = 1852534357;
  v26 = &unk_6E776F;
  memset(v27, 0, sizeof(v27));
  if ( !GetModuleFileNameA(nullptr, Filename, 0x104u) )
    Filename[0] = 0;
  lpString2 = rf_path_basename_backslash(Filename);
  lstrcpyA(String1, lpString2);
  last_char_wrapper = rf_cstring_find_last_char_wrapper(String1, 46);
  if ( last_char_wrapper )
    *last_char_wrapper = 0;
  lstrcpyA((LPSTR)lpString2, "errorlog.txt");
  hFile = CreateFileA(Filename, 0x40000000u, 0, nullptr, 4u, 0x80000080, nullptr);
  if ( hFile == (HANDLE)-1 )
  {
    OutputDebugStringA("Error creating exception report");
    return 0;
  }
  else
  {
    SetFilePointer(hFile, 0, nullptr, 2u);
    rf_exception_report_writef(hFile, "\r\n\r\n\r\n\r\n");
    v30 = *a1;
    v23 = a1[1];
    v24 = "Unknown";
    if ( VirtualQuery((LPCVOID)v23[46], &Buffer, 0x1Cu)
      && GetModuleFileNameA((HMODULE)Buffer.AllocationBase, Str, 0x104u) )
    {
      v24 = rf_path_basename_backslash(Str);
    }
    v8 = v23[46];
    v7 = v23[47];
    v6 = v24;
    v3 = rf_exception_code_description(*v30);
    rf_exception_report_writef(hFile, "%s caused %s in module %s at %04x:%08x.\r\n", String1, v3, v6, v7, v8);
    rf_exception_report_writef(hFile, "Exception handler called in %s.\r\n", a2);
    rf_exception_report_write_system_info(hFile);
    if ( *v30 == -1073741819 && (unsigned int)v30[4] >= 2 )
    {
      v19 = "Read from";
      if ( v30[5] )
        v19 = "Write to";
      wsprintfA(v18, "%s location %08x caused an access violation.\r\n", v19, v30[6]);
      rf_exception_report_writef(hFile, "%s", v18);
    }
    rf_exception_report_writef(hFile, "\r\n");
    rf_exception_report_writef(hFile, "Registers:\r\n");
    rf_exception_report_writef(hFile, "EAX=%08x CS=%04x EIP=%08x EFLGS=%08x\r\n", v23[44], v23[47], v23[46], v23[48]);
    rf_exception_report_writef(hFile, "EBX=%08x SS=%04x ESP=%08x EBP=%08x\r\n", v23[41], v23[50], v23[49], v23[45]);
    rf_exception_report_writef(hFile, "ECX=%08x DS=%04x ESI=%08x FS=%04x\r\n", v23[43], v23[38], v23[40], v23[36]);
    rf_exception_report_writef(hFile, "EDX=%08x ES=%04x EDI=%08x GS=%04x\r\n", v23[42], v23[37], v23[39], v23[35]);
    rf_exception_report_writef(hFile, "Bytes at CS:EIP:\r\n");
    v29 = v23[46];
    for ( i = 0; i < 16; ++i )
    {
      ms_exc.registration.TryLevel = 0;
      rf_exception_report_writef(hFile, "%02x ", *(unsigned __int8 *)(i + v29));
      ms_exc.registration.TryLevel = -2;
    }
    rf_exception_report_writef(hFile, "\r\nStack dump:\r\n");
    ms_exc.registration.TryLevel = 1;
    v12 = (_DWORD *)v23[49];
    StackBase = NtCurrentTeb()->NtTib.StackBase;
    if ( StackBase > v12 + 2048 )
      StackBase = v12 + 2048;
    v15 = 0;
    memset(v10, 0, 1000);
    v11 = 50;
    v13 = &v10[950];
    v16 = v10;
    while ( v12 + 1 <= StackBase )
    {
      if ( !(v15 % 8) )
      {
        v4 = wsprintfA(v16, "%08x: ", v12);
        v16 += v4;
      }
      v9 = " ";
      if ( !(++v15 % 8) || v12 + 2 > StackBase )
        v9 = "\r\n";
      v5 = wsprintfA(v16, "%08x%s", *v12, v9);
      v16 += v5;
      ++v12;
      if ( v16 > v13 )
      {
        rf_exception_report_writef(hFile, "%s", v10);
        v10[0] = 0;
        v16 = v10;
      }
    }
    rf_exception_report_writef(hFile, "%s", v10);
    ms_exc.registration.TryLevel = -2;
    rf_exception_report_list_modules(hFile);
    CloseHandle(hFile);
    return 0;
  }
}

