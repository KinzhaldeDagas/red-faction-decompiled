// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058D170 rf_font_center_current_line_x
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Uses current-font glyph advances to sum bytes until NUL or LF, then returns signed integer(viewportWidth187CCC4-totalAdvance)/2. Does not select/restore font, include viewport origin, or test input/current font NULL. Kerning helper gets lookahead byte even for last measured character.
int __cdecl rf_font_center_current_line_x(unsigned __int8 *a1)
{
  int v2; // [esp+0h] [ebp-Ch] BYREF
  int v3; // [esp+4h] [ebp-8h] BYREF
  int v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  while ( *a1 && *a1 != 10 )
  {
    rf_font_lookup_glyph_width_and_advance(*a1, a1[1], &v2, &v3);
    v4 += v3;
    ++a1;
  }
  return (unk_187CCC4 - v4) / 2;
}

