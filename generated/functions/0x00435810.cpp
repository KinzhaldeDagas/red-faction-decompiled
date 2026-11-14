// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435810 rf_entity_select_movement4_or7
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(entity), path-dependent EAX/AL. Require class flags1828mask0x500 ANYnonzero; false returnsAL0 predicate
// residue. Current movement-kind4/7 predicate ANYnonzero returns early with its zero-extended AL (normally1). Otherwise class contact-geomod mask0x400 ANYnonzero requests speed1
// through4344D0 then descriptor445740(7). Zero mask path: crouch810 ANYnonzero invokes4361B0 but IGNORES failed uncrouch result, then ALWAYS requests speed0 and descriptor445740(4).
// Both admitted branches store descriptor2136 and ADDRESS7BEB0C at2140; EAX becomes original ENTITY POINTER, not status. No output/NULL/health/authority guard, timer,
// descriptor-validation or rollback; shared speed transaction may override requested mode.
char __cdecl rf_entity_select_movement4_or7(int a1)
{
  char result; // al

  result = rf_entity_class_flags724_has_mask500(a1);
  if ( result )
  {
    result = rf_entity_movement_is_index4_or7(a1);
    if ( !result )
    {
      if ( rf_entity_class_has_contact_geomod_flag400(a1) )
      {
        sub_4344D0(a1, 1);
        *(_DWORD *)(a1 + 2136) = sub_445740(7u);
      }
      else
      {
        if ( rf_entity_is_crouched_state810(a1) )
          rf_entity_try_apply_standing_shape_centers(a1);
        sub_4344D0(a1, 0);
        *(_DWORD *)(a1 + 2136) = sub_445740(4u);
      }
      *(_DWORD *)(a1 + 2140) = &unk_7BEB0C;
      return a1;
    }
  }
  return result;
}

