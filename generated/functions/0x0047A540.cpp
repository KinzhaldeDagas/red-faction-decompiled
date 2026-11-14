// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A540 rf_level_browser_request_selected_level
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, liquid transition lifecycle, native x87 unordered comparisons, stable pointer erase, static runtime ownership and level-browser flow): 
// Cdecl no arguments. Reads selected entry from text list6FC978. NULL selection plays sounds.tbl event2 with arguments(2,0,0.0,1.0) and returns that delegate. Otherwise uses entry
// Cstring48 and unbounded last-dot suffix replacement to build .rfl path. Constructs TWO8-byte by-value RFStrings: first logical level=path, second save=empty Cstring63878D. Calls
// transition_assign_level_and_save_strings, which copies globals and destroys both argument strings; caller cleans16 stack bytes.
// If multiplayer mode byte==1 and authority byte==0 calls multiplayer_runtime_teardown with NO native arguments. Clears level-state cache, then requests immediate panel(5,0),
// returning delegate EAX. No direct world deserialization or independent path/capacity validation.
int rf_level_browser_request_selected_level()
{
  int v1[2]; // [esp-8h] [ebp-240h] BYREF
  int v2[5]; // [esp+0h] [ebp-238h] BYREF
  _DWORD *v3; // [esp+14h] [ebp-224h]
  int *v4; // [esp+18h] [ebp-220h]
  void *v5; // [esp+1Ch] [ebp-21Ch]
  int selected_entry; // [esp+20h] [ebp-218h]
  char Source[516]; // [esp+24h] [ebp-214h] BYREF
  int v8; // [esp+234h] [ebp-4h]

  selected_entry = rf_text_list_get_selected_entry(unk_6FC978);
  if ( !selected_entry )
    return rf_gamesound_play_event(2, 0, 0.0, 1.0);
  rf_path_replace_last_dot_suffix_unbounded(Source, *(char **)(selected_entry + 48), ".rfl");
  v5 = v2;
  v3 = rf_string_construct_from_cstr(v2, (char *)&byte_63878D);
  v2[4] = (int)v3;
  v8 = 0;
  v4 = v1;
  v2[3] = (int)rf_string_construct_from_cstr(v1, Source);
  v8 = -1;
  rf_level_transition_assign_level_and_save_strings(v1[0], (char *)v1[1], v2[0], (char *)v2[1]);
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
    rf_multiplayer_runtime_teardown();
  rf_level_state_cache_clear();
  return rf_ui_request_panel_immediate(5, 0);
}

