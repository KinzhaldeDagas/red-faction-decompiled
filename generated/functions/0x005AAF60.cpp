// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAF60 rf_ui_palette_default_construct_groups4_of4
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 4 groups of4 colors at0,16,32,48;64 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
char *__thiscall rf_ui_palette_default_construct_groups4_of4(char *this)
{
  rf_ui_palette_default_construct_colors4((int)this);
  rf_ui_palette_default_construct_colors4((int)(this + 16));
  rf_ui_palette_default_construct_colors4((int)(this + 32));
  rf_ui_palette_default_construct_colors4((int)(this + 48));
  return this;
}

