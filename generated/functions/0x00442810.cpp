// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00442810 rf_pause_game_input_audio_and_stop_primary_weapon
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Call569310 owned-music resource getter and store its returned pointer/residue in DWORD6E6AC0
// FIRST. If primary entity global681E38 nonNULL, pass its full handle44 and selected weapon676 to422A40 stop firing; primary global is re-read for those two fields, with no
// selected-index validation here. Always disable mouse centering request, set centering-disabled argument1, call568A00 with raw slots(1,-1), then448B40(lockBYTE0), forwarding final
// EAX. Pause helper may reject runtime EXACT1 or already-paused EXACT1 AFTER music cache, weapon stop, mouse and audio side effects have occurred; wrapper does not gate or undo them.
// No own player/authority/backend/readiness guard, menu-music fade, key reset, status normalization or rollback.
int rf_pause_game_input_audio_and_stop_primary_weapon()
{
  unk_6E6AC0 = rf_music_owned_get_resource_record();
  if ( dword_681E38 )
    rf_entity_stop_weapon_firing(*(_DWORD *)(dword_681E38 + 44), *(_DWORD *)(dword_681E38 + 676));
  rf_mouse_disable_centering_request();
  rf_mouse_set_centering_disabled(1);
  rf_sound_backend_set_paused(1);
  return rf_game_pause_unless_multiplayer_or_already_paused(0);
}

