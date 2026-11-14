// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFAC0 rf_projectile_target_passes_pair_gate
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, ordered object-pair type matrix, side-specific INOUT mask writes, native x87 unordered branches and projectile global-plane gate): 
// Cdecl(projectile,target,lowByteGuard), AL1=admitted,0=rejected. No own null/type/class guard. Computes common-position difference target60-projectile60, dot with projectile COMMON
// forward96, stores dot to binary32, rejects ONLY ordered dot<0. Zero or NaN dot passes; no normalization or radius in this facing test.
// Guard BYTE0 returns1 immediately after facing test. Nonzero guard resolves projectile owner48 as ENTITY. Rejects only when owner exists, owner common friendliness504==0, target
// friendliness504==0, owner entity field1376 != target HANDLE44, AND target type0 predicate true. This is literal zero-friendliness/identifier behavior, not a generic team or
// self-hit rule; owner absence, exception handle equality, or nonentity target bypasses it.
// Then projectile class616 mask0x20 enables FOUR GLOBAL plane tests at813BD8+16*i. For each, signed plane distance uses target PHYSICAL position228, unlike common-position facing
// above. Reject only when -(target physical radius384+projectile physical radius384) is ORDERED > plane distance. Sum/negation remain in x87 with NO binary32 store before FCOMPP;
// unordered comparisons never reject that plane. Equality admits. Caller must have prepared appropriate global planes; no per-projectile owner/serial check, cache rebuild,
// finite/zero-radius/normal validation or state write. AL1 only after all enabled tests pass; no F/output mask parameter.
char __cdecl rf_projectile_target_passes_pair_gate(int a1, int a2, char a3)
{
  int i; // [esp+0h] [ebp-18h]
  int v5; // [esp+4h] [ebp-14h]
  float out_vector[3]; // [esp+8h] [ebp-10h] BYREF
  float v7; // [esp+14h] [ebp-4h]

  rf_vector_subtract((const float *)(a2 + 60), out_vector, (const float *)(a1 + 60));
  v7 = rf_vector_dot((float *)(a1 + 96), out_vector);
  if ( v7 < 0.0 )
    return 0;
  if ( a3 )
  {
    v5 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 48));
    if ( v5
      && !*(_DWORD *)(v5 + 504)
      && !*(_DWORD *)(a2 + 504)
      && *(_DWORD *)(v5 + 1376) != *(_DWORD *)(a2 + 44)
      && rf_object_is_entity(a2) )
    {
      return 0;
    }
    if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 0x20) != 0 )
    {
      for ( i = 0; i < 4; ++i )
      {
        if ( -(*(float *)(a2 + 384) + *(float *)(a1 + 384)) > rf_plane_point_signed_distance(
                                                                &flt_813BD8[4 * i],
                                                                (float *)(a2 + 228)) )
          return 0;
      }
    }
  }
  return 1;
}

