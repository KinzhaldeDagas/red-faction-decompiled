// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBC40 rf_event_strip_player_weapons_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type56 Strip_Player_Weapons. If global player entity0x681E38 exists, call0x43C040(entity), then0x4E25C0 (matched empty body). No target-list traversal, immediate weapon switch, or item-drop spawn in this leaf.
void rf_event_strip_player_weapons_apply()
{
  if ( dword_681E38 )
  {
    rf_entity_clear_weapon_inventory(dword_681E38);
    rf_player_weapon_reset_noop();
  }
}

