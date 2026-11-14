// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00448DC0 sub_448DC0
// UNREALRED VERIFIED [indirect-source-20261029] Shared entity/clutter VClip explosion helper calls radial4BAA30(position, damageScale*radius*vclipDamagePerMeter, radius, sourceHandle=-1, damageType=3). Disassembly448F56..448F6C pushes3 then-1. Its presentation owner/room arguments do not identify a damage attacker; do not substitute the exploding entity or its killer for this anonymous source.
// UNREALRED VERIFIED [combat-vclip-world-frame]: arg_18 is forwarded unchanged as optional direction vector to 0x506E20 at 0x448DCE..0x448DEB. Entity-death caller 0x420790 (push zero at 0x4207CD) and clutter-death caller 0x414950 (push zero at 0x414ACC) both supply null, so inline particles use authored global RF source direction, independent of the dying body orientation. Their explosion origin offsets are transformed separately before this call.
void __cdecl sub_448DC0(int a1, int a2, int a3, float *lhs, float a5, float a6, int a7)
{
  float v7; // [esp+Ch] [ebp-30h]
  int v8; // [esp+10h] [ebp-2Ch] BYREF
  int v9; // [esp+14h] [ebp-28h] BYREF
  float v10; // [esp+18h] [ebp-24h]
  float v11; // [esp+1Ch] [ebp-20h]
  float out_vector[3]; // [esp+20h] [ebp-1Ch] BYREF
  int v13; // [esp+2Ch] [ebp-10h]
  float v14; // [esp+30h] [ebp-Ch]
  int i; // [esp+34h] [ebp-8h]
  float definition_damage; // [esp+38h] [ebp-4h]

  if ( a1 >= 0 )
    rf_vclip_spawn_runtime_effect(a1, a2, a3, (int)lhs, a5, -1, a7, 1);
  definition_damage = 1.0;
  if ( a1 > -1 )
    definition_damage = rf_vclip_get_definition_damage(a1);
  v14 = a6 * a5 * definition_damage;
  for ( i = 0; i < rf_local_player_entry_count; ++i )
  {
    v13 = rf_entity_resolve_handle(*(_DWORD *)(rf_local_player_entries[i] + 20));
    if ( v13 )
    {
      v10 = v14;
      rf_vector_subtract(lhs, out_vector, (const float *)(v13 + 60));
      v11 = rf_vector3_length(out_vector);
      if ( v11 >= 1.0 )
        v10 = v10 / v11;
      if ( v10 > 25.0 )
      {
        *(float *)&v9 = v10 * 0.001000000047497451;
        rf_float_clamp_in_place((float *)&v9, 0.0, 0.99000001);
        v7 = rf_sqrt_float(*(float *)&v9);
        rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(*(_DWORD *)(v13 + 5168) + 196), *(float *)&v9, v7);
        rf_vector_normalize_reciprocal_sqrt(out_vector);
        *(float *)&v9 = rf_vector_dot((float *)(v13 + 2040), out_vector);
        *(float *)&v8 = (v10 - 25.0) / 25.0;
        rf_float_clamp_in_place((float *)&v8, 0.0, 1.0);
      }
    }
  }
  rf_damage_apply_radial(lhs, v14, a5, -1, 3);
}

