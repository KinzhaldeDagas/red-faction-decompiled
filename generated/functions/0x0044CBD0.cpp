// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CBD0 rf_hud_persona_set_target_opacity255
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Stores the supplied float divided by double 255.0 as target opacity, without clamping. Admission supplies 255.0; the timer-and-voice-complete render branch supplies 0.0.
void __cdecl rf_hud_persona_set_target_opacity255(float opacity_255)
{
  float v1; // [esp+0h] [ebp-4h]

  v1 = opacity_255 / 255.0;
  rf_hud_persona_target_opacity = v1;
}

