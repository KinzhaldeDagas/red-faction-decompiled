// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473030 rf_item_advance_fade_lifetime
// UNREALRED VERIFIED [item-pickups-20261028]: Only when respawn-inactive flag is clear and fading bit4 set, subtracts frame delta seconds from float+692 and marks item for deferred deletion when<=0. Does not directly unlink/free item, clear fade bit, or clamp negative lifetime.
void __cdecl rf_item_advance_fade_lifetime(int a1)
{
  if ( !rf_object_has_respawn_inactive_flag(a1) && rf_item_is_fading(a1) )
  {
    *(float *)(a1 + 692) = *(float *)(a1 + 692) - rf_frame_delta_seconds;
    if ( *(float *)(a1 + 692) <= 0.0 )
      rf_object_mark_for_deferred_delete(a1);
  }
}

