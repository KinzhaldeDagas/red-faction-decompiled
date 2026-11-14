// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DA560 rf_developer_kill_self_command
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): No arguments. Any nonzero console execute1809818 calls4DF5E0 with global local player; no own player NULL check, help branch or other effects. Its address is referenced by retail command-constructor code62CF63. Return value unspecified; existing command name preserved.
void rf_developer_kill_self_command()
{
  if ( dword_1809818 )
    rf_player_request_suicide_or_apply_fixed_damage(rf_local_fpgun_player);
}

