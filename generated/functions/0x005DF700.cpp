// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF700 rf_render_state_get_blend_selector
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts the D3D8 alpha-blend selector as descriptor bits 15..19.
int __thiscall rf_render_state_get_blend_selector(_DWORD *this)
{
  return (*this >> 15) & 0x1F;
}

