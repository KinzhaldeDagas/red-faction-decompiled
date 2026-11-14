// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477D30 rf_push_region_find_containing_point
// UNREALRED VERIFIED [combat-particle-wind-20261029]: Ordered first-enabled-containing-region selection, not summed fields. Sphere boundary is strict squaredDistance<storedRadiusSquared; axis-aligned and oriented box bounds include surfaces and use half serialized full dimensions. Unknown shape IDs produce no containing match.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): ABI correction verified against every native branch: one cdecl const float point pointer on stack, common-region pointer returned in EAX; NO
// incoming ST0 argument and no void result. Sphere branch first produces its own x87 squared-distance value via vector helper, stores it to an eight-byte local before pointer-array
// lookup, compares region FLOAT+60 ordered strictly greater than distance. First enabled BYTE+104 region matching shape1 sphere,2 AABB(min+64,max+76),3 oriented
// box(center+12,matrix+24,full dimensions+88) returns region pointer; enabled means any nonzero byte. Unknown shape continues. Signed registry loop count re-read each iteration; miss
// returns EAX0. No summing across overlapping regions. Correcting old usercall prototype removes fictitious propagated ST0 inputs in push-region callers while preserving original
// code and all existing semantic comments.
int __cdecl rf_push_region_find_containing_point(const float *point)
{
  int v1; // eax
  int v2; // eax
  const float *v4; // [esp-8h] [ebp-18h]
  const float *v5; // [esp-4h] [ebp-14h]
  float *v6; // [esp-4h] [ebp-14h]
  const float *v7; // [esp-4h] [ebp-14h]
  double v8; // [esp+0h] [ebp-10h]
  int v9; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_push_region_registry); ++i )
  {
    if ( *(_BYTE *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 104) )
    {
      v9 = **(_DWORD **)sub_552200(rf_push_region_registry, i);
      switch ( v9 )
      {
        case 1:
          v5 = (const float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 12);
          v8 = rf_vector_distance_squared(point, v5);
          if ( *(float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 60) > v8 )
            return *(_DWORD *)sub_552200(rf_push_region_registry, i);
          break;
        case 2:
          v6 = (float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 76);
          v1 = sub_552200(rf_push_region_registry, i);
          if ( rf_aabb_contains_point_inclusive((float *)point, (float *)(*(_DWORD *)v1 + 64), v6) )
            return *(_DWORD *)sub_552200(rf_push_region_registry, i);
          break;
        case 3:
          v7 = (const float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 88);
          v4 = (const float *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 24);
          v2 = sub_552200(rf_push_region_registry, i);
          if ( rf_oriented_box_contains_point(point, (const float *)(*(_DWORD *)v2 + 12), v4, v7) )
            return *(_DWORD *)sub_552200(rf_push_region_registry, i);
          break;
      }
    }
  }
  return 0;
}

