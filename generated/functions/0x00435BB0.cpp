// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435BB0 rf_entity_primary_tag_position
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity,outPosition3), explicit fullEAX0/-1, not transform-validity guarantee. Require SIGNED
// firstDWORD[class660+444]>0 and nonNULL entity model128. Admitted path runs no-op local matrix ctor, clamps signed entity tag counter1296<0 to0 IN PLACE, no upper-count check.
// Unchecked inline DWORD element(class+444,index1296) supplies raw tag, even-1. Call5651D0(model,tag,COMMON matrix72,COMMON position60,localMatrix,outPosition), ignore
// return/underlying adapter validity, returnEAX0. Composer may consume untouched node-transform scratch; no safe-position fallback for its failure. If count<=0 OR modelNULL, copy
// COMMON position60 to caller output, return fullEAX-1. No selected-weapon676 test, entity/class/output pointer validation, alias snapshot or rollback; fallback writes output even
// though return-1.
int __cdecl rf_entity_primary_tag_position(unsigned int *entity, float *out_position)
{
  int v3; // [esp-14h] [ebp-44h]
  float copy_result[3]; // [esp+0h] [ebp-30h] BYREF
  char v5[36]; // [esp+Ch] [ebp-24h] BYREF

  if ( rf_receiver_get_first_dword((void *)(entity[165] + 444)) > 0 && entity[32] )
  {
    rf_matrix3_construct(v5);
    if ( (entity[324] & 0x80000000) != 0 )
      entity[324] = 0;
    v3 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(entity[165] + 444), entity[324]);
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

