// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593FE0 rf_window_detect_run_title_for_executable
// UNREALRED VERIFIED [system-progress-20261028]: Clears found flag0x1BC2128. Gets current module path(max127chars),finds FIRST case-sensitive .exe substring through0x41F140,truncates it,walks backward to last path delimiter and constructs [run] - basename - into256-byte local. Enumerates windows via0x593C80; matching title sets flag. No activation,process termination or window closing. Path scan has no beginning guard,GetModuleFileName truncation is unchecked. Return low byte is incidental,not the found flag.
char rf_window_detect_run_title_for_executable()
{
  char *ModuleHandleA; // eax
  const char *v3; // [esp+Ch] [ebp-198h]
  CHAR Filename[132]; // [esp+14h] [ebp-190h] BYREF
  HMODULE hModule; // [esp+98h] [ebp-10Ch]
  char lParam[256]; // [esp+9Ch] [ebp-108h] BYREF
  const char *v7; // [esp+1A0h] [ebp-4h]

  unk_1BC2128 = 0;
  ModuleHandleA = (char *)GetModuleHandleA(nullptr);
  hModule = (HMODULE)ModuleHandleA;
  if ( ModuleHandleA )
  {
    ModuleHandleA = (char *)GetModuleFileNameA(hModule, Filename, 0x7Fu);
    if ( (int)ModuleHandleA >= 1 )
    {
      ModuleHandleA = rf_cstring_find_first_substring(Filename, ".exe");
      v7 = ModuleHandleA;
      if ( ModuleHandleA )
      {
        *v7 = 0;
        while ( *v7 != 92 && *v7 != 47 && *v7 != 58 )
          --v7;
        v3 = ++v7;
        do
          LOBYTE(ModuleHandleA) = *v3;
        while ( *v3++ );
        if ( v3 != v7 + 1 )
        {
          sprintf(lParam, "[run] - %s -", v7);
          LOBYTE(ModuleHandleA) = EnumWindows((WNDENUMPROC)rf_window_enum_find_title_substring, (LPARAM)lParam);
        }
      }
    }
  }
  return (char)ModuleHandleA;
}

