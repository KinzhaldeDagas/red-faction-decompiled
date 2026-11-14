// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A410 rf_geomod_cutter_registry_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, queue/history ownership, smoke lifetime, cutter registry, native region constraints and corrected stack/AL ABI): 
// Cdecl process init. Sets registry count6EDEDC=0 without prior cleanup; calls find_or_append in exact order Holey01.v3d,bit_driller_double.v3d,bit_driller_single.v3d,Holey_APC.v3d.
// Ordinary fresh indices0,1,2,3; helper caches returned embedded solid pointer even if NULL. Registers cutter cleanup44A370 with atexit and returns that status. No file loading,
// geometry duplication, name canonicalization or validation of returned solids in this wrapper. Repeated init can overwrite previously owned entries without freeing their solids
// first.
int rf_geomod_cutter_registry_init()
{
  dword_6EDEDC = 0;
  rf_geomod_cutter_registry_find_or_append("Holey01.v3d");
  rf_geomod_cutter_registry_find_or_append("bit_driller_double.v3d");
  rf_geomod_cutter_registry_find_or_append("bit_driller_single.v3d");
  rf_geomod_cutter_registry_find_or_append("Holey_APC.v3d");
  return atexit(rf_geomod_cutter_registry_exit_cleanup);
}

