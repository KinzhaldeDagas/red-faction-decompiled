// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAF00 rf_ui_palette_default_construct_groups2_of3
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 2 groups of3 colors at0,12;24 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
char *__thiscall rf_ui_palette_default_construct_groups2_of3(char *this)
{
  rf_ui_palette_default_construct_colors3((int)this);
  rf_ui_palette_default_construct_colors3((int)(this + 12));
  return this;
}

