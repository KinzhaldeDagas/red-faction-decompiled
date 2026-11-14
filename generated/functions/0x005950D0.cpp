// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005950D0 rf_clipboard_copy_ansi_text
// UNREALRED VERIFIED [transfer-scene-20261028]: Arguments writable buffer,max characters. Writes buffer[0]=0, calls OpenClipboard(NULL) ignoring result, GetClipboardData(CF_TEXT=1),GlobalLock. With valid locked text, copies min(strlen(text),signed max) bytes and writes an extra NUL at buffer[count], then unlocks and closes clipboard. Caller needs max+1 capacity for nonnegative max. GetClipboardData or GlobalLock failure returns WITHOUT CloseClipboard. Returns incidental WinAPI handle/BOOL, not copied length. No null buffer, negative max or accessible source bounds validation.
HANDLE __cdecl rf_clipboard_copy_ansi_text(_BYTE *a1, signed int a2)
{
  HANDLE result; // eax
  HGLOBAL hMem; // [esp+10h] [ebp-10h]
  signed int v4; // [esp+14h] [ebp-Ch]
  signed int i; // [esp+1Ch] [ebp-4h]

  *a1 = 0;
  OpenClipboard(nullptr);
  result = GetClipboardData(1u);
  hMem = result;
  if ( result )
  {
    result = GlobalLock(result);
    if ( result )
    {
      v4 = strlen((const char *)result);
      if ( v4 > a2 )
        v4 = a2;
      for ( i = 0; i < v4; ++i )
        a1[i] = *((_BYTE *)result + i);
      a1[i] = 0;
      GlobalUnlock(hMem);
      return (HANDLE)CloseClipboard();
    }
  }
  return result;
}

