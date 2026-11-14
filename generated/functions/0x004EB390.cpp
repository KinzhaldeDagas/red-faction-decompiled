// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EB390 rf_player_target_forward_cone_score
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Cdecl(player,target entity,float*score), assumes pointers valid except own UID resolution may fail->AL0. Delta=target point2004-own point2004, unchecked normalization, dot with own forward2040, both dot and cos(F320.52359879) storedF32. Native rejects ONLY ordered cos>dot. Equal or UNORDERED comparisons pass, write F32(dot-cos),AL1; hence degenerate/NaN vector can report true with NaN score. On rejection score untouched. No distance/visibility/death test here; caller4EB210 applies those separately.
char __cdecl rf_player_target_forward_cone_score(int a1, int a2, float *a3)
{
  float out_vector[3]; // [esp+4h] [ebp-18h] BYREF
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]
  int v7; // [esp+18h] [ebp-4h]

  v7 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v7 )
    return 0;
  rf_vector_subtract((const float *)(a2 + 2004), out_vector, (const float *)(v7 + 2004));
  rf_vector_normalize_reciprocal_sqrt(out_vector);
  v6 = rf_vector_dot((float *)(v7 + 2040), out_vector);
  v5 = rf_cos_float(0.52359879);
  if ( v5 > (double)v6 )
    return 0;
  *a3 = v6 - v5;
  return 1;
}

