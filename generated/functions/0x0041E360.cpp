// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041E360 rf_corpse_rebind_cached_character_model
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl(corpse,filename). Calls character-cache filename predicate FIRST. Cache hit OR NULL corpse enters binding branch; null is NOT safely rejected and is subsequently passed/dereferenced. Nonnull corpse plus cache miss marks deletion; if global local entity681E38 has field1884 equal corpse handle44, resets1884=-1 and arms its timer1300 for500ms. Binding branch constructs temporary RFString, invokes4BC000(corpse,name,2) ignoring bind result, resets cyclic model; signed death action696>=0 starts held action, advances duration then0.3, resizes sphere collection count to model named-sphere count via41F1F0 and refreshes geometry. Resize0 frees backing but leaves capacity/base
// stale, as documented separately. Destroys temporary string. No cache load fallback, pointer/filename/action/model success guard or rollback.
void __cdecl rf_corpse_rebind_cached_character_model(int a1, char *Source)
{
  char *v2; // eax
  float v3; // [esp+18h] [ebp-20h]
  int v4; // [esp+1Ch] [ebp-1Ch]
  _DWORD v5[2]; // [esp+20h] [ebp-18h] BYREF
  int v6; // [esp+28h] [ebp-10h]
  int v7; // [esp+34h] [ebp-4h]

  if ( rf_character_cache_contains_filename_adapter((int)Source) || !a1 )
  {
    v6 = a1;
    rf_string_construct_from_cstr(v5, Source);
    v7 = 0;
    v2 = (char *)rf_string_object_c_str_or_empty(v5);
    rf_object_bind_model_filename_by_kind(a1, v2, 2);
    rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(v6 + 128));
    if ( *(int *)(v6 + 696) > -1 )
    {
      rf_vfx_start_instance(*(int **)(v6 + 128), *(_DWORD *)(v6 + 696), 1.0, 1);
      v3 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(v6 + 128), *(_DWORD *)(v6 + 696));
      rf_vfx_update_instance(*(int **)(v6 + 128), v3, 0, 0, 0, 1);
      rf_vfx_update_instance(*(int **)(v6 + 128), 0.30000001, 0, 0, 0, 1);
      v4 = rf_model_handle_named_sphere_count_adapter(*(_DWORD **)(v6 + 128));
      rf_array24_set_count_reallocate_unchecked(v6 + 388, v4);
      rf_corpse_refresh_vmesh_geometry(v6);
    }
    v7 = -1;
    rf_string_destroy_buffer(v5);
  }
  else
  {
    rf_object_mark_for_deferred_delete(a1);
    if ( dword_681E38 )
    {
      if ( *(_DWORD *)(dword_681E38 + 1884) == *(_DWORD *)(a1 + 44) )
      {
        *(_DWORD *)(dword_681E38 + 1884) = -1;
        rf_replicator_arm_milliseconds((int *)(dword_681E38 + 1300), 500);
      }
    }
  }
}

