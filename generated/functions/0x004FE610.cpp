// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE610 rf_event_shield_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_shield forward, vtable0x63E0B4 slot+4. Resolve only entity targets; add signed integer event+0x2B8 to armor float+0x38 then clamp[0,definition+0x48]. Nonzero byte+0x2BC also applies to global local entity0x681E38 if present, with same clamp; duplicate/list-local paths can apply twice. No death check, life modification, common damage call or explicit forwarding in this body.
void __thiscall rf_event_shield_forward(int this)
{
  int *v1; // eax
  int v3; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v3 = rf_entity_resolve_handle(*v1);
    if ( v3 )
    {
      *(float *)(v3 + 56) = (double)*(int *)(this + 696) + *(float *)(v3 + 56);
      rf_float_clamp_in_place((float *)(v3 + 56), 0.0, *(float *)(*(_DWORD *)(v3 + 660) + 72));
    }
  }
  if ( *(_BYTE *)(this + 700) && dword_681E38 )
  {
    *(float *)(dword_681E38 + 56) = (double)*(int *)(this + 696) + *(float *)(dword_681E38 + 56);
    rf_float_clamp_in_place((float *)(dword_681E38 + 56), 0.0, *(float *)(*(_DWORD *)(dword_681E38 + 660) + 72));
  }
}

