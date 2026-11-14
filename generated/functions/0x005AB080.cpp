// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB080 rf_ui_palette_default_construct_groups3_of2
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 3 groups of2 colors at0,8,16;24 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
char *__thiscall rf_ui_palette_default_construct_groups3_of2(char *this)
{
  rf_ui_palette_default_construct_colors2((int)this);
  rf_ui_palette_default_construct_colors2((int)(this + 8));
  rf_ui_palette_default_construct_colors2((int)(this + 16));
  return this;
}

