// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423090 rf_entity_compose_tag_or_retained_firing_transform
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl FIVE slots(entity,outPoint3,outMatrix9,tagIndex,primaryBYTE), output-transform procedure; no canonical EAX status. Any nonzero lowBYTE
// primary selects inline tag array at class(entity+660)+444; zero selects+456. Read count via486DE0; SIGNED tagIndex<count admits lookup at array+4+4*tagIndex, with NO tagIndex>=0
// check. Default tag=-1; only tag EXACT-1 or entity model+128==0 selects fallback. Other negative tags pass composition. Valid tag/model:5651D0(model,tag,entity common
// matrix+72,common position+60,outMatrix,outPoint), ignoring result/status. Then class DWORD+1832 mask20 AND current AI target full handle entity+1376 resolving as COMMON object:
// construct orientation from safe-normalized(target common position+60-outPoint), with559300 unit-X zero fallback. Otherwise overwrite composed orientation with entity retained
// matrix+2016. BOTH paths then423260(entity,outPoint,outMatrix), so class mask20 is not a global target-facing veto; that delegate re-resolves target and can replace orientation
// again. Fallback first writes outMatrix=retained2016, then outPoint=retained2004+FLOAT0.30000001192092896*retained forward2040, then ALSO423260 with all THREE slots. Point stays
// composed/fallback while orientation may be overwritten or retained; no own output validation, bound cap, normalization of source pose or rollback. Partial delegate failure can
// leave earlier writes visible.
void __cdecl rf_entity_compose_tag_or_retained_firing_transform(
        int entity,
        float *rhs,
        float *out_orientation,
        int a4,
        char a5)
{
  float *v5; // eax
  float scaled_result[3]; // [esp+4h] [ebp-2Ch] BYREF
  float copy_result[3]; // [esp+10h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+1Ch] [ebp-14h] BYREF
  int v9; // [esp+28h] [ebp-8h]
  int v10; // [esp+2Ch] [ebp-4h]

  v10 = -1;
  if ( a5 )
  {
    if ( a4 < rf_receiver_get_first_dword((void *)(*(_DWORD *)(entity + 660) + 444)) )
      v10 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(*(_DWORD *)(entity + 660) + 444), a4);
  }
  else if ( a4 < rf_receiver_get_first_dword((void *)(*(_DWORD *)(entity + 660) + 456)) )
  {
    v10 = *(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(*(_DWORD *)(entity + 660) + 456), a4);
  }
  if ( v10 == -1 || !*(_DWORD *)(entity + 128) )
  {
    rf_matrix3_copy(out_orientation, (const float *)(entity + 2016));
    rf_vector_copy(rhs, copy_result, (const float *)(entity + 2004));
    v5 = rf_vector_multiply_scalar((const float *)(entity + 2040), scaled_result, 0.30000001);
    rf_vector_accumulate(rhs, v5);
    rf_entity_adjust_firing_orientation_toward_target(entity, rhs, out_orientation);
  }
  else
  {
    rf_vmesh_compose_prop_world_transform(
      *(_DWORD *)(entity + 128),
      v10,
      (float *)(entity + 72),
      entity + 60,
      (int)out_orientation,
      rhs);
    if ( (*(_DWORD *)(*(_DWORD *)(entity + 660) + 1832) & 0x20) != 0
      && (v9 = rf_object_resolve_handle(*(_DWORD *)(entity + 1376))) != 0 )
    {
      rf_vector_subtract((const float *)(v9 + 60), out_vector, rhs);
      rf_vector_normalize(out_vector);
      rf_orientation_matrix_from_normalized_direction(out_orientation, out_vector);
      rf_entity_adjust_firing_orientation_toward_target(entity, rhs, out_orientation);
    }
    else
    {
      rf_matrix3_copy(out_orientation, (const float *)(entity + 2016));
      rf_entity_adjust_firing_orientation_toward_target(entity, rhs, out_orientation);
    }
  }
}

