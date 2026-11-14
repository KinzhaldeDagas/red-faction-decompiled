// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B790 rf_settings_toggle_autoswitch_explosives
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, gameplay priority/audio call chains, original selector/geometry/constant data and native
// signed/x87/stack/callback ABI): Full native contract:normalize logical-not checkboxBYTE6F7BD8;store LOGICAL-NOT of that newcheckbox into unchecked playerBYTE3905(F41),so stored
// boolean remains inverse of visible enablement. Sound44 when checkboxtrue,45 when false,not based on stored inverse. No player/runtime/input admission,priority reorder,weapon-class
// scan,default mutation or save in this body. Existing interpretation of F41 retained;native callback only stores preference.
int rf_settings_toggle_autoswitch_explosives()
{
  byte_6F7BD8[0] = byte_6F7BD8[0] == 0;
  *(_BYTE *)(rf_local_fpgun_player + 3905) = byte_6F7BD8[0] == 0;
  if ( byte_6F7BD8[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

