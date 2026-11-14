// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005007E0 rf_event_make_invulnerable_apply_reverse
// UNREALRED VERIFIED [mission-protection-20261020] Reverse Make_Invulnerable clears common bit4 on linked objects and special name player. Does NOT reset/cancel +0x2BC timer. Does not stack or restore prior protection owners. Generic reverse propagation follows, with normal mover suppression.
char __thiscall rf_event_make_invulnerable_apply_reverse(_DWORD *this)
{
  int *v1; // eax
  unsigned int v2; // eax
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 167); ++i )
  {
    v1 = (int *)sub_552200(this + 167, i);
    v5 = rf_object_resolve_handle(*v1);
    if ( v5 )
      *(_DWORD *)(v5 + 124) &= ~4u;
  }
  LOBYTE(v2) = rf_string_equals_case_insensitive((int)(this + 7), "player");
  if ( (_BYTE)v2 && dword_681E38 )
  {
    v2 = *(_DWORD *)(dword_681E38 + 124) & 0xFFFFFFFB;
    *(_DWORD *)(dword_681E38 + 124) = v2;
  }
  return v2;
}

