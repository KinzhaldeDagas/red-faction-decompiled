// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B280 rf_entity_update_attached_clutter_pose
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity,signed slot), no slot bounds or nonnegative check. Constructs no-write local vector/matrix; resolves entity DWORD[5212+4*slot]
// as full CLUTTER UID/type4. Miss returns EAX0 without output writes. Found clutter additionally requires signed gameplay class(+660) DWORD[1772+4*slot]>=0; negative tag returns
// EAX=entity pointer, not failure-1. Admitted path calls5651D0(entity model+128,tag,entity COMMON matrix+72,COMMON position+60,localMatrix,localPoint), ignoring result and without
// own model/tag validity guard. Copies localPoint to clutter vector+240 BEFORE thiscall4BC330(clutter,localPoint), which publishes position+60/current+228/predicted+240 and derived
// bounds through delegate. Then copies localMatrix to clutter matrices+72,+252,+288, in that order. Successful EAX is final matrix-copy residue clutter+312, not a success Boolean. No
// rollback/pose snapshot on model-node failure, no entity pose writes or ownership/death/visibility gate.
float *__cdecl rf_entity_update_attached_clutter_pose(int a1, int a2)
{
  float *result; // eax
  float copy_result[3]; // [esp+0h] [ebp-40h] BYREF
  float v4[9]; // [esp+Ch] [ebp-34h] BYREF
  float source[3]; // [esp+30h] [ebp-10h] BYREF
  float *v6; // [esp+3Ch] [ebp-4h]

  rf_vector3_default_construct_noop(source);
  rf_matrix3_construct((char *)v4);
  result = (float *)rf_clutter_find_by_uid(*(_DWORD *)(a1 + 4 * a2 + 5212));
  v6 = result;
  if ( result )
  {
    result = (float *)a1;
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * a2 + 1772) >= 0 )
    {
      rf_vmesh_compose_prop_world_transform(
        *(_DWORD *)(a1 + 128),
        *(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * a2 + 1772),
        (float *)(a1 + 72),
        a1 + 60,
        (int)v4,
        source);
      rf_vector_copy(v6 + 60, copy_result, source);
      rf_object_publish_position_and_bounds((int)v6, source);
      rf_matrix3_copy(v6 + 18, v4);
      rf_matrix3_copy(v6 + 63, v4);
      return (float *)rf_matrix3_copy(v6 + 72, v4);
    }
  }
  return result;
}

