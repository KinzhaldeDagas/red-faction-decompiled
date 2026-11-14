// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561C30 rf_model_system_release_character_and_asset_caches
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Calls character-system instance/resource release, then5B8140 cache release, then5B2000 cache release in exact order. No retry, status handling or new allocation. Last two drain their pointer caches and set counts0; this dispatcher has no arguments and no semantic return.
void __cdecl rf_model_system_release_character_and_asset_caches()
{
  rf_character_system_release_instances_and_resources();
  rf_v3c_asset_cache_release_all();
  rf_asset_cache1D6CF28_release_all();
}

