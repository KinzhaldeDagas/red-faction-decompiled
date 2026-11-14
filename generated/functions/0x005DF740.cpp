// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF740 rf_render_state_get_fog_selector
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts the fog selector as descriptor bits 25..29.
int __thiscall rf_render_state_get_fog_selector(_DWORD *this)
{
  return (*this >> 25) & 0x1F;
}

