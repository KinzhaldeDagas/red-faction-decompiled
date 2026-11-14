// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004355A0 sub_4355A0
// UNREALRED VERIFIED [combat-panic-movement-20261111]: This resets native movement mode, not a canonical animation-state tag.435440 admits authored walk bit1. Non-walk calls4344D0(1) only. Walk and common810 bit400:4361B0 must succeed before later writes; completed clearance rejection leaves all later movement-reset stores untouched. Successful admitted branch clears Entity+13EC region-related pointer, calls4344D0(1), stores445780(gameplayclass Movemode+30) at858 including native null, stores global7BEB0C matrix sentinel at85C, zeros Entity+148 vertical velocity.40B1A0 ignores this helper return and still writes mode17/secondary1/route. Do not infer an animation name from this registry.
char __cdecl sub_4355A0(int a1)
{
  char result; // al
  char *v2; // eax

  if ( !rf_entity_class_flags724_has_mask1(a1) )
    return (unsigned __int8)sub_4344D0(a1, 1);
  if ( !rf_entity_is_crouched_state810(a1) || (result = rf_entity_try_apply_standing_shape_centers(a1)) != 0 )
  {
    *(_DWORD *)(a1 + 5100) = 0;
    sub_4344D0(a1, 1);
    v2 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 48));
    *(_DWORD *)(a1 + 2136) = sub_445780(v2);
    *(_DWORD *)(a1 + 2140) = &unk_7BEB0C;
    *(float *)(a1 + 328) = 0.0;
    return a1;
  }
  return result;
}

