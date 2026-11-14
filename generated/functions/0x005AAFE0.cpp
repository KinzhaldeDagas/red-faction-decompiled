// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAFE0 rf_ui_palette_default_construct_groups2_of6
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 2 groups of6 colors at0,24;48 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
char *__thiscall rf_ui_palette_default_construct_groups2_of6(char *this)
{
  rf_ui_palette_default_construct_colors6((int)this);
  rf_ui_palette_default_construct_colors6((int)(this + 24));
  return this;
}

