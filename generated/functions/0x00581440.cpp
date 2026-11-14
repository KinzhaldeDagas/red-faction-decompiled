// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581440 rf_renderer_get_far_clip_distance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered no-argument leaf returns float global18CD36C through ST0. Does not apply projection scaling,check far-plane enable or rebuild planes;disabled state typically stores0 through5813D0.
double __cdecl rf_renderer_get_far_clip_distance()
{
  return flt_18CD36C;
}

