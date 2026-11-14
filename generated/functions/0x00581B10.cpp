// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581B10 rf_renderer_reciprocal_scaled_camera_depth
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl float input. Calls float-rounded depth scaling581AF0(input*18CD3C4),returns float-rounded reciprocal1/scaledValue in ST0. No zero/finite guard,clamp or sign handling;not near/far remap.
double __cdecl rf_renderer_reciprocal_scaled_camera_depth(float a1)
{
  return (float)(1.0 / rf_renderer_scale_camera_depth_bias(a1));
}

