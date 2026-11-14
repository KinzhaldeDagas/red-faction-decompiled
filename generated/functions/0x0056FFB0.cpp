// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056FFB0 rf_console_lexer_copy_and_fold_ascii_uppercase
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Copies raw token18099F0 includingNUL to normalized1809928. If flag663F00 nonzero,adds32 only to ASCII A..Z;other bytes unchanged. Loop is do-while and advances before testing next byte,so empty token still touches first byte and may scan prior bytes after initialNUL until anotherNUL. Returns cursor at stopping location,not normalized buffer base. No Unicode/locale folding,capacity check or source mutation.
char *rf_console_lexer_copy_and_fold_ascii_uppercase()
{
  char v0; // cl
  char *result; // eax
  char v2; // [esp+0h] [ebp-1Ch]
  _BYTE *v3; // [esp+Ch] [ebp-10h]
  char *v4; // [esp+10h] [ebp-Ch]
  char *v5; // [esp+14h] [ebp-8h]
  char v6; // [esp+18h] [ebp-4h]

  v6 = 32;
  if ( !dword_663F00 )
    v6 = 0;
  v4 = unk_18099F0;
  v3 = &unk_1809928;
  do
  {
    v0 = *v4;
    *v3++ = *v4++;
  }
  while ( v0 );
  v5 = (char *)&unk_1809928;
  do
  {
    if ( *v5 < 65 || *v5 > 90 )
      v2 = *v5;
    else
      v2 = v6 + *v5;
    *v5++ = v2;
    result = v5;
  }
  while ( *v5 );
  return result;
}

