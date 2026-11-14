// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A8330 rf_multiplayer_reset_update_handle_cache
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): No arguments. Writes EXACT1024 DWORDs at7B1538+4*i to-1, then arms deadline7B2538 with offset0. Does not clear log handle7B1530, initialize
// player/motion buffers, send a packet or guarantee return status.
int rf_multiplayer_reset_update_handle_cache()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 1024; ++i )
    unk_7B1538[i] = -1;
  return rf_clock_deadline_set_wrapped_offset(&dword_7B2538, 0);
}

