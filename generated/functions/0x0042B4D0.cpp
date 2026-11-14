// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B4D0 rf_entity_apply_frame_damage_type10
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(entity), void. NULL returns. Player-flag4BB430 EXACT AL1 uses entity FLOAT+56 gate: only ORDERED value>DOUBLE0 suppresses; zero/negative/NaN
// proceeds and skips entity mask40 check. Every other predicate byte instead rejects entity DWORD+2064 mask0x40. Then requires4362E0 ANY nonzero (raw current-room BYTE+66, NULL room
// yields0) and humanoid40D150 ANY nonzero, short-circuited; class(+660) secondary flags DWORD+1832 mask8 must be clear. Damage=FLOAT32(global frame-delta seconds663EC8 * DOUBLE10).
// Calls4BB070(full entity handle+44,damage,-1,-1,type10,0,-1,LOWBYTE0), cleans32 and explicitly discards ST0; no positive/finite damage guard and no success test. Afterwards
// player-pointer-if-type0 predicate4BD1F0 EXACT AL1 constructs local ZERO vector, calls4E05B0(player pointer+5168,&zero), then4E06A0(re-read player pointer,returned direction mask).
// Verified direction helper gives15 for zero X/Z when its player entity resolves, otherwise0; OR helper accumulates low nibble into player flag bits13..16 rather than replacing them.
// Damage failure/zero result does not suppress this indicator path. No own health/dead/runtime/authority test or deadline mutation; damage/HUD delegate effects remain ordered.
void __cdecl rf_entity_apply_frame_damage_type10(int a1)
{
  float *v1; // eax
  char v2; // al
  float v3; // [esp+1Ch] [ebp-10h]
  float v4[3]; // [esp+20h] [ebp-Ch] BYREF

  if ( a1 )
  {
    if ( rf_object_has_player_flag(a1) )
    {
      if ( *(float *)(a1 + 56) > 0.0 )
        return;
    }
    else if ( (*(_DWORD *)(a1 + 2064) & 0x40) != 0 )
    {
      return;
    }
    if ( rf_object_cached_room_byte66((void *)a1)
      && rf_entity_has_humanoid_flag(a1)
      && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 8) == 0 )
    {
      v3 = rf_frame_delta_seconds * 10.0;
      rf_damage_dispatch(*(_DWORD *)(a1 + 44), v3, -1, -1, 10, 0, -1, 0);
      if ( rf_entity_has_player_pointer_if_type0(a1) )
      {
        v1 = rf_vector3_set_components_return_destination(v4, 0.0, 0.0, 0.0);
        v2 = rf_player_direction_to_local_quadrant_mask(*(_DWORD *)(a1 + 5168), v1);
        rf_player_or_direction_nibble_into_flags(*(_DWORD *)(a1 + 5168), v2);
      }
    }
  }
}

