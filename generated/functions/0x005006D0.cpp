// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005006D0 rf_event_make_invulnerable_apply_forward
// UNREALRED VERIFIED [mission-protection-20261020] Make_Invulnerable forward sets common+0x7C bit4 on each ordered resolved UID. Then positive float+0x2B8 arms +0x2BC with trunc(double(seconds)*1000+0.5), except name player (case-insensitive) already protected. The player test runs AFTER linked flags are set; a linked player suppresses its own timer arm. Finally name player sets local player bit4. Repeated ordinary activations rearm; already-protected named player does not. Ordinary base forwarding still follows this handler.
char __thiscall rf_event_make_invulnerable_apply_forward(int this)
{
  int *v1; // eax
  int v2; // eax
  int v5; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v5 = rf_object_resolve_handle(*v1);
    if ( v5 )
      *(_DWORD *)(v5 + 124) |= 4u;
  }
  if ( *(float *)(this + 696) > 0.0
    && (!rf_string_equals_case_insensitive(this + 28, "player") || (*(_DWORD *)(dword_681E38 + 124) & 4) == 0) )
  {
    rf_replicator_arm_milliseconds((int *)(this + 700), (int)(*(float *)(this + 696) * 1000.0 + 0.5));
  }
  LOBYTE(v2) = rf_string_equals_case_insensitive(this + 28, "player");
  if ( (_BYTE)v2 && dword_681E38 )
  {
    v2 = *(_DWORD *)(dword_681E38 + 124) | 4;
    *(_DWORD *)(dword_681E38 + 124) = v2;
  }
  return v2;
}

