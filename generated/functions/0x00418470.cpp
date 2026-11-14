// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00418470 rf_geomod_debris_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Only runs when physics is enabled at +136. Ordered objectY+64 below world floor (world solid+76) marks deferred deletion but continues contact handling. Sound requires current-contact flag0x10000000 and prior-contact flag0x08000000 clear at +424. Size factor is radius+120 /20, upper-clamped to1 only for ordered >1, then sqrt; no lower/finite clamp. Flags+668 bit8 with nonzero count+680, an already-playing value+684, or liquid-point membership suppress sound, but every admitted first-contact path increments +680. Custom event+688 resolves row/count by contact material+464; positive count calls 0x4BCD20 and stores its selected SOUND ASSET ID in +684, with no fallback after that call. Otherwise material selector uses own
// material+508 and contact material+464, retrying material1 on -1; positional play is invoked even if retry remains -1, storing its VOICE result at +684. These two stored values have distinct native origins. No rollback on deferred deletion/sound failure, flag consumption or counter reset.
void __cdecl rf_geomod_debris_update(int a1)
{
  float v1[3]; // [esp-10h] [ebp-3Ch] BYREF
  int v2; // [esp-4h] [ebp-30h]
  int v3; // [esp+0h] [ebp-2Ch]
  float v4; // [esp+4h] [ebp-28h]
  float size_factor; // [esp+8h] [ebp-24h]
  int v6; // [esp+10h] [ebp-1Ch]
  int v7; // [esp+14h] [ebp-18h] BYREF
  int v8; // [esp+18h] [ebp-14h] BYREF
  int first_dword; // [esp+1Ch] [ebp-10h]
  bool v10; // [esp+22h] [ebp-Ah]
  char v11; // [esp+23h] [ebp-9h]
  float v12; // [esp+24h] [ebp-8h]
  int material_b; // [esp+28h] [ebp-4h]

  if ( rf_physics_state_is_enabled(a1 + 136) )
  {
    if ( *(float *)(rf_world_solid + 76) > (double)*(float *)(a1 + 64) )
      rf_object_mark_for_deferred_delete(a1);
    if ( (*(_DWORD *)(a1 + 424) & 0x10000000) != 0 && (*(_DWORD *)(a1 + 424) & 0x8000000) == 0 )
    {
      v12 = *(float *)(a1 + 120) / 20.0;
      if ( v12 > 1.0 )
        v12 = 1.0;
      v12 = rf_sqrt_float(v12);
      material_b = *(_DWORD *)(a1 + 464);
      v11 = 0;
      if ( (*(_DWORD *)(a1 + 668) & 8) == 0 || !*(_DWORD *)(a1 + 680) )
      {
        v10 = 0;
        first_dword = rf_receiver_get_first_dword((void *)a1);
        if ( first_dword )
          v10 = rf_liquid_room_contains_point(first_dword, a1 + 60);
        if ( !rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 684)) && !v10 )
        {
          if ( *(_DWORD *)(a1 + 688) )
          {
            rf_geomod_debris_bounce_event_resolve(*(_DWORD *)(a1 + 688), material_b, &v8, &v7);
            if ( v7 > 0 )
            {
              v11 = 1;
              size_factor = 0.0;
              v4 = 1.0;
              v3 = v7;
              v2 = v8;
              rf_vector3_copy_return_destination(v1, (float *)(a1 + 60));
              *(_DWORD *)(a1 + 684) = rf_sound_list_select_play_return_asset(
                                        a1,
                                        v1[0],
                                        SLODWORD(v1[1]),
                                        SLODWORD(v1[2]),
                                        v2,
                                        v3,
                                        v4,
                                        size_factor);
            }
          }
          if ( !v11 )
          {
            v6 = rf_geomod_debris_material_sound_select(*(_DWORD *)(a1 + 508), material_b, v12);
            if ( v6 == -1 )
              v6 = rf_geomod_debris_material_sound_select(*(_DWORD *)(a1 + 508), 1, v12);
            *(_DWORD *)(a1 + 684) = rf_gamesound_play_positional_event(
                                      v6,
                                      (float *)(a1 + 60),
                                      1.0,
                                      (int)&unk_17F10B0,
                                      0);
          }
        }
      }
      ++*(_DWORD *)(a1 + 680);
    }
  }
}

