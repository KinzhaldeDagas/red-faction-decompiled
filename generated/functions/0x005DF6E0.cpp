// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF6E0 rf_render_state_get_alpha_modulation_selector
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts the alpha-modulation selector as descriptor bits 10..14.
int __thiscall rf_render_state_get_alpha_modulation_selector(_DWORD *this)
{
  return (*this >> 10) & 0x1F;
}

