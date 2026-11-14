// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00474210 rf_item_apply_queued_model_filename
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): cdecl(object,filename). If filename already in V3C cache, skips direct model-handle load and proceeds with current object+128 unchanged
// at that point. Otherwise loads563EC0(filename,1,-1), writes returned handle to object+128 even whenNULL; NULL marks object for deferred deletion and returns, leaving queued bit
// unchanged. Success/cache path constructs owned temporary8-byte RFString from filename, calls bind_model_filename_by_kind(object,tempCstr,1), clears ONLY bit0 of objectDWORD+700,
// destroys temporary including SEH cleanup. No old-handle release or source/object/null guard in this wrapper, and no binding-result check before clearing bit.
void __cdecl rf_item_apply_queued_model_filename(int a1, char *String2)
{
  char *v2; // eax
  _DWORD v3[2]; // [esp+4h] [ebp-18h] BYREF
  int v4; // [esp+Ch] [ebp-10h]
  int v5; // [esp+18h] [ebp-4h]

  if ( rf_v3c_cache_contains_filename_adapter(String2)
    || (*(_DWORD *)(a1 + 128) = rf_model_handle_load_v3m_mode1(String2, 1, (void *)0xFFFFFFFF)) != 0 )
  {
    v4 = a1;
    rf_string_construct_from_cstr(v3, String2);
    v5 = 0;
    v2 = (char *)rf_string_object_c_str_or_empty(v3);
    rf_object_bind_model_filename_by_kind(a1, v2, 1);
    *(_DWORD *)(v4 + 700) &= ~1u;
    v5 = -1;
    rf_string_destroy_buffer(v3);
  }
  else
  {
    rf_object_mark_for_deferred_delete(a1);
  }
}

