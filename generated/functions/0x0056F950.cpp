// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056F950 rf_console_read_argument_validate_type_mask
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(requiredMask,preserveCase),returns flags&requiredMask or prints error and longjmps global context180A3C0 with1. preserveCase!=0 temporarily sets casefold flag663F00=0 before FED0 then unconditionally restores1,not prior value. Copies raw token18099F0->original1809310 and normalized1809928->current1809820;tail pointer1809810=lexer cursor. Type0(end) flags1;ordinary/string flags2;quoted type3 strips outer quotes with overlapping memcpy(length-2),NULs and becomes flags2. For string tokens every character whose DWORD class==4 (digits,+,-,.) makes float flag0x10 and atof result180A400;absence ofdot additionally int flag8/atoi180981C,so malformed signs/dots are accepted as numeric by this classifier.
// Otherwise lowercase literal0x prefix plus complete strtol(base0) sets hex0x20|int0x8. Recognizes on/true0x40,off/false0x80,+0x100,-0x200,comma0x400;integer nonzero adds40,zero adds80. Numeric globals NOT cleared for nonnumeric tokens. Quoted numeric strings also classified. Debug int diagnostic uses %f with only integer low word supplied,an ABI mismatch;not a float conversion. Mask mismatch missing-end vs wrong-keyword selects diagnostics,then nonlocal abort. No reentrancy/context validity or full numeric grammar validation.
int __cdecl rf_console_read_argument_validate_type_mask(int a1, int a2)
{
  char v2; // al
  int result; // eax
  double v4; // [esp+4h] [ebp-64h]
  char *v5; // [esp+38h] [ebp-30h]
  char *v6; // [esp+3Ch] [ebp-2Ch]
  char v7; // [esp+43h] [ebp-25h]
  char *v8; // [esp+48h] [ebp-20h]
  char *v9; // [esp+4Ch] [ebp-1Ch]
  int v10; // [esp+50h] [ebp-18h]
  char *EndPtr; // [esp+54h] [ebp-14h] BYREF
  int v12; // [esp+58h] [ebp-10h]
  int v13; // [esp+5Ch] [ebp-Ch]
  int i; // [esp+60h] [ebp-8h]
  int v15; // [esp+64h] [ebp-4h]

  if ( a2 )
    rf_console_lexer_set_ascii_casefold(0);
  rf_console_lexer_next_token();
  if ( a2 )
    rf_console_lexer_set_ascii_casefold(1);
  unk_1809810 = off_663EF8;
  v9 = unk_18099F0;
  v8 = unk_1809310;
  do
  {
    v7 = *v9;
    *v8++ = *v9++;
  }
  while ( v7 );
  v6 = (char *)&unk_1809928;
  v5 = &MEMORY[0x1809820];
  do
  {
    v2 = *v6;
    *v5++ = *v6++;
  }
  while ( v2 );
  if ( unk_180A488 )
  {
    sprintf(&unk_18CD828, "next arg is '%s', was originally '%s'\n", &MEMORY[0x1809820], unk_1809310);
    rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    rf_console_output_append_text_lines("Rest of the command line is ", nullptr);
    rf_console_output_append_text_lines((char *)unk_1809810, nullptr);
    rf_console_output_append_text_lines("\n", nullptr);
  }
  if ( unk_1809924 )
  {
    if ( unk_1809924 == 1 )
    {
      dword_1809308 = 2;
    }
    else if ( unk_1809924 == 3 )
    {
      dword_1809308 = 4;
    }
    else
    {
      dword_1809308 = 2;
    }
  }
  else
  {
    dword_1809308 = 1;
  }
  if ( (dword_1809308 & 4) != 0 )
  {
    v15 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 - byte_1809821;
    memcpy_0(&MEMORY[0x1809820], byte_1809821, v15 - 2);
    *(_BYTE *)(v15 + 25204766) = 0;
    dword_1809308 = 2;
  }
  if ( (dword_1809308 & 2) != 0 )
  {
    v13 = &MEMORY[0x1809820] + strlen(&MEMORY[0x1809820]) + 1 - byte_1809821;
    v12 = 0;
    for ( i = 0; i < v13; ++i )
    {
      if ( unk_1809410[(unsigned __int8)*(&MEMORY[0x1809820] + i)] == 4 )
        ++v12;
    }
    if ( v12 == v13 )
    {
      dword_1809308 |= 0x10u;
      flt_180A400 = atof(&MEMORY[0x1809820]);
      if ( !rf_cstring_find_first_character(&MEMORY[0x1809820], 46) )
      {
        dword_1809308 |= 8u;
        dword_180981C = atoi(&MEMORY[0x1809820]);
      }
    }
    else if ( MEMORY[0x1809820] == 48 && byte_1809821[0] == 120 )
    {
      v10 = strtol(&MEMORY[0x1809820], &EndPtr, 0);
      if ( !*EndPtr )
      {
        dword_1809308 |= 0x28u;
        dword_180981C = v10;
      }
    }
    if ( unk_180A488 )
    {
      if ( (dword_1809308 & 0x10) != 0 )
      {
        sprintf(&unk_18CD828, "Found float number! %f\n", flt_180A400);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
      if ( (dword_1809308 & 8) != 0 )
      {
        LODWORD(v4) = dword_180981C;
        sprintf(&unk_18CD828, "Found int number! %f\n", v4);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
      if ( (dword_1809308 & 0x20) != 0 )
      {
        sprintf(&unk_18CD828, "Found hex number! %x\n", dword_180981C);
        rf_console_output_append_text_lines(&unk_18CD828, nullptr);
      }
    }
    if ( !_stricmp(&MEMORY[0x1809820], "on") )
      dword_1809308 |= 0x40u;
    if ( !_stricmp(&MEMORY[0x1809820], "true") )
      dword_1809308 |= 0x40u;
    if ( !_stricmp(&MEMORY[0x1809820], off_640BC8) )
      dword_1809308 |= 0x80u;
    if ( !_stricmp(&MEMORY[0x1809820], "false") )
      dword_1809308 |= 0x80u;
    if ( !_stricmp(&MEMORY[0x1809820], "+") )
      dword_1809308 |= 0x100u;
    if ( !_stricmp(&MEMORY[0x1809820], "-") )
      dword_1809308 |= 0x200u;
    if ( !_stricmp(&MEMORY[0x1809820], ",") )
      dword_1809308 |= 0x400u;
  }
  if ( (dword_1809308 & 8) != 0 )
  {
    if ( dword_180981C )
      dword_1809308 |= 0x40u;
    else
      dword_1809308 |= 0x80u;
  }
  result = a1 & dword_1809308;
  if ( (a1 & dword_1809308) == 0 )
  {
    if ( (dword_1809308 & 1) == 0 || (a1 & 1) != 0 )
    {
      sprintf(&unk_18CD828, unk_88E2B0, &MEMORY[0x1809820]);
      rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    }
    else
    {
      rf_console_output_append_text_lines(unk_88E2AC, nullptr);
    }
    longjmp(Buf, 1);
  }
  return result;
}

