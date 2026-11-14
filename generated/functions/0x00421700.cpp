// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00421700 rf_entity_contact_with_entity_allows_velocity_response
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(self,other),booleanAL. Use-vehicle self AND predicate43BFA0(other) ->true immediately. Otherwise use-vehicle self AND ORDERED other scalar152<30 ->returnsfalse,first calls437390(other) if self velocity324 ORangular336 squared length ORDERED>0. Otherwise self class660 DWORD1828 bit0x8000 AND current material464==3 ->alwaysfalse;calls437390(other) when velocity324 ORangular336 squared ORDERED>0.5,or self class0x200 predicate AND runtime-enabled438090(self,-1). All other cases return NOT other player-flag. No own NULL/class/other validity guard. Returnfalse does not imply no side effects;437390 can be invoked before rejecting velocity response. Relies on delegated predicates;does not apply an impulse
// itself.
bool __cdecl rf_entity_contact_with_entity_allows_velocity_response(int a1, int a2)
{
  if ( rf_object_is_use_vehicle((_DWORD *)a1) && rf_entity_class_flag2000000_positive_scalar56(a2) )
    return 1;
  if ( rf_object_is_use_vehicle((_DWORD *)a1) && *(float *)(a2 + 152) < 30.0 )
  {
    if ( rf_vector_length_squared((float *)(a1 + 324)) > 0.0 || rf_vector_length_squared((float *)(a1 + 336)) > 0.0 )
      rf_entity_apply_type9_damage_and_play_sound(a2);
    return 0;
  }
  else if ( (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1828) & 0x8000) != 0 && *(_DWORD *)(a1 + 464) == 3 )
  {
    if ( rf_vector_length_squared((float *)(a1 + 324)) > 0.5
      || rf_vector_length_squared((float *)(a1 + 336)) > 0.5
      || rf_entity_class_has_contact_geomod_flag200(a1) && rf_entity_runtime_enabled_or_resolved_attachment(a1, -1) )
    {
      rf_entity_apply_type9_damage_and_play_sound(a2);
    }
    return 0;
  }
  else
  {
    return !rf_object_has_player_flag(a2);
  }
}

