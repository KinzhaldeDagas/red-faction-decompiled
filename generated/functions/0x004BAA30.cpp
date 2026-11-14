// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BAA30 rf_damage_apply_radial
// UNREALRED VERIFIED [mission-unhide-20261020] Radial damage entity and clutter loops reject common inactive; the corpse list loop does not check that predicate. UnrealRed filters inactive live character radial candidates and inactive clutter, while preserving corpse candidacy. This filter must not be copied to direct common damage dispatch4BB070.
// UNREALRED VERIFIED [indirect-source-20261029] At4BAB56..4BAB5F a nonzero multiplayer-runtime byte jumps to4BAC61, bypassing BOTH clutter and corpse loops. Entity iteration precedes this branch; remote-charge iteration and glass radial handling follow it and remain active in MP. This is a radial candidate-list rule, not a general immunity rule for direct damage.
void __cdecl rf_damage_apply_radial(float *a1, float a2, float a3, int a4, int a5)
{
  int k; // [esp+10h] [ebp-28h]
  int j; // [esp+14h] [ebp-24h]
  int i; // [esp+18h] [ebp-20h]
  int m; // [esp+1Ch] [ebp-1Ch]
  int v9[3]; // [esp+20h] [ebp-18h] BYREF
  int v10[3]; // [esp+2Ch] [ebp-Ch] BYREF

  if ( a2 > 0.0 && a3 > 0.1000000014901161 )
  {
    rf_vector3_default_construct_noop(v10);
    rf_vector3_default_construct_noop(v9);
    *(float *)v10 = *a1 - a3;
    *(float *)&v10[1] = a1[1] - a3;
    *(float *)&v10[2] = a1[2] - a3;
    *(float *)v9 = *a1 + a3;
    *(float *)&v9[1] = a1[1] + a3;
    *(float *)&v9[2] = a1[2] + a3;
    for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
    {
      if ( !rf_entity_has_attached_use_vehicle(i)
        && !rf_object_has_respawn_inactive_flag(i)
        && rf_aabb_overlap_inclusive((float *)v10, (float *)v9, (float *)(i + 400), (float *)(i + 412)) )
      {
        rf_damage_apply_radial_to_target(i, (int)a1, a2, a3, a4, a5);
      }
    }
    if ( !rf_multiplayer_runtime_mode )
    {
      for ( j = rf_clutter_list_head; (_UNKNOWN *)j != &unk_666D18; j = *(_DWORD *)(j + 652) )
      {
        if ( !rf_object_has_respawn_inactive_flag(j)
          && rf_aabb_overlap_inclusive((float *)v10, (float *)v9, (float *)(j + 400), (float *)(j + 412)) )
        {
          rf_damage_apply_radial_to_target(j, (int)a1, a2, a3, a4, a5);
        }
      }
      for ( k = rf_corpse_list_head; (_UNKNOWN *)k != &unk_681AF8; k = *(_DWORD *)(k + 652) )
      {
        if ( rf_aabb_overlap_inclusive((float *)v10, (float *)v9, (float *)(k + 400), (float *)(k + 412)) )
          rf_damage_apply_radial_to_target(k, (int)a1, a2, a3, a4, a5);
      }
    }
    for ( m = dword_911F74; (_UNKNOWN *)m != &unk_911CE8; m = *(_DWORD *)(m + 652) )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(m + 660) + 612) & 0x40) != 0
        && rf_aabb_overlap_inclusive((float *)v10, (float *)v9, (float *)(m + 400), (float *)(m + 412)) )
      {
        rf_damage_apply_radial_to_target(m, (int)a1, a2, a3, a4, a5);
      }
    }
    rf_glass_radial_damage((int)a1, (int)v10, (int)v9, a2, a3);
  }
}

