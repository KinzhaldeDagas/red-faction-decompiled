// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C3C0 rf_font_load_with_spacing_override
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Calls load/register/build-atlas58C420. On negative result returns-1. If default-font pointer193BBA0 is NULL, selects the returned record as default. For spacingOverride>=0 stores it at record+56. Returns font index. Drawing/measurement newline height still comes from+52; +56 is the separate spacing property.
int __cdecl rf_font_load_with_spacing_override(char *a1, int a2)
{
  int register_and_build_atlas; // [esp+0h] [ebp-4h]

  register_and_build_atlas = rf_font_load_register_and_build_atlas(a1);
  if ( register_and_build_atlas < 0 )
    return -1;
  if ( !unk_193BBA0 )
    unk_193BBA0 = (char *)&unk_193B688 + 108 * register_and_build_atlas;
  if ( a2 > -1 )
    unk_193B6C0[27 * register_and_build_atlas] = a2;
  return register_and_build_atlas;
}

