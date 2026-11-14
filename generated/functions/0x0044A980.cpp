// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044A980 rf_hud_reset_layers_unless_flag704E83_is1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments; exact BYTE704E83==1 skips all delegates with EAX1 fromMOVZX; every other byte, including other nonzero values,
// runs strict sequence44B260 message-queue metadata/deadline reset,44CEB0 persona-presentation reset,44C2F0,44E130,44D930,44C310 world-target-count reset. No result gating between
// calls. Last delegate EAX is incidental on admitted branch, not uniform success. Parent does not memset all HUD storage, stop every persona voice, clear retained message texts or
// reset every persona history entry; delegated partial/reset ownership is preserved. No own player argument, allocation, pause gate or rollback.
void rf_hud_reset_layers_unless_flag704E83_is1()
{
  if ( byte_704E83 != 1 )
  {
    rf_hud_message_queue_reset_metadata_and_deadline();
    rf_hud_persona_reset_presentation();
    rf_hud_lifecycle_noop_44C2F0();
    sub_44E130();
    rf_hud_zero_local_player_fields11E0_through11EC();
    rf_hud_world_target_registry_reset();
  }
}

