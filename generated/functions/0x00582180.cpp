// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582180 rf_renderer_transform_world_point_to_clip_vertex
// UNREALRED VERIFIED [renderer-polygons-20261028]: Subtracts camera position0x18CD5E8 from input world point,then multiplies by camera matrix rows0x18CD4B4..0x18CD4D4,writing cameraXYZ at output+0/+4/+8. If byte0x663F39 clear,overrides resulting z with global0x18CD380. Sets flagsbyte+25=0,recomputes outcodebyte+24 through rf_camera_frustum_outcode and returns it. Does not project screen x/y or initialize UV,color,channelcount or other payload. Uses local difference vector,so source/destination position alias is supported.
char __cdecl rf_renderer_transform_world_point_to_clip_vertex(int a1, float *lhs)
{
  float out_vector; // [esp+4h] [ebp-Ch] BYREF
  float v4; // [esp+8h] [ebp-8h]
  float v5; // [esp+Ch] [ebp-4h]

  rf_vector_subtract(lhs, &out_vector, &flt_18CD5E8);
  *(float *)a1 = out_vector * flt_18CD4B4 + v4 * unk_18CD4B8 + v5 * unk_18CD4BC;
  *(float *)(a1 + 4) = out_vector * unk_18CD4C0 + v4 * unk_18CD4C4 + v5 * unk_18CD4C8;
  *(float *)(a1 + 8) = out_vector * unk_18CD4CC + v4 * unk_18CD4D0 + v5 * unk_18CD4D4;
  if ( !byte_663F39 )
    *(float *)(a1 + 8) = unk_18CD380;
  *(_BYTE *)(a1 + 25) = 0;
  *(_BYTE *)(a1 + 24) = rf_camera_frustum_outcode((float *)a1);
  return *(_BYTE *)(a1 + 24);
}

