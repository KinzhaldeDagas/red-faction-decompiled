// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF6C0 rf_render_state_get_rgb_modulation_selector
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts the RGB-modulation selector as descriptor bits 5..9.
int __thiscall rf_render_state_get_rgb_modulation_selector(_DWORD *this)
{
  return (*this >> 5) & 0x1F;
}

