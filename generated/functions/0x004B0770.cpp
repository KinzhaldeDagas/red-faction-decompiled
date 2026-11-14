// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0770 rf_multiplayer_begin_authority_session
// UNREALRED VERIFIED [local-multiplayer-20261028] Marks server authority and host startup flag, then0x4494C0 prepares state and issues immediate panel/state request5. This occurs after validated selected maps, runtime/configuration and local-host setup in0x4666F0.
int rf_multiplayer_begin_authority_session()
{
  rf_multiplayer_server_authority = 1;
  unk_704E84 = 1;
  return rf_client_level_entry_initialize_and_request_panel5();
}

