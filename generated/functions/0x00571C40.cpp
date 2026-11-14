// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571C40 rf_renderer_clear_color_backend_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): For backend102 calls rf_renderer_clear_color_clip_rectangle. Other backends do no clear and leave backend code in EAX. Does not clear depth.
int rf_renderer_clear_color_backend_dispatch()
{
  int result; // eax

  result = dword_187CC9C;
  if ( dword_187CC9C == 102 )
    return rf_renderer_clear_color_clip_rectangle();
  return result;
}

