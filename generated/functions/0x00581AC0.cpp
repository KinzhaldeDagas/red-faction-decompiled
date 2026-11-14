// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581AC0 rf_renderer_project_world_width_to_pixels
// UNREALRED VERIFIED [renderer-mesh-20261028]: Arguments clipvertex and pointer tofloatwidth. Returns float-rounded(*width*0x18CD3BC*0x18CD1C8 / vertex.cameraZ+8) in x87. No projectionflag or zero-z check. Does not consume projectedreciprocal or depthbias; widthpointer not modified.
double __cdecl rf_renderer_project_world_width_to_pixels(int a1, float *a2)
{
  return (float)(*a2 * unk_18CD3BC * unk_18CD1C8 / *(float *)(a1 + 8));
}

