// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045EF90 rf_multiplayer_rules_toggle_weapons_stay
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Noarg. Logical-NOT raw checkboxBYTE6F4060:zero->1,ANY nonzero->0;store normalized result before sound. New1 plays44,new0 plays45,with(0,0.0,1.0);return sound residue.
// Original builder callback/text binding verifies Weapons stay identity (runtime label localized). No own state9/mode/runtime/authority guard,registry/network write or gameplay flag
// mutation. Separate apply45F680 consumes ANY nonzero byte and maps gameFlags bits10,so toggling does not itself apply server rules.
int rf_multiplayer_rules_toggle_weapons_stay()
{
  byte_6F4060[0] = byte_6F4060[0] == 0;
  if ( byte_6F4060[0] )
    return rf_gamesound_play_event(44, 0, 0.0, 1.0);
  else
    return rf_gamesound_play_event(45, 0, 0.0, 1.0);
}

