// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593C80 rf_window_enum_find_title_substring
// UNREALRED VERIFIED [system-progress-20261028]: EnumWindows callback HWND,substring pointer. Gets title into128-byte local with max127,continues(TRUE) if empty or no case-sensitive strstr match. Match sets DWORD found0x1BC2128=1 and stops enumeration(FALSE). Does not compare executable/process identity or exact full title. Original generic EnumFunc name replaced only after verifying body.
BOOL __stdcall rf_window_enum_find_title_substring(HWND hWnd, char *a2)
{
  CHAR String[128]; // [esp+4h] [ebp-88h] BYREF
  char *SubStr; // [esp+88h] [ebp-4h]

  SubStr = a2;
  if ( !GetWindowTextA(hWnd, String, 127) || !rf_cstring_find_first_substring(String, SubStr) )
    return 1;
  unk_1BC2128 = 1;
  return 0;
}

