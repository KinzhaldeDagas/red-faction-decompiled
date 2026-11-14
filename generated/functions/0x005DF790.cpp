// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF790 rf_renderer_depth_from_vertex_reciprocal
// UNREALRED VERIFIED [renderer-helpers-20261028]: Loads float at vertex+20,forwards it to rf_renderer_scale_reciprocal_depth0x5A41B0,and leaves float result in x87 ST0. Current void prototype is misleading; line renderer0x5D3D90 immediately FSTP result into GPUvertex+8. Does not project vertex or change fields. Types preserved.
void __cdecl rf_renderer_depth_from_vertex_reciprocal(int a1)
{
  rf_renderer_scale_reciprocal_depth(*(float *)(a1 + 20));
}

