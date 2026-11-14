// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426790 rf_entity_update_allocated_sphere_center_positions
// [UnrealRed physical spheres 2026-11-12; verified ASM] Updates separate allocated12-byte world-position array Entity+13DC using standingcount. If crouched AND index>0 uses crouch center; index0 deliberately remains standing. Rotates with common48 then addscommon3C. This is NOT the physical24 updater used by410170.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl required entity, returns final standing-count getter EAX, not success. Starts no-op local matrix/vector constructors. Signed
// i=0..<DWORD[entity.definition668+3308] re-reads definition pointer and standing count each bound. Every iteration calls crouch810 predicate; ANY nonzero AND signed i>0 chooses
// inline40 source record at definition668+3632, otherwise source at+3308, including deliberate standing index0 while crouched. No crouch-count test. Accessor43CD60 computes
// arrayBase+4+40*i; copies center vector at element+24 into local vector, rotates ROW-vector by current entity COMMON matrix+72, adds current position+60 with native FLOAT32
// vector-helper stores, and sequentially assigns to allocated destination DWORD entity+5084 plus12*i. Destination base is reread each iteration; this body neither allocates nor
// validates its length/nullness. No radius copy or physical24 contact record update; no array capacity, entity/definition/finite guards, snapshot or rollback. Nonpositive standing
// count makes no destination writes.
int __cdecl rf_entity_update_allocated_sphere_center_positions(int a1)
{
  int result; // eax
  int element_address; // eax
  int v3; // eax
  float *v4; // eax
  float v5[3]; // [esp+0h] [ebp-64h] BYREF
  float sum_result[3]; // [esp+Ch] [ebp-58h] BYREF
  float v7[3]; // [esp+18h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+24h] [ebp-40h] BYREF
  char v9[36]; // [esp+30h] [ebp-34h] BYREF
  int i; // [esp+54h] [ebp-10h]
  float destination[3]; // [esp+58h] [ebp-Ch] BYREF

  rf_matrix3_construct(v9);
  rf_vector3_default_construct_noop(destination);
  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(*(_DWORD *)(a1 + 668) + 3308));
    if ( i >= result )
      break;
    if ( rf_entity_is_crouched_state810(a1) && i > 0 )
    {
      element_address = rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3632), i);
      rf_vector_copy(destination, copy_result, (const float *)(element_address + 24));
    }
    else
    {
      v3 = rf_inline_array40_get_element_address((void *)(*(_DWORD *)(a1 + 668) + 3308), i);
      rf_vector_copy(destination, v7, (const float *)(v3 + 24));
    }
    rf_vector_rotate_by_matrix3(destination, (float *)(a1 + 72));
    v4 = rf_vector_add((const float *)(a1 + 60), sum_result, destination);
    rf_vector_copy((float *)(*(_DWORD *)(a1 + 5084) + 12 * i), v5, v4);
  }
  return result;
}

