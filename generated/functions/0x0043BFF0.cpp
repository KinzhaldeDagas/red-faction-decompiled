// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043BFF0 sub_43BFF0
// UNREALRED VERIFIED [combat-ammo-roles-pickups-20261111]: Exact4014F0 selector entry: player commonflag =>false. Otherwise requires actualMP runtime ORsplitscreen, then humanoid. OrdinarySP nativegrant never enters literal3 initialization/selection throughthiscallback. Do not substitute alternate weapon tablechoice for mode/authority or inferNPC solely fromcontrolrole.
bool __cdecl sub_43BFF0(int a1)
{
  if ( rf_object_has_player_flag(a1) )
    return 0;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    return rf_entity_has_humanoid_flag(a1);
  return 0;
}

