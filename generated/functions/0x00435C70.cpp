// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435C70 rf_entity_secondary_tag_position
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity,outPosition3), explicit fullEAX0/-1. Same native flow as435BB0 but uses class660 inline
// array+456 and tag counter entity1292. Signed count>0 plus nonNULL model128 admits; negative counter is persistently reset0, nonnegative out-of-range counter unguarded. Raw tag
// atinline+4+4*counter passed to5651D0 with entity COMMON72/60, local matrix and caller position, return ignored; EAX0 means composition attempted, not valid node output.
// Count<=0/modelNULL writes caller position=COMMON60 then EAX-1. No selected-secondary680 test, tag!=-1/output/pointer/finite validation, fallback after node failure or rollback.
int __cdecl rf_entity_secondary_tag_position(unsigned int *entity, float *out_position)
{
  int v3; // [esp-14h] [ebp-44h]
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  char v5[36]; // [esp+Ch] [ebp-24h] BYREF

  if ( rf_receiver_get_first_dword((void *)(entity[165] + 456)) > 0 && entity[32] )
  {
    rf_matrix3_construct(v5);
    if ( (entity[323] & 0x80000000) != 0 )
      entity[323] = 0;
    v3 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(entity[165] + 456), entity[323]);
    rf_vmesh_compose_prop_world_transform(
      entity[32],
      v3,
      (float *)entity + 18,
      (int)(entity + 15),
      (int)v5,
      out_position);
    return 0;
  }
  else
  {
    rf_vector_copy(out_position, copy_result, (const float *)entity + 15);
    return -1;
  }
}

