// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C3940 rf_firing_effect_slot_set_pose_if_standard_pair
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, firing effect ring paired ownership, original GeoMod chunk initialization/motion, x87 threshold branches and native five-argument call ABI): 
// Cdecl slotIndex,position,direction. Requires standard pointers0 AND4 nonnull, regardless multiplayer mode or multiplayer pair validity. Then sequentially copies shared slot
// position16/direction28 and normalizes stored direction via reciprocal-sqrt helper; returns that helper result. Without standard pair, no writes and EAX40*index cast to pointer. No
// selected-mode fallback, source snapshots, finite/index guards or direct emitter frame update.
float *__cdecl rf_firing_effect_slot_set_pose_if_standard_pair(int a1, float *source, float *a3)
{
  float *result; // eax
  float v4[3]; // [esp+0h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-Ch] BYREF

  result = (float *)(40 * a1);
  if ( unk_814CF8[10 * a1] )
  {
    if ( unk_814CFC[10 * a1] )
    {
      rf_vector_copy((float *)&unk_814D08 + 10 * a1, copy_result, source);
      rf_vector_copy(&unk_814D14[10 * a1], v4, a3);
      return rf_vector_normalize_reciprocal_sqrt(&unk_814D14[10 * a1]);
    }
  }
  return result;
}

