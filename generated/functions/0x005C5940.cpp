// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5940 rf_render_state_texture_mode_at_least_four
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, stack layout, API calls and callers): Returns ((descriptor DWORD & 0x1F) >=4) through rf_render_state_get_texture_mode. Exact numeric category predicate; does not query or change the graphics device.
bool __thiscall rf_render_state_texture_mode_at_least_four(_DWORD *this)
{
  return rf_render_state_get_texture_mode(this) >= 4;
}

