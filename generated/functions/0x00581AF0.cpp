// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581AF0 rf_renderer_scale_camera_depth_bias
// UNREALRED VERIFIED [face-batch-20261028]: Returns float-rounded callerfloat*global0x18CD3C4. Face renderer uses inputs0.05 and0.5 for depth-bias magnitude/threshold; helper does not clamp or convert units otherwise.
double __cdecl rf_renderer_scale_camera_depth_bias(float a1)
{
  return (float)(a1 * unk_18CD3C4);
}

