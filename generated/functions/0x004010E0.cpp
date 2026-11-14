// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004010E0 rf_ai_copy_target_point_for_current_movement
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl(required AI block,target object,output vector). Compares source entity current descriptor+2136 by POINTER EQUALITY with registry
// lookup445740(7), then445740(9); either match copies target common position+60. Registry lookup can fall back to slot0 and changes its own selected-index global, so these are not
// guaranteed descriptor-index7/9 tests. Otherwise source crouch predicate AL==EXACT1 also copies common position. Remaining path calls object point helper(target,out), ignores its
// return, subtracts DOUBLE0.10000000149011612 from output.Y and rounds to float32. Helper uses resolved entity retained point+2004 or common position; no own target/output null
// guard, finite check or normalization. A failed point helper can leave prior output data that still has Y adjusted. EAX is incidental vector-helper/local-output address on early
// copy paths, output address on final path; do not rely on inferred int return as status.
float *__cdecl rf_ai_copy_target_point_for_current_movement(int *a1, int a2, float *destination)
{
  int v3; // esi
  int v4; // esi
  float v6[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  v3 = *a1;
  if ( *(char **)(v3 + 2136) == sub_445740(7u) )
    return rf_vector_copy(destination, copy_result, (const float *)(a2 + 60));
  v4 = *a1;
  if ( *(char **)(v4 + 2136) == sub_445740(9u) )
    return rf_vector_copy(destination, copy_result, (const float *)(a2 + 60));
  if ( rf_entity_is_crouched_state810(*a1) )
    return rf_vector_copy(destination, v6, (const float *)(a2 + 60));
  rf_object_copy_entity_vector7D4_or_position(a2, destination);
  destination[1] = destination[1] - 0.1000000014901161;
  return destination;
}

