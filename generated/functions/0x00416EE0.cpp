// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416EE0 rf_render_state_pack
// VERIFIED [impact-glass-render]: Packs six immediate-mode render-state fields into one 32-bit RF renderer descriptor.
// UNREALRED VERIFIED [packed-render-state-layout-20260903]: Exact layout: texture mode bits 0..4, RGB-modulation selector 5..9, alpha-modulation selector 10..14, blend selector 15..19, depth/alpha-test selector 20..24, and fog selector 25..29. The packer shifts and ORs inputs without masking; bits 30..31 are unused for valid 0..31 inputs.
int *__thiscall rf_render_state_pack(int *this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  *this = (a7 << 25) | (a6 << 20) | (a5 << 15) | (a4 << 10) | a2 | (32 * a3);
  return this;
}

