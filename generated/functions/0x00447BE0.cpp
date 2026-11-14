// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447BE0 rf_ui_execute_level_load_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Captures whether446190 returned EXACT panel10, then sets loading BYTE182A378=1, stops owned menu music,
// conditionally destroys prior level when LIVE6FC424 mask0x1 is set, samples performance milliseconds(scale1000; unused), and releases unretained model caches. If RFString6FC300 is
// empty, copies6FC308 into it and clears save string6FC2F8. Registers progress callback A for captured panel10, otherwise B, with control-1/inputPoll0; registration immediately
// invokes that callback. Calls no-op447BC0 for panel10, otherwise checks save-string emptiness solely to pass0/1 to no-op447BB0. Executes an EMPTY signed loop index0..<LIVE
// local-player count, then progress-polls(0,0) and ignores sticky-abort AL, then calls448190(capturedPanel10). After these potentially state-mutating delegates, if LIVE local-fpgun
// pointer is nonnull and its unguarded pointer at+4608 has DWORD+8 mask0x40, returns-1 WITHOUT clearing182A378 or finishing the progress callback. Otherwise initializes only the
// first byte of a1024-byte loader-error buffer toNUL and calls477370(level6FC300,save6FC2F8,errorBuffer). EAX0 calls4485C0(capturedPanel10), samples another unused performance
// millisecond value, finishes progress through5951C0(NULL,-1,0), clears182A378 and returns0. Any nonzero loader EAX constructs 'Error loading level: '+6FC31C,
// calls44B4B0(message,1,0,NULL), destroys the temporary string, clears92DE1C ONLY if EXACT1, and unbounded-sprintfs localized88E134 with6FC31C into another1024-byte buffer. If
// loader-error string nonempty, appends newline then its entire NUL-terminated contents with unbounded manual copies. EXACT704E83 byte1 prints '%s\n' and calls nonreturning56F8E0(1);
// otherwise shows localized-title88E138 OK modal, requests panel2/force0, clears182A378, returns-1, and DOES NOT finish the progress callback. C++ unwind only destroys the diagnostic
// temporary; no general loading-flag/callback rollback, local-player count clamp, pointer validity repair or loader-error bounds check.
int rf_ui_execute_level_load_transition()
{
  const char *v1; // eax
  const char *v2; // eax
  char v3; // cl
  char *v5; // [esp+14h] [ebp-868h]
  _BYTE *v6; // [esp+28h] [ebp-854h]
  char *v8; // [esp+30h] [ebp-84Ch]
  char *Format; // [esp+44h] [ebp-838h]
  std::exception *v10; // [esp+48h] [ebp-834h]
  _BYTE v11[7]; // [esp+50h] [ebp-82Ch] BYREF
  char v12; // [esp+57h] [ebp-825h] BYREF
  char Buffer[1024]; // [esp+58h] [ebp-824h] BYREF
  int v14; // [esp+458h] [ebp-424h]
  int v15; // [esp+45Ch] [ebp-420h]
  char v16; // [esp+460h] [ebp-41Ch] BYREF
  _BYTE v17[1034]; // [esp+461h] [ebp-41Bh] BYREF
  char v18; // [esp+86Bh] [ebp-11h]
  int i; // [esp+86Ch] [ebp-10h]
  int v20; // [esp+878h] [ebp-4h]

  v18 = rf_ui_panel_stack_current_id() == 10;
  unk_182A378 = 1;
  rf_main_menu_stop_owned_music();
  if ( (unk_6FC424 & 1) != 0 )
    rf_level_destroy_runtime_resources();
  v14 = rf_performance_clock_elapsed_scaled(1000);
  rf_model_caches_release_unretained();
  if ( rf_string_is_empty(unk_6FC300) )
  {
    rf_string_assign_from_object(unk_6FC300, (int)&unk_6FC308);
    rf_string_assign_from_cstr(unk_6FC2F8, (char *)&byte_633C9E);
  }
  if ( v18 )
  {
    rf_progress_register_or_finish_callback(
      (int (__cdecl *)(_DWORD, _DWORD, _DWORD))rf_level_loading_network_poll_callback_a,
      -1,
      0);
    rf_ui_noop_447bc0();
  }
  else
  {
    rf_progress_register_or_finish_callback(
      (int (__cdecl *)(_DWORD, _DWORD, _DWORD))rf_level_loading_network_poll_callback_b,
      -1,
      0);
    rf_string_is_empty(unk_6FC2F8);
    rf_ui_noop_447bb0();
  }
  for ( i = 0; i < rf_local_player_entry_count; ++i )
    ;
  rf_progress_update_poll_network_and_callback(0, 0);
  sub_448190(v18);
  if ( rf_local_fpgun_player && (*(_DWORD *)(*(_DWORD *)(rf_local_fpgun_player + 4608) + 8) & 0x40) != 0 )
    return -1;
  v16 = 0;
  if ( rf_level_load_and_initialize_world((std::exception *)unk_6FC300, (std::exception *)unk_6FC2F8, &v16) )
  {
    v10 = (std::exception *)rf_string_concat_cstr_object(v11, "Error loading level: ", (const void **)unk_6FC31C);
    v20 = 0;
    v1 = rf_string_object_c_str_or_empty(v10);
    rf_hud_message_enqueue_expand_tokens_and_rearm_head(v1, 1, 0, nullptr);
    v20 = -1;
    rf_string_destroy_buffer(v11);
    if ( unk_92DE1C == 1 )
      unk_92DE1C = 0;
    Format = (char *)unk_88E134;
    v2 = rf_string_object_c_str_or_empty(unk_6FC31C);
    sprintf(Buffer, Format, v2);
    if ( &v17[strlen(&v16)] != v17 )
    {
      v8 = &v12;
      while ( *++v8 )
        ;
      *(_WORD *)v8 = 10;
      v6 = &v17[strlen(&v16)];
      v5 = &v12;
      while ( *++v5 )
        ;
      qmemcpy(v5, &v16, v6 - &v16);
    }
    if ( byte_704E83 == 1 )
    {
      rf_console_printf_unbounded_stack2048("%s\n", Buffer);
      rf_console_wait_for_input_if_enabled_then_exit_one(v3);
    }
    rf_ui_show_ok_modal(unk_88E138, (int)Buffer, 0, 0);
    rf_ui_request_panel_immediate(2, 0);
    unk_182A378 = 0;
    return -1;
  }
  else
  {
    sub_4485C0(v18);
    *(_DWORD *)&v17[1027] = rf_performance_clock_elapsed_scaled(1000);
    v15 = rf_progress_register_or_finish_callback(nullptr, -1, 0);
    unk_182A378 = 0;
    return 0;
  }
}

