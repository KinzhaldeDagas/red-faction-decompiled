// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004426C0 rf_play_end_movie_then_request_credits_panel
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): No arguments. Set BYTE6EDD38=1 FIRST. Then568A00 with raw caller slots(1,-1), stop/release all gamesound
// voice slots568650, synchronously invoke58E020("end.bik"), then453B20("call_credits") regardless of movie/backend success. Exact case-insensitive call_credits branch in453B20
// requests immediate panel23 with force0 through446100; it does not enter that helper's other-string blackout/copy branch. Audio wrapper consumes its own declared byte argument;
// extra caller DWORD-1 remains caller-owned and is cleaned with the first slot. No own backend/window/file/pause/player admission, resume, latch clear or rollback. Returns raw final
// panel-request EAX, not movie success; earlier latch/audio mutations survive movie failure or panel-request rejection.
int rf_play_end_movie_then_request_credits_panel()
{
  unk_6EDD38 = 1;
  rf_sound_backend_set_paused(1);
  rf_gamesound_stop_all_voice_slots();
  rf_movie_play_bink_blocking("end.bik");
  return rf_frontend_request_credits_or_endgame_blackout("call_credits");
}

