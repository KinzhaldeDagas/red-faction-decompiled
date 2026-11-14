// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485A30 rf_material_system_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl noargs. Registers rf_material_system_shutdown with atexit, releases ONLY bitmap-prefix vector backing storage via rf_pointer_array_release_storage, then calls table loader
// unconditionally. If sound-ready helper AL is nonzero, calls material-pair sound builder; otherwise skips it. Does not delete existing pointed prefix objects before releasing that
// storage, clear custom sets/pair vectors, or reset physics records here. Repeated initialization therefore is not a complete teardown/reload transaction; atexit status is ignored.
void rf_material_system_init()
{
  atexit(rf_material_system_shutdown);
  rf_pointer_array_release_storage((void **)rf_material_bitmap_prefix_registry);
  rf_material_tables_load();
  if ( rf_sound_system_ready_get() )
    rf_material_hit_sounds_build();
}

