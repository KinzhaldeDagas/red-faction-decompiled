// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507AD0 rf_ammo_initialize_registry_and_register_string_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Sets global ammo count911480=0, invokes507B00 to parse ammo.tbl, then registers507C80 with atexit and returns registration result. Does not clear existing records/bitmap handles before resetting count, cap rows or detect repeated initialization.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Ammo registry initialization resets911480 count, parses via507B00, registers507C80 cleanup. Startup4F1440 calls this at4F17BB BEFORE weapon50D2E0 at4F17CA; WeaponInfo+24 stores immediate ordinal lookup into that source registry, not a normalized pool string.
int rf_ammo_initialize_registry_and_register_string_cleanup()
{
  unk_911480 = 0;
  rf_ammo_load_table_append_records();
  return atexit(rf_ammo_clear_record_strings);
}

