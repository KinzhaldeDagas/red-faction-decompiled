// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437370 rf_entity_refresh_idle_animation_deadline
// UNREALRED VERIFIED [mission-play-animation-20261013] Arms Entity+0x1370 with inclusive random30000..60000 milliseconds through0x55EFF0. Play_Animation calls this before the per-entity animation-slot availability check. It does not reset action/state animation contexts.
// UNREALRED VERIFIED [mission-unhide-20261020] Refreshes the idle-animation deadline using inclusive random30000..60000 milliseconds. Common reactivation4BC930 invokes this even for an already-active entity; UnrealRed refreshes its idle cooldown on every admitted show callback.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] 437370 draws inclusive integer30000..60000 milliseconds via55EFF0 into Entity+1370. Common reactivation4BC930 calls it even on repeated show; canonical PlayAnimation also calls before absent animation-slot admission. This draw belongs to shared CRT stream, not UE FMath or independent actor RNG.
int __cdecl rf_entity_refresh_idle_animation_deadline(int a1)
{
  return rf_timestamp_arm_random_inclusive_milliseconds((int *)(a1 + 4976), 30000, 60000);
}

