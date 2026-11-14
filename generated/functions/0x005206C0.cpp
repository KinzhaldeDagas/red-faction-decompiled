// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005206C0 rf_render_entry_compare_camera_plane_side
// UNREALRED VERIFIED [room-render-20261028]: Evaluates signed plane distances of camera and entry position+4. Treats distance>=0 as positive side. Returns1 if same side,-1 if opposite; never0. Does not use entry radius or plane-normal normalization. Literal comparisons retained for unordered values.
int __cdecl rf_render_entry_compare_camera_plane_side(float *a1, int a2, float *a3)
{
  float v4; // [esp+0h] [ebp-8h]
  float v5; // [esp+4h] [ebp-4h]

  v5 = rf_plane_point_signed_distance(a1, a3);
  v4 = rf_plane_point_signed_distance(a1, (float *)(a2 + 4));
  if ( v5 >= 0.0 )
  {
    if ( v4 >= 0.0 )
      return 1;
    else
      return -1;
  }
  else if ( v4 >= 0.0 )
  {
    return -1;
  }
  else
  {
    return 1;
  }
}

