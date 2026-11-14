// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF720 rf_render_state_get_depth_alpha_test_selector
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Extracts the combined depth/alpha-test selector as descriptor bits 20..24.
int __thiscall rf_render_state_get_depth_alpha_test_selector(_DWORD *this)
{
  return (*this >> 20) & 0x1F;
}

