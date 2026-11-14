// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446820 sub_446820
// UNREALRED VERIFIED [combat-speech-providers-20261111]: Loader order: when native sound-ready is true call446850 sounds.tbl at44682F, then446A10 Foley at446834. The ready=false branch skips base sounds but still loads Foley. A host backend with no audio device must preserve completed duration0/play-1 separately from source/resource unavailability; it must not silently remap the base enum registry.
int sub_446820()
{
  if ( rf_sound_system_ready_get() )
    rf_gamesound_load_table();
  rf_foley_load_table_append_sets();
  rf_reserved_noop_567F50();
  return atexit(rf_foley_free_variant_arrays);
}

