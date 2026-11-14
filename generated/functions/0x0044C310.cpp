// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044C310 rf_hud_world_target_registry_reset
// UNREALRED VERIFIED [hud-world-targets] Clears the fixed world-target registry count without touching unrelated RFL target-marker objects.
void rf_hud_world_target_registry_reset()
{
  rf_hud_world_target_count = 0;
}

