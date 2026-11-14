// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B0790 rf_client_roster_complete_begin_level_entry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, compiled packet6/9/10/11/23 bindings, endpoint/source use, roster tags, readiness transitions, team sorting
// and native string/color ABI): Noarg. Write server-authority BYTE=0 before calling4494C0 initialization/panel5 helper; preserve delegate EAX. Does not set runtime mode, verify
// roster count/IDs, create local entity, arm sync timer or require current authority/client state. Called on roster tag2.
int rf_client_roster_complete_begin_level_entry()
{
  rf_multiplayer_server_authority = 0;
  return rf_client_level_entry_initialize_and_request_panel5();
}

