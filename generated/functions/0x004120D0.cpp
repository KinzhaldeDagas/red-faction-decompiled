// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004120D0 rf_camera_slot_enter_first_person
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(slot pointer), canonical AL0/1 only. Reads camera=slot DWORD0 and player=slot DWORD1, resolves ENTITY using player
// DWORD+20; no slot/player/camera pointer guards. Resolution failure returnsAL0 before any camera/slot writes. Success stores resolved entity full handle+44 at camera+512; assigns
// camera position+60 from entity retained position+2004, camera orientation+72 from entity COMMON orientation+72, camera retained orientation+2016 from entity+2016, in that order.
// Uses first-DWORD getter486DE0(entity) as room argument to4BC210(camera,room), then writes slot DWORD+8=0 and returnsAL1. Calls vector assignment with separate caller result
// scratch, not scratch as persistent destination. No reciprocal entity+2252 relation, pending state or rollback.
char __cdecl rf_camera_slot_enter_first_person(float **a1)
{
  int first_dword; // eax
  float copy_result[3]; // [esp+0h] [ebp-14h] BYREF
  int v4; // [esp+Ch] [ebp-8h]
  float *v5; // [esp+10h] [ebp-4h]

  v5 = *a1;
  v4 = rf_entity_resolve_handle(*((_DWORD *)a1[1] + 5));
  if ( !v4 )
    return 0;
  v5[128] = *(float *)(v4 + 44);
  rf_vector_copy(v5 + 15, copy_result, (const float *)(v4 + 2004));
  rf_matrix3_copy(v5 + 18, (const float *)(v4 + 72));
  rf_matrix3_copy(v5 + 504, (const float *)(v4 + 2016));
  first_dword = rf_receiver_get_first_dword((void *)v4);
  rf_object_set_room_and_cache_position(v5, first_dword);
  a1[2] = nullptr;
  return 1;
}

