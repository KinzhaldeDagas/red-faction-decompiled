// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435500 sub_435500
// UNREALRED VERIFIED [ai-goto-event-20260826]: Goto calls this presentation/action helper only after destination installation returns success and event byte +0x2B9 is clear. The broader class/action-token meaning remains unproven and is deliberately not named.
float *__cdecl sub_435500(int a1, char a2)
{
  if ( !rf_entity_class_flags724_has_mask1(a1) )
    return sub_4344D0(a1, 0);
  if ( a2 )
  {
    *(_DWORD *)(a1 + 2064) |= 0x400u;
  }
  else if ( rf_entity_is_crouched_state810(a1) )
  {
    rf_entity_try_apply_standing_shape_centers(a1);
  }
  sub_4344D0(a1, 0);
  *(_DWORD *)(a1 + 2136) = sub_445740(1u);
  *(_DWORD *)(a1 + 2140) = &unk_7BEB0C;
  *(float *)(a1 + 328) = 0.0;
  return (float *)a1;
}

