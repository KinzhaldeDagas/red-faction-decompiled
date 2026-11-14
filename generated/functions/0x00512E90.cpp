// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512E90 rf_projected_shadow_walk_intersecting_geometry
// UNREALRED VERIFIED [general-gap-20260830]: Recursively walks intersecting level geometry for one projected-shadow volume and clips each admitted candidate polygon.
// UNREALRED VERIFIED [projected-shadow-receiver-20260903]: Binds the shadow texture, starts an explicit node stack at Room+0x3C, AABB-tests every node against Projector+0xE4/+0xF0, pushes both non-null children at Node+0x20/+0x24, processes the face collection at Node+0x18, and recursively traverses every room pointer in Room+0x6C. This is an all-overlap traversal, not a nearest-hit query.
int __cdecl rf_projected_shadow_walk_intersecting_geometry(int a1, int a2, float *a3, float *a4, float *a5)
{
  int result; // eax
  int *v6; // eax
  int v7; // [esp+0h] [ebp-Ch]
  int v8; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  rf_renderer_set_pending_texture_handles(rf_projected_shadow_texture_handle, -1);
  unk_927410[0] = *(_DWORD *)(a1 + 60);
  v8 = 1;
  while ( v8 > 0 )
  {
    v7 = unk_927410[--v8];
    if ( rf_aabb_overlap_strict_ordered((float *)v7, (float *)(v7 + 12), a3 + 57, a3 + 60) )
    {
      if ( *(_DWORD *)(v7 + 32) )
        unk_927410[v8++] = *(_DWORD *)(v7 + 32);
      if ( *(_DWORD *)(v7 + 36) )
        unk_927410[v8++] = *(_DWORD *)(v7 + 36);
      rf_projected_shadow_clip_polygon(a2, a3, (void *)(v7 + 24), a4, a5);
    }
  }
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 108));
    if ( i >= result )
      break;
    v6 = (int *)sub_552200((_DWORD *)(a1 + 108), i);
    rf_projected_shadow_walk_intersecting_geometry(*v6, a2, a3, (int)a4, a5);
  }
  return result;
}

