// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050DDA0 rf_projectile_auto_acquire_target
// UNREALRED VERIFIED [weapon-penetration-radius] Filters live entities by common-object collision radius +0x180, including the decoded 0.5-unit minimum, proving this field is geometric radius rather than physical mass.
void __cdecl rf_projectile_auto_acquire_target(int projectile)
{
  float v1; // [esp+0h] [ebp-24h]
  int v2; // [esp+4h] [ebp-20h]
  float v3; // [esp+8h] [ebp-1Ch]
  bool v4; // [esp+Fh] [ebp-15h]
  _BYTE v5[12]; // [esp+14h] [ebp-10h] BYREF
  int target_entity; // [esp+20h] [ebp-4h]

  if ( projectile )
  {
    rf_vector3_default_construct_noop(v5);
    v2 = -1;
    v3 = *(float *)(*(_DWORD *)(projectile + 660) + 312);
    v4 = (*(_DWORD *)(*(_DWORD *)(projectile + 660) + 612) & 0x10000) != 0;
    rf_entity_resolve_handle(*(_DWORD *)(projectile + 48));
    for ( target_entity = dword_68211C;
          (_UNKNOWN *)target_entity != &unk_681E90;
          target_entity = *(_DWORD *)(target_entity + 652) )
    {
      if ( !rf_object_has_respawn_inactive_flag(target_entity)
        && !rf_entity_is_dead(target_entity)
        && *(_DWORD *)(projectile + 48) != *(_DWORD *)(target_entity + 44)
        && (!v4 || rf_entity_runtime_flags810_has_mask2000(target_entity))
        && *(float *)(target_entity + 384) >= 0.5
        && ((unsigned int)&unk_800000 & *(_DWORD *)(*(_DWORD *)(target_entity + 660) + 1828)) == 0 )
      {
        v1 = rf_vector_fast_distance((const float *)(projectile + 60), (const float *)(target_entity + 2004));
        if ( *(float *)(*(_DWORD *)(projectile + 660) + 312) > (double)v1
          && rf_projectile_target_point_is_in_homing_cone(projectile, target_entity)
          && (!rf_geometry_segment_is_obstructed(
                 (float *)(projectile + 60),
                 (float *)(target_entity + 2004),
                 3,
                 nullptr)
           || !rf_geometry_segment_is_obstructed((float *)(projectile + 60), (float *)(target_entity + 60), 3, nullptr))
          && v3 > (double)v1 )
        {
          v3 = v1;
          v2 = *(_DWORD *)(target_entity + 44);
        }
      }
    }
    *(_DWORD *)(projectile + 744) = v2;
  }
}

