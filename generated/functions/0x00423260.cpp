// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423260 rf_entity_adjust_firing_orientation_toward_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Native cdecl THREE slots(entity,read-only muzzle point3,outMatrix9); saved two-argument prototype omitted orientation destination.
// Player-association4BCF40==EXACT AL1 copies entity retained matrix+2016 to output immediately, bypassing flinch/target checks. Other values:435D30 flinch updater any nonzero AL
// returns with output orientation UNCHANGED (updater may mutate entity override). Otherwise COMMON resolve entity AI target full handle+1376; missing target copies retained2016.
// Found COMMON target point first copies+60; independently resolve its full handle+44 as ENTITY and, if successful, replace point with entity retained+2004. Unchecked reciprocal-sqrt
// normalize(targetPoint-muzzlePoint); dot with source entity retained forward+2040, explicit FLOAT32 store, compare against exact DOUBLE0.8. ONLY ORDERED strict dot>0.8
// calls55C190(ECX outMatrix,normalizedForward,entity upHint+2028). Equal/less/UNORDERED leaves incoming output matrix UNCHANGED, no reset/copy fallback. Point argument is never
// intentionally written. Zero/coincident direction can yield NaN and take unchanged-orientation branch. No own pointer/output initialization/finite checks or canonical success
// result; returns incidental delegate/x87-status bits.55C190 retains its native unchecked normalization and degenerate-up behavior.
void __cdecl rf_entity_adjust_firing_orientation_toward_target(
        int entity,
        const float *muzzle_point,
        float *out_orientation)
{
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  float lhs[3]; // [esp+Ch] [ebp-24h] BYREF
  float out_vector[3]; // [esp+18h] [ebp-18h] BYREF
  int v6; // [esp+24h] [ebp-Ch]
  float v7; // [esp+28h] [ebp-8h]
  int v8; // [esp+2Ch] [ebp-4h]

  if ( rf_object_is_player_associated(entity) == 1 )
    goto LABEL_9;
  if ( rf_character_update_damage_flinch_override(entity) )
    return;
  v8 = rf_object_resolve_handle(*(_DWORD *)(entity + 1376));
  if ( !v8 )
  {
LABEL_9:
    rf_matrix3_copy(out_orientation, (const float *)(entity + 2016));
  }
  else
  {
    rf_vector3_copy_return_destination(lhs, (float *)(v8 + 60));
    v6 = rf_entity_resolve_handle(*(_DWORD *)(v8 + 44));
    if ( v6 )
      rf_vector_copy(lhs, copy_result, (const float *)(v6 + 2004));
    rf_vector_subtract(lhs, out_vector, muzzle_point);
    rf_vector_normalize_reciprocal_sqrt(out_vector);
    v7 = rf_vector_dot(out_vector, (float *)(entity + 2040));
    if ( v7 > 0.8 )
      rf_orientation_from_forward_and_up_hint(out_orientation, out_vector, (float *)(entity + 2028));
  }
}

