// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5740 rf_renderer_project_world_point_to_screen
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Uses a 48-byte local clip vertex. World-transform backend wrapper must return outcode zero; otherwise returns false without writing outputs. Projects through wrapper and requires flags byte+25 bit1 (projected). On success copies screenX+12 and screenY+16 to two supplied float pointers and returns1. Failed/rejected projection returns0; no pointer checks. The apparent 12-byte local in pseudocode is part of the full contiguous vertex stack record.
char __cdecl rf_renderer_project_world_point_to_screen(float *a1, float *a2, float *a3)
{
  _BYTE v4[12]; // [esp+4h] [ebp-30h] BYREF
  float v5; // [esp+10h] [ebp-24h]
  float v6; // [esp+14h] [ebp-20h]
  char v7; // [esp+1Dh] [ebp-17h]

  rf_vector_prefix_construct_noop(v4);
  if ( rf_renderer_transform_world_point_backend_wrapper((int)v4, a1) )
    return 0;
  rf_renderer_project_clip_vertex_backend_wrapper((int)v4);
  if ( (v7 & 1) == 0 )
    return 0;
  *a2 = v5;
  *a3 = v6;
  return 1;
}

