// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAED0 rf_ui_palette_default_construct_groups3_of5
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 3 groups of5 colors at offsets0,20,40;60 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
char *__thiscall rf_ui_palette_default_construct_groups3_of5(char *this)
{
  rf_ui_palette_default_construct_colors5((int)this);
  rf_ui_palette_default_construct_colors5((int)(this + 20));
  rf_ui_palette_default_construct_colors5((int)(this + 40));
  return this;
}

