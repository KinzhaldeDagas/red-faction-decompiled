// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472880 rf_item_system_initialize
// UNREALRED VERIFIED [event-item-dispatch-20261028]: For all96 fixed definitions clears callback/context dwords+72/+76, arms global timer0x6FAF30 at0ms, clears definition count0x6F9124, sets item-list head/tail to sentinel0x6FAF38. Parses items.tbl then registers named pickup callbacks for Suit Repair, Miner Envirosuit, Medical Kit, First Aid Kit, and five Multi powerup classes. Registers0x472F80 at exit. Does not zero every definition field here.
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Clears ONLY callback/context dwords+48/+4C of all96 physical80byte records, arms item timer0ms, resets count and linked-list sentinels, then4729C0 parses. Afterwards472830 binds each named health/armor/powerup handler through FIRST class-name lookup473770. Later duplicate class rows retain their prior zero handler and execute default pickup dispatch. This is not a per-row name-based handler decision.
int rf_item_system_initialize()
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 96; ++i )
  {
    *((_DWORD *)&unk_6F9130 + 20 * i + 18) = 0;
    *((_DWORD *)&unk_6F9130 + 20 * i + 19) = 0;
  }
  rf_replicator_arm_milliseconds((int *)&unk_6FAF30, 0);
  unk_6F9124 = 0;
  unk_6FB1C4 = &unk_6FAF38;
  unk_6FB1C8 = &unk_6FAF38;
  rf_item_definitions_load_table();
  rf_item_definition_register_pickup_handler("Suit Repair", (int)rf_item_pickup_suit_repair, 0);
  rf_item_definition_register_pickup_handler("Miner Envirosuit", (int)rf_item_pickup_miner_envirosuit, 0);
  rf_item_definition_register_pickup_handler("Medical Kit", (int)rf_item_pickup_medical_kit, 0);
  rf_item_definition_register_pickup_handler("First Aid Kit", (int)rf_item_pickup_medical_kit, 0);
  rf_item_definition_register_pickup_handler("Multi Invulnerability", (int)rf_item_pickup_multiplayer_powerup, 0);
  rf_item_definition_register_pickup_handler("Multi Damage Amplifier", (int)rf_item_pickup_multiplayer_powerup, 0);
  rf_item_definition_register_pickup_handler("Multi Super Armor", (int)rf_item_pickup_multiplayer_powerup, 0);
  rf_item_definition_register_pickup_handler("Multi Super Health", (int)rf_item_pickup_multiplayer_powerup, 0);
  rf_item_definition_register_pickup_handler("Multi Nanoshield", (int)rf_item_pickup_multiplayer_powerup, 0);
  return atexit(rf_item_definition_clear_names_at_exit);
}

