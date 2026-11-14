// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564FC0 rf_vfx_get_remaining_time
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): Corrected stale void declaration to double cdecl(handle,action). Calls562BE0 and leaves its floating result LIVE in ST0 through epilogue. Scene remaining is15fps timeline delta or tiny positive particle-live sentinel; tag2 delegates character remaining time. No reset or wait.
double __cdecl rf_vfx_get_remaining_time(const void *a1, int a2)
{
  return rf_model_handle_animation_remaining_time(a1, a2);
}

