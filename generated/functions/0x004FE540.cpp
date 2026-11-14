// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FE540 rf_event_heal_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_heal forward, vtable0x63E0A0 slot+4. Iterate target identifiers and resolve COMMON objects, then apply signed integer event+0x2B8 converted to float through0x4BC750. Optional nonzero byte+0x2BC and non-null global0x681E38 applies same helper again to that local entity, then clamps its life+0x34 to[0,definition+0x44]. Ordinary targets receive helper upper clamp only, permitting negative life from negative healing. Local entity included in target list can receive both contributions; no deduplication, death check, damage dispatcher, or explicit forwarding here.
void __thiscall rf_event_heal_forward(int this)
{
  int *v1; // eax
  float v2; // [esp+4h] [ebp-10h]
  float v3; // [esp+4h] [ebp-10h]
  int i; // [esp+Ch] [ebp-8h]
  int v6; // [esp+10h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v6 = rf_object_resolve_handle(*v1);
    if ( v6 )
    {
      v2 = (float)*(int *)(this + 696);
      rf_object_add_life_upper_clamped(v6, v2);
    }
  }
  if ( *(_BYTE *)(this + 700) && dword_681E38 )
  {
    v3 = (float)*(int *)(this + 696);
    rf_object_add_life_upper_clamped(dword_681E38, v3);
    rf_float_clamp_in_place((float *)(dword_681E38 + 52), 0.0, *(float *)(*(_DWORD *)(dword_681E38 + 660) + 68));
  }
}

