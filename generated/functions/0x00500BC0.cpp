// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500BC0 rf_event_attack_forward
// UNREALRED VERIFIED [event-actions-presentation-continuation-20261027] event_attack forward, vtable0x63E258 slot+4. Resolve ONE attacker from event+0x2B8 via0x4BC680 then common id+0x2C through entity resolver. First authored target resolving as a COMMON object causes0x40B2D0(attacker AI) BEFORE guarded target setter0x40BA80(AI,target id), then stop target scan. Independently if event NAME string+0x1C equals player case-insensitively and global0x681E38 exists, repeat combat helper then request local player entity id, potentially overriding the prior target. Setter admission can reject; this handler does not guarantee mode/target assignment.
char __thiscall rf_event_attack_forward(int *this)
{
  int v1; // eax
  int *v2; // eax
  int v5; // [esp+4h] [ebp-Ch]
  int v6; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  v1 = rf_object_find_by_saved_identifier(*(this + 174));
  if ( v1 )
  {
    v1 = rf_entity_resolve_handle(*(_DWORD *)(v1 + 44));
    v5 = v1;
    if ( v1 )
    {
      for ( i = 0; i < rf_receiver_get_first_dword(this + 167); ++i )
      {
        v2 = (int *)sub_552200(this + 167, i);
        v6 = rf_object_resolve_handle(*v2);
        if ( v6 )
        {
          sub_40B2D0((int *)(v5 + 672));
          sub_40BA80((int *)(v5 + 672), *(_DWORD *)(v6 + 44));
          break;
        }
      }
      LOBYTE(v1) = rf_string_equals_case_insensitive((int)(this + 7), "player");
      if ( (_BYTE)v1 && dword_681E38 )
      {
        sub_40B2D0((int *)(v5 + 672));
        LOBYTE(v1) = sub_40BA80((int *)(v5 + 672), *(_DWORD *)(dword_681E38 + 44));
      }
    }
  }
  return v1;
}

