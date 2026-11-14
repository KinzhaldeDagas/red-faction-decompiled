// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581B40 rf_renderer_vertex_scaled_camera_depth
// UNREALRED VERIFIED [renderer-mesh-20261028]: Returns float-rounded vertex.cameraZ+8 times global0x18CD294 in x87. No projection or clamp. Taperedsegment uses mean endpointresults as its own return value.
double __cdecl rf_renderer_vertex_scaled_camera_depth(int a1)
{
  return (float)(*(float *)(a1 + 8) * unk_18CD294);
}

