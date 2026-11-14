// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AAFA0 rf_ui_palette_default_construct_colors4
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall aggregate palette constructor: 4 default colors at0,4,8,12;16 bytes addressed. All subordinate color construction resolves to no-op0x571990,so NO component bytes are initialized and no allocation occurs. Returns this. Group offsets describe observed call structure,not assumed semantic color roles.
int __thiscall rf_ui_palette_default_construct_colors4(int this)
{
  rf_rgba8_default_construct_noop((void *)this);
  rf_rgba8_default_construct_noop((void *)(this + 4));
  rf_rgba8_default_construct_noop((void *)(this + 8));
  rf_rgba8_default_construct_noop((void *)(this + 12));
  return this;
}

