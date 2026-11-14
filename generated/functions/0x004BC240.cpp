// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC240 rf_object_refresh_room_cache_and_audio
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Thiscall common receiver, no stack arguments. Refreshes room if current room DWORD0 isNULL OR cached-position4 to common-position60 squared distance is ORDERED >0; NaN/zero distance with nonnull room skips resolve. Calls world cached-room resolver with oldRoomNULL and start=end=commonPos,final flag0. On nonnull result, if changed room AND global local FPGun player exists AND object handle44 equals player entity handle20, sets audio environment to underwater when liquid contains position, otherwise room C-string+74. Writes new room0 and caches common position+4. Resolver failure leaves old room/position unchanged. ALWAYS clears common dirty mask0x04000000 at+124, including failure/NaN/unchanged paths.
// Does not require dirty bit at entry, test exact component inequality, update physical position or retain dirty bit for retry. No own world/object/room-string validation; audio extension availability handled by delegate.
// UNREALRED VERIFIED (2026-11-11; native ABI refinement): ECX common receiver ONLY, no incoming ST0 or stack argument. The only local x87 comparison consumes distance-squared helper RETURN at4BC25F; null-room path skips both. Saved usercall ST0 input was false and propagated to4BD750. Corrected thiscall prototype preserves EAX result: final native AND4BC31A/store4BC322 leaves newly masked common flags inEAX on every normal path, not a normalized success code.
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Consumed burn-room adapter must use direct POINT lookup517060(NULL,current3C,current3C,0), NOT old-room portal/crossing resolution. Refresh when cached roomNULL or ordered5598C0(cached4,current3C)>0; compare forwarded ST0, whose final squared sum already rounds FLOAT32 in40D1C0 at40D1EF/40D1F2; no extra caller rounding store (clarified2026-11-12). NONNULL lookup commits room0+cached4. Native null retains BOTH old room AND cached position. Always clears dirty04000000. Host geometry-provider unavailable is distinct from native classifier returningNULL; never erase a retained room or label failed provider a known native null.
unsigned int __thiscall rf_object_refresh_room_cache_and_audio(void *this)
{
  unsigned int result; // eax
  float copy_result[3]; // [esp+4h] [ebp-10h] BYREF
  char *v4; // [esp+10h] [ebp-4h]

  if ( !*(_DWORD *)this || rf_vector_distance_squared((const float *)this + 1, (const float *)this + 15) > 0.0 )
  {
    v4 = (char *)rf_world_resolve_cached_room(
                   (void *)rf_world_solid,
                   nullptr,
                   (const float *)this + 15,
                   (const float *)this + 15,
                   0);
    if ( v4 )
    {
      if ( v4 != *(char **)this
        && rf_local_fpgun_player
        && *((_DWORD *)this + 11) == *(_DWORD *)(rf_local_fpgun_player + 20) )
      {
        if ( rf_liquid_room_contains_point((int)v4, (int)this + 60) )
          rf_audio_set_environment_if_property_extension_enabled("underwater");
        else
          rf_audio_set_environment_if_property_extension_enabled(v4 + 74);
      }
      *(_DWORD *)this = v4;
      rf_vector_copy((float *)this + 1, copy_result, (const float *)this + 15);
    }
  }
  result = *((_DWORD *)this + 31) & 0xFBFFFFFF;
  *((_DWORD *)this + 31) = result;
  return result;
}

