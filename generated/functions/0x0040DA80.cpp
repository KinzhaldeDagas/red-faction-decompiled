// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040DA80 rf_player_entity_mutual_use_target_test
// UNREALRED VERIFIED [trigger-use-20261021] Uses common+0x3C positions, +0x78 radii, and third matrix rows+0x60 for mutual facing. Stored float distance must be <= radiusA+radiusB+double2.5. Each stored float dot is compared with double0.3. No LOS trace. Coincident positions normalize without a zero guard; with masked IEEE exceptions both unordered fcomp/test-ah-5/jp branches admit. UnrealRed preserves that case; UE body forward is the current host facing adapter, not a claim of full raw RF pose/physics parity.
bool __cdecl rf_player_entity_mutual_use_target_test(int a1, int a2)
{
  float *v4; // eax
  float copy_result[3]; // [esp+0h] [ebp-2Ch] BYREF
  float v6[3]; // [esp+Ch] [ebp-20h] BYREF
  float v7; // [esp+18h] [ebp-14h]
  float out_vector[3]; // [esp+1Ch] [ebp-10h] BYREF
  float v9; // [esp+28h] [ebp-4h]

  if ( !rf_entity_auto_trigger_use_candidate(a2) )
    return 0;
  v7 = rf_vector_distance((const float *)(a1 + 60), (const float *)(a2 + 60));
  if ( v7 > *(float *)(a1 + 120) + *(float *)(a2 + 120) + 2.5 )
    return 0;
  rf_vector_subtract((const float *)(a2 + 60), out_vector, (const float *)(a1 + 60));
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v9 = rf_vector_dot((float *)(a1 + 96), out_vector);
  if ( v9 < 0.3 )
    return 0;
  v4 = rf_vector_negate(out_vector, v6);
  rf_vector_copy(out_vector, copy_result, v4);
  v9 = rf_vector_dot((float *)(a2 + 96), out_vector);
  return v9 >= 0.3;
}

