// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC620 rf_event_holster_player_weapon_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type65 Holster_Player_Weapon. If global player entity exists, OR entity+0x810 bit0x800 only. Does not write AI-block holster bit+0x530/0x200, stop firing directly, or request presentation/weapon switch in this body.
int rf_event_holster_player_weapon_apply()
{
  int result; // eax

  if ( dword_681E38 )
  {
    result = dword_681E38;
    *(_DWORD *)(dword_681E38 + 2064) |= 0x800u;
  }
  return result;
}

