// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500890 rf_event_make_invulnerable_update_expiry
// UNREALRED VERIFIED [mission-protection-20261020] Per-frame Make_Invulnerable update tests +0x2BC deadline. Once elapsed, clears linked common bit4 and named-player bit4, but DOES NOT reset deadline. It therefore clears again every later frame until rearmed or timer wrap comparison changes. It does not invoke generic target forwarding on expiry; overlapping event timers can clear protection set by another event.
char __thiscall rf_event_make_invulnerable_update_expiry(int *this)
{
  char result; // al
  int *v2; // eax
  int v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = rf_replicator_has_elapsed(this + 175);
  if ( result == 1 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword(this + 167); ++i )
    {
      v2 = (int *)sub_552200(this + 167, i);
      v4 = rf_object_resolve_handle(*v2);
      if ( v4 )
        *(_DWORD *)(v4 + 124) &= ~4u;
    }
    result = rf_string_equals_case_insensitive((int)(this + 7), "player");
    if ( result )
    {
      if ( dword_681E38 )
      {
        result = dword_681E38;
        *(_DWORD *)(dword_681E38 + 124) &= ~4u;
      }
    }
  }
  return result;
}

