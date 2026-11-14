// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00406620 rf_ai_mode8_face_auxiliary_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode8 handler. Resolves COMMON auxiliary handle+724 (not ordinary target+704);
// missing makes no own state changes. Valid record ->no-write vector constructor, object retained-entity-point/common-position helper(record,out), ignores helper return;
// calls410920(owner,out), stores returnedST0 float32. Ordered result<DOUBLE0.15 calls40A2A0(block), then arms look deadline+1256 for500ms and copies all three computed point floats
// to block+1260. Equality/greater/NaN does not take completion branch. No own target clear, route reset or return-status construction.
void __cdecl rf_ai_mode8_face_auxiliary_target(_DWORD *a1)
{
  float copy_result[3]; // [esp+0h] [ebp-20h] BYREF
  float source[3]; // [esp+Ch] [ebp-14h] BYREF
  int v3; // [esp+18h] [ebp-8h]
  float v4; // [esp+1Ch] [ebp-4h]

  v3 = rf_object_resolve_handle(a1[181]);
  if ( v3 )
  {
    rf_vector3_default_construct_noop(source);
    rf_object_copy_entity_vector7D4_or_position(v3, source);
    v4 = sub_410920(*a1, source);
    if ( v4 < 0.15 )
    {
      sub_40A2A0(a1);
      rf_replicator_arm_milliseconds(a1 + 314, 500);
      rf_vector_copy((float *)a1 + 315, copy_result, source);
    }
  }
}

