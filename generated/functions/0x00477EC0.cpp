// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477EC0 rf_push_region_flag40_contains_point
// UNREALRED VERIFIED [level-lifecycle-20261028]: Returns bool in AL (current decompiler void/x87 prototype is misleading). Scans push registry; requires enable byte+104==exactly1 and raw flags+8 mask0x40. Shape1 returns true only when squared distance(point,position+12)<float+60, strict sphere boundary. Shape2 uses inclusive AABB at+64/+76; shape3 oriented-box test position+12,matrix+24. Unsupported shapes skipped, no match false. Meaning of raw flag0x40 remains unproven; unlike general finder enable test is exact1.
void __cdecl rf_push_region_flag40_contains_point(float *point)
{
  int v2; // eax
  int v3; // eax
  int v4; // eax
  const float *v5; // [esp-8h] [ebp-18h]
  float *v6; // [esp-4h] [ebp-14h]
  const float *v7; // [esp-4h] [ebp-14h]
  double v8; // [esp+0h] [ebp-10h]
  int v9; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_push_region_registry); ++i )
  {
    if ( *(_BYTE *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 104) == 1
      && (*(_DWORD *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 8) & 0x40) != 0 )
    {
      v9 = **(_DWORD **)sub_552200(rf_push_region_registry, i);
      switch ( v9 )
      {
        case 1:
          v2 = sub_552200(rf_push_region_registry, i);
          v8 = rf_vector_distance_squared(point, (const float *)(*(_DWORD *)v2 + 12));
          if ( *(float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 60) > v8 )
            return;
          break;
        case 2:
          v6 = (float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 76);
          v3 = sub_552200(rf_push_region_registry, i);
          if ( rf_aabb_contains_point_inclusive(point, (float *)(*(_DWORD *)v3 + 64), v6) )
            return;
          break;
        case 3:
          v7 = (const float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 88);
          v5 = (const float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 24);
          v4 = sub_552200(rf_push_region_registry, i);
          if ( rf_oriented_box_contains_point(point, (const float *)(*(_DWORD *)v4 + 12), v5, v7) )
            return;
          break;
      }
    }
  }
}

