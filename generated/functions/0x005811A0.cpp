// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005811A0 rf_renderer_apply_room_clip_aperture_backend_wrapper
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Backend102 forwards byte selector and four floats unchanged to room aperture helper;otherwise no action,nominal EAX backend value. Does not rebuild aperture on unsupported backend or validate selector/coordinates;return not defined as boolean success.
int __cdecl rf_renderer_apply_room_clip_aperture_backend_wrapper(char a1, float a2, float a3, float a4, float a5)
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_apply_room_clip_aperture(a1, a2, a3, a4, a5);
  return result;
}

