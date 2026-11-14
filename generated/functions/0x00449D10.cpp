// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00449D10 rf_geomod_network_history_count_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl noargs; returns DWORD rf_geomod_network_history_count verbatim in EAX. No execution-queue scan, pending-node count, saved-admission count or reset. GeoMod admission uses this
// accessor only for exact multiplayer mode1/authority1 server limit, independently of per-level saved-record cap128.
int rf_geomod_network_history_count_get()
{
  return rf_geomod_network_history_count;
}

