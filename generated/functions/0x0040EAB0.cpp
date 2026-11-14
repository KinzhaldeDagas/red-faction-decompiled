// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040EAB0 sub_40EAB0
// UNREALRED VERIFIED [combat-panic-20261104]: Builds random local graph route, used by panic and other callers.40DE20 retains endpoint hintsRoute+114/+118 and movement dimensions; clears endnode adjacency and optionallylinks priorhint;518D30 must succeed and count>=2. On success previousindex0,current1,route+134 deadline0,copy bodypriorpoint/endpoint snapshots. It does NOT reset inherited moverwait+144, interpolationbyte+15C or lateralfloat+158; do not replace with UE random reachable destination.
char __cdecl sub_40EAB0(int a1)
{
  float v2[3]; // [esp+0h] [ebp-20h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-14h] BYREF
  float *v4; // [esp+18h] [ebp-8h]
  float *v5; // [esp+1Ch] [ebp-4h]

  v5 = (float *)rf_entity_resolve_handle(a1);
  if ( !v5 )
    return 0;
  v4 = v5 + 354;
  unk_666408 = v5 + 392;
  rf_ai_publish_owner_route_search_request(v5);
  *(_DWORD *)(unk_666408 + 64) = unk_66641C != 1;
  rf_pointer_array_clear_count_keep_storage((_DWORD *)v4 + 48);
  if ( dword_66640C )
    rf_pointer_array_append_dword((_DWORD *)v4 + 48, dword_66640C);
  if ( !sub_518D30((int)&dword_6663FC) )
    return 0;
  *(_DWORD *)v4 = unk_666430;
  if ( *(int *)v4 < 2 )
    return 0;
  v4[5] = 0.0;
  *((_DWORD *)v4 + 6) = 1;
  rf_replicator_arm_milliseconds((int *)v4 + 77, 0);
  rf_vector_copy(v4 + 83, copy_result, v5 + 501);
  rf_vector_copy(v4 + 89, v2, v4 + 38);
  return 1;
}

