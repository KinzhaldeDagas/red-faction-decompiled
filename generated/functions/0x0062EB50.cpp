// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EB50 rf_glare_static_sentinel_destroy_members_atexit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): No-argument atexit adapter. Calls derived/base member destructor0x48C050 with static glare sentinel0x680AE8. Only inherited member cleanup; does not iterate glare runtime records or release definition bitmaps/names, and does not free static storage.
void rf_glare_static_sentinel_destroy_members_atexit()
{
  rf_common_derived_destroy_base_members(&unk_680AE8);
}

