// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056E830 rf_console_prompt_append_character_or_commit_line
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl one char. LF copies current prompt180A4A0 unbounded into current261B ring record,stores default color at+257,advances/wraps500 index and clears prompt first byte. Other bytes append to prompt only if current strlen<255,then NUL. Does not increment dirty counter itself and does not split other line terminators. AL is incidental(character/length/index arithmetic),not success boolean.
char __cdecl rf_console_prompt_append_character_or_commit_line(char a1)
{
  char v1; // al
  char result; // al
  int v3; // kr00_4
  char *v4; // [esp+18h] [ebp-Ch]
  char *v5; // [esp+1Ch] [ebp-8h]

  if ( a1 == 10 )
  {
    v5 = (char *)&unk_180A4A0;
    v4 = &unk_180A5B0[261 * dword_1809920];
    do
    {
      v1 = *v5;
      *v4++ = *v5++;
    }
    while ( v1 );
    result = 5 * dword_1809920;
    *(int *)((char *)unk_180A6B1 + 261 * dword_1809920++) = unk_180A49C;
    if ( dword_1809920 >= 500 )
      dword_1809920 = 0;
    unk_180A4A0 = 0;
  }
  else
  {
    v3 = strlen((const char *)&unk_180A4A0);
    result = v3;
    if ( v3 < 255 )
    {
      *((_BYTE *)&unk_180A4A0 + v3) = a1;
      unk_180A4A1[v3] = 0;
      return a1;
    }
  }
  return result;
}

