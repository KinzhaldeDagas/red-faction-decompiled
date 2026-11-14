// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AB050 rf_ui_palette_default_construct_colors5
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 3-color group at0 plus colors at12,16;20 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
int __thiscall rf_ui_palette_default_construct_colors5(int this)
{
  rf_ui_palette_default_construct_colors3(this);
  rf_rgba8_default_construct_noop((void *)(this + 12));
  rf_rgba8_default_construct_noop((void *)(this + 16));
  return this;
}

