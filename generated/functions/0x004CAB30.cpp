// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CAB30 rf_particle_entity_damage_admitted
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl (particle120, float damage_amount, entity), result in AL. Admission predicate only; does not itself damage or modify either object. Entity is dereferenced before any nullable
// helper: DWORD +508 must equal 3, respawn-inactive helper and dead helper must not return exactly 1, particle owner handle +8 must differ from entity handle +44, and common flags
// +124 bit4 must be clear. Rejects multiplayer only when runtime mode byte equals 1 AND authority byte equals 0.
// Particle WORD +78 bit8 bypasses the armor/amount gate. Otherwise reject only when entity FLOAT +56 is ordered >=5 AND damage_amount is ordered <2.5. Native TEST AH,1/JNZ admits
// armor<5 or unordered; TEST AH,5/JP admits amount>=2.5 or unordered. NaNs therefore pass this subgate, subject to later tests.
// Entity cached room must be nonnull with raw BYTE room+352 nonzero. Strict sphere overlap uses entity common position +60 and PHYSICAL outer radius +384 (not common +120), against
// particle position +12 and F32(particle radius +56 * double 0.5). For entity DWORD +676 equal to global 0x911C80, a successfully resolved clutter UID from entity +5200 enables a
// final facing gate: F32(dot(entity forward +96, particle velocity +24)) must not be ordered negative. Unordered dot passes. The clutter object's fields are not read here. Returns
// AL=1 only after all gates.
char __cdecl rf_particle_entity_damage_admitted(int a1, float a2, int a3)
{
  float radius_b; // [esp+8h] [ebp-10h]
  float v5; // [esp+Ch] [ebp-Ch]
  int first_dword; // [esp+14h] [ebp-4h]

  if ( *(_DWORD *)(a3 + 508) != 3 )
    return 0;
  if ( rf_object_has_respawn_inactive_flag(a3) )
    return 0;
  if ( *(_DWORD *)(a1 + 8) == *(_DWORD *)(a3 + 44) )
    return 0;
  if ( rf_entity_is_dead(a3) )
    return 0;
  if ( (*(_DWORD *)(a3 + 124) & 4) != 0 )
    return 0;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    return 0;
  if ( (*(_WORD *)(a1 + 78) & 8) == 0 && *(float *)(a3 + 56) >= 5.0 && a2 < 2.5 )
    return 0;
  first_dword = rf_receiver_get_first_dword((void *)a3);
  if ( !first_dword )
    return 0;
  if ( !*(_BYTE *)(first_dword + 352) )
    return 0;
  radius_b = *(float *)(a1 + 56) * 0.5;
  if ( !rf_spheres_overlap_strict((const float *)(a3 + 60), (const float *)(a1 + 12), *(float *)(a3 + 384), radius_b) )
    return 0;
  if ( *(_DWORD *)(a3 + 676) == unk_911C80 )
  {
    if ( rf_clutter_find_by_uid(*(_DWORD *)(a3 + 5200)) )
    {
      v5 = rf_vector_dot((float *)(a3 + 96), (float *)(a1 + 24));
      if ( v5 < 0.0 )
        return 0;
    }
  }
  return 1;
}

