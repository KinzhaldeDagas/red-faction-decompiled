// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF760 rf_render_state_set_texture_mode
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Replaces descriptor bits 0..4 by clearing the low five bits and ORing the supplied value. The value is not masked; verified callers supply valid texture modes, including the mode-4 compatibility rewrite to mode 5.
_DWORD *__thiscall rf_render_state_set_texture_mode(_DWORD *this, int a2)
{
  *this &= 0xFFFFFFE0;
  *this |= a2;
  return this;
}

