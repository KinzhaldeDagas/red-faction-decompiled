// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056EA40 rf_console_complete_unique_longer_command_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Scans sorted registry for case-insensitive prefix equal to entire current input and command name STRICTLY longer. More than one match returns immediately without modifying input;no cycling or longest-common-prefix completion. Exactly one copies full borrowed name unbounded to input180A2C0,adjusts cursor by length difference,appends space+NUL via WORD32 and increments cursor. Equal-length exact name is not eligible. Empty prefix completes only if exactly one registered name. No256B capacity guard or NULL-entry check;AL incidental.
char rf_console_complete_unique_longer_command_prefix()
{
  int v0; // eax
  char v1; // dl
  _BYTE *v3; // [esp+14h] [ebp-58h]
  char *v4; // [esp+18h] [ebp-54h]
  _BYTE *v6; // [esp+58h] [ebp-14h]
  int i; // [esp+5Ch] [ebp-10h]
  unsigned int MaxCount; // [esp+60h] [ebp-Ch]
  int v9; // [esp+68h] [ebp-4h]

  v6 = &unk_180A2C0;
  do
    LOBYTE(v0) = *v6;
  while ( *v6++ );
  MaxCount = v6 - (_BYTE *)&unk_180A2C1;
  v9 = -1;
  for ( i = 0; i < dword_180A480; ++i )
  {
    if ( MaxCount < strlen(*(const char **)dword_180A408[i]) )
    {
      v0 = _strnicmp((const char *)&unk_180A2C0, *(const char **)dword_180A408[i], MaxCount);
      if ( !v0 )
      {
        if ( v9 != -1 )
          return v0;
        v9 = i;
      }
    }
    LOBYTE(v0) = i + 1;
  }
  if ( v9 != -1 )
  {
    dword_180A48C += strlen(*(const char **)dword_180A408[v9]) - strlen((const char *)&unk_180A2C0);
    v4 = *(char **)dword_180A408[v9];
    v3 = &unk_180A2C0;
    do
    {
      v1 = *v4;
      *v3++ = *v4++;
    }
    while ( v1 );
    *(_WORD *)((char *)&unk_180A2C0 + strlen((const char *)&unk_180A2C0)) = 32;
    LOBYTE(v0) = ++dword_180A48C;
  }
  return v0;
}

