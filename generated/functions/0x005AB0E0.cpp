// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB0E0 rf_ui_palette_default_construct_groups3_3_2
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: groups of3,3,2 colors at0,12,24;32 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
void *__thiscall rf_ui_palette_default_construct_groups3_3_2(void *this)
{
  rf_ui_palette_default_construct_colors3((int)this);
  rf_ui_palette_default_construct_colors3((int)this + 12);
  rf_ui_palette_default_construct_colors2((int)this + 24);
  return this;
}

