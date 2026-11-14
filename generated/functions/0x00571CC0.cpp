// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571CC0 rf_renderer_set_depth_clear_enabled
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): When control byte is nonzero, stores flag182AB99=1 and, for renderer backend102, invokes rf_renderer_clear_depth_clip_rectangle. Zero clears the flag without clearing depth. Does not write camera outcode clipping-enable byte663F38. Used by camera projection setup; no return value.
void __cdecl rf_renderer_set_depth_clear_enabled(unsigned __int8 a1)
{
  if ( a1 )
  {
    unk_182AB99 = 1;
    if ( dword_187CC9C == 102 )
      rf_renderer_clear_depth_clip_rectangle();
  }
  else
  {
    unk_182AB99 = 0;
  }
}

