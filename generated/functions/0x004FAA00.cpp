// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAA00 rf_event_make_invulnerable_build_from_duration
// UNREALRED VERIFIED [mission-protection-20261020] Builds type24 Make_Invulnerable: generic float0 is stored at+0x2B8 and protection replicator+0x2BC starts reset/unarmed. Ordinary event Delay+0x294 and this duration are separate timers.
int __cdecl rf_event_make_invulnerable_build_from_duration(float *a1, float a2)
{
  int v3; // [esp+0h] [ebp-4h]

  v3 = rf_mission_event_create_at_position(a1, 0x18u);
  if ( v3 )
  {
    *(float *)(v3 + 696) = a2;
    rf_replicator_reset((_DWORD *)(v3 + 700));
  }
  return v3;
}

