// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACCE0 rf_powerup_nodes_initialize_and_register_cleanup
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Noarg init. Set three HUD powerup bitmap handles (invulnerability,damage,nano) to-1, register4ACB80 with atexit ignoring registration result, assign root7B2548=0 and
// return EAX0. No existing list teardown, old bitmap release, duplicate-init guard or allocation. Reinitializing a live root loses ownership of old nodes.
int rf_powerup_nodes_initialize_and_register_cleanup()
{
  rf_hud_powerup_invulnerability_bitmap = -1;
  rf_hud_powerup_damage_bitmap = -1;
  rf_hud_powerup_nano_bitmap = -1;
  atexit(rf_powerup_nodes_atexit_destroy_all);
  unk_7B2548 = 0;
  return 0;
}

