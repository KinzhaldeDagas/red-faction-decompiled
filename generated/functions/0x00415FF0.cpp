// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415FF0 rf_clutter_bind_cached_static_model_or_mark_missing
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl(object,filename),void,temporaryRFString/SEHcleanup. Constructs temporary from input. Only if current V3C-cache filename-presence helper succeeds,binds commonmodel via4BC000(object,filename,kind1 staticV3M). No own old-model destruction or class660/664 changes before/after binding. Cachemiss SKIPS bind and retains oldmodel128. Regardlesscachepath,if finalmodel128==0 marksobject for deferred delete;cachemiss with existingmodel does NOT markdelete. Binder failure can replace oldmodel with0 and trigger deletion;does not roll back. No own file-open/reload/cache-retention promise,NULL/filename-length check or physics-shape rebuild.
void __cdecl rf_clutter_bind_cached_static_model_or_mark_missing(int a1, char *String2)
{
  char *v2; // eax
  _DWORD v3[2]; // [esp+4h] [ebp-14h] BYREF
  int v4; // [esp+14h] [ebp-4h]

  rf_string_construct_from_cstr(v3, String2);
  v4 = 0;
  if ( rf_v3c_cache_contains_filename_adapter(String2) )
  {
    v2 = (char *)rf_string_object_c_str_or_empty(v3);
    rf_object_bind_model_filename_by_kind(a1, v2, 1);
  }
  if ( !*(_DWORD *)(a1 + 128) )
    rf_object_mark_for_deferred_delete(a1);
  v4 = -1;
  rf_string_destroy_buffer(v3);
}

