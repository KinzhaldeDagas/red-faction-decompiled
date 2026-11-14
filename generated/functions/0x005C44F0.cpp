// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C44F0 rf_d3d8_texture_mode_supported
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): When multitexture global 1DAEDF4 is false, accepts only descriptor texture modes below 4 (low five bits). With multitexture available, mode5 returns raw option/capability byte 1DAEDF5, while all other modes return 1. No texture allocation or descriptor mutation.
char __cdecl rf_d3d8_texture_mode_supported(_DWORD *a1)
{
  if ( !rf_d3d8_multitexture_available )
    return !rf_render_state_texture_mode_at_least_four(a1);
  if ( rf_render_state_get_texture_mode(a1) == 5 )
    return unk_1DAEDF5;
  return 1;
}

