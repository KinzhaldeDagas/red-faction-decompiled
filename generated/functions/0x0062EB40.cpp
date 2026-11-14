// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EB40 rf_physical_debris_static_sentinel_destroy_members_atexit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): No-argument atexit adapter. Loads physical-debris static sentinel as ECX and calls derived/base member destructor0x48C050; no list walk, count reset, owned-solid cleanup or outer allocation free. Distinct from no-op gameplay shutdown hook0x4182A0 and per-object debris cleanup0x4190E0.
void rf_physical_debris_static_sentinel_destroy_members_atexit()
{
  rf_common_derived_destroy_base_members(&rf_physical_debris_list_sentinel);
}

