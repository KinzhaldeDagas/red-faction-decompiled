// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050DF90 rf_projectile_target_point_is_in_homing_cone
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Corrected incomplete stored one-argument type: cdecl projectile pointer and target entity pointer, one native caller50DDA0 pushes target then projectile and ADD ESP8. Subtracts projectile position+60 from target point+2004, unchecked-normalizes via559200, stores dot with projectile forward+96 as F32. Computes half-angle F32(info+308 * DOUBLE3.141592741012573 / DOUBLE180 * DOUBLE0.5), cos_float then F32. AL true iff cosine<=dot OR comparison UNORDERED (AH41/JNZ); NaN is admitted, unlike ordered cosine<=dot pseudocode. No distance, occlusion/team, NULL, zero-length, finite or angle-range check. Source508990 maps+308 to +View Cone degrees.
bool __cdecl rf_projectile_target_point_is_in_homing_cone(int projectile, int target_entity)
{
  float v3; // [esp+4h] [ebp-18h]
  float out_vector[3]; // [esp+8h] [ebp-14h] BYREF
  float v5; // [esp+14h] [ebp-8h]
  float v6; // [esp+18h] [ebp-4h]

  rf_vector_subtract((const float *)(target_entity + 2004), out_vector, (const float *)(projectile + 60));
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v6 = rf_vector_dot((float *)(projectile + 96), out_vector);
  v3 = *(float *)(*(_DWORD *)(projectile + 660) + 308) * 3.141592741012573 / 180.0 * 0.5;
  v5 = rf_cos_float(v3);
  return v5 <= (double)v6;
}

