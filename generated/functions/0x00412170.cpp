// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412170 rf_camera_slot_enter_third_person
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(slot pointer), canonical AL0/1. ENTITY resolve from slot.player DWORD+20; missing entity returnsAL0 with camera/slot
// unchanged. Success first stores entity full handle+44 at camera+512. If prior slot state DWORD+8 is EXACT2, assigns camera+520=camera+228 minus entity+2004, inverse-rotates that
// vector by entity+2016, then assigns camera+532=camera orientation+252 times transpose(entity+2016), using argument-times-receiver matrix ABI. All other prior states set
// camera+520=(0,0,-4) and camera+532=identity. Finally slot state=1 and AL1. Does not directly update camera COMMON/retained pose, room, target reciprocal field or run interpolation.
// No camera/player/class pointer guards or matrix normalization.
char __cdecl rf_camera_slot_enter_third_person(int *a1)
{
  float *v2; // eax
  const float *v3; // eax
  float *v4; // eax
  const float *v5; // [esp+8h] [ebp-6Ch]
  float v6[9]; // [esp+Ch] [ebp-68h] BYREF
  _BYTE v7[36]; // [esp+30h] [ebp-44h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+60h] [ebp-14h] BYREF
  int v10; // [esp+6Ch] [ebp-8h]
  int v11; // [esp+70h] [ebp-4h]

  v11 = *a1;
  v10 = rf_entity_resolve_handle(*(_DWORD *)(a1[1] + 20));
  if ( !v10 )
    return 0;
  *(_DWORD *)(v11 + 512) = *(_DWORD *)(v10 + 44);
  if ( a1[2] == 2 )
  {
    v2 = rf_vector_subtract((const float *)(v11 + 228), out_vector, (const float *)(v10 + 2004));
    rf_vector_copy((float *)(v11 + 520), copy_result, v2);
    rf_matrix3_inverse_rotate_vector((float *)(v11 + 520), (float *)(v10 + 2016));
    v5 = (const float *)(v11 + 252);
    v3 = (const float *)rf_matrix3_transpose_to_output((float *)(v10 + 2016), (int)v7);
    v4 = rf_matrix3_argument_times_receiver_to_output(v3, v6, v5);
    rf_matrix3_copy((float *)(v11 + 532), v4);
  }
  else
  {
    rf_vector3_set_components_thiscall((float *)(v11 + 520), 0.0, 0.0, -4.0);
    rf_identity_orientation_matrix((float *)(v11 + 532));
  }
  a1[2] = 1;
  return 1;
}

