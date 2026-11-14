// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477CA0 rf_world_obb_region_find_containing_point
// UNREALRED VERIFIED [level-lifecycle-20261028]: Scans registry0x6FC3E8 in order and invokes rf_oriented_box_contains_point with caller point, record position+4 and orientation+16. Returns first containing record or0. No enable-byte/type filtering or null-record check in this body. Does not assume this registry is a push-region registry.
int __cdecl rf_world_obb_region_find_containing_point(float *point)
{
  int v1; // eax
  const float *v3; // [esp-8h] [ebp-Ch]
  const float *v4; // [esp-4h] [ebp-8h]
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(unk_6FC3E8); ++i )
  {
    v4 = (const float *)(*(_DWORD *)sub_552200(unk_6FC3E8, i) + 52);
    v3 = (const float *)(*(_DWORD *)sub_552200(unk_6FC3E8, i) + 16);
    v1 = sub_552200(unk_6FC3E8, i);
    if ( rf_oriented_box_contains_point(point, (const float *)(*(_DWORD *)v1 + 4), v3, v4) )
      return *(_DWORD *)sub_552200(unk_6FC3E8, i);
  }
  return 0;
}

