// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058CF00 rf_font_set_default_by_name
// UNREALRED VERIFIED [hud-persona-presentation-20261027] Resolves requested loaded font by name through 0x58C420 and installs its 108-byte font-record pointer as default at 0x193BBA0. Gameplay late-HUD init 0x448110 calls this with rfpc-medium.vf after loading countdown font. 0x58CFC0 and 0x58C130 use that default when the explicit font argument is negative. Explicit host ownership of the normal gameplay default avoids misidentifying -1 persona/caption slots as smallfont.vf or bigfont.vf; arbitrary later renderer-global default overrides are outside this baseline contract.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Loads/resolves font through58C420. Negative result returns byte0; otherwise installs record pointer base+108*index at default-font193BBA0 and returns1. Does not select current-font193BB9C or free previous default.
char __cdecl rf_font_set_default_by_name(char *a1)
{
  int register_and_build_atlas; // [esp+0h] [ebp-4h]

  register_and_build_atlas = rf_font_load_register_and_build_atlas(a1);
  if ( register_and_build_atlas < 0 )
    return 0;
  unk_193BBA0 = (char *)&unk_193B688 + 108 * register_and_build_atlas;
  return 1;
}

