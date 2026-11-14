// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5920 rf_render_state_get_texture_mode
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts texture mode as descriptor bits 0..4.
int __thiscall rf_render_state_get_texture_mode(_DWORD *this)
{
  return *this & 0x1F;
}

