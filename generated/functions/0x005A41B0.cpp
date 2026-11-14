// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A41B0 rf_renderer_scale_reciprocal_depth
// UNREALRED VERIFIED [face-batch-20261028]: Returns float-rounded(global float0x6649F4 * caller float),in x87. Render callers supply reciprocal camera z; no perspective divide or clamp in helper.
double __cdecl rf_renderer_scale_reciprocal_depth(float a1)
{
  return (float)(flt_6649F4 * a1);
}

