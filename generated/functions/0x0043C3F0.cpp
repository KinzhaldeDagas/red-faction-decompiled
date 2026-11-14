// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C3F0 rf_entity_select_weapon_float_with_context_gates
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(required entity,weaponIndex,BYTE alternate,BYTE override), returns a FLOAT32 local through ST0. If jeep
// predicate AL!=0 AND unchecked relation-array2252 slot1 pointer is nonNULL, resolve that relation DWORD4 handle to PLAYER context via4DD720; otherwise resolve own entity handle44. A
// present relation that lacks a matching player does NOT retry own handle. Pass canonical BYTE(player!=NULL), raw weaponIndex and both original low bytes to5102E0, storing
// returnedST0 as FLOAT32. If a player exists and4EAEF0 raw alt-zoom byte is EXACT1, store0. If player exists and511A50 special-pair predicate AL!=0, multiply current FLOAT32 by
// entity FLOAT5044 and round/store again, even after the prior zero: zero times NaN/infinity can yield NaN. Next entity2068 bit4 overrides to0; finally43C120 class flag2_100
// overrides to0. Return final local throughST0. No NULL entity/relation-count/range/finite/clamp guards, no input event/ammo/weapon mutation; do not commute the overrides and
// multiplication.
double __cdecl rf_entity_select_weapon_float_with_context_gates(int a1, int a2, char a3, char a4)
{
  int v4; // eax
  _DWORD *v6; // [esp+0h] [ebp-8h]
  float v7; // [esp+4h] [ebp-4h]

  if ( rf_entity_has_jeep_flag(a1) && *(_DWORD *)sub_552200((_DWORD *)(a1 + 2252), 1) )
  {
    v4 = sub_552200((_DWORD *)(a1 + 2252), 1);
    v6 = sub_4DD720(*(_DWORD *)(*(_DWORD *)v4 + 4));
  }
  else
  {
    v6 = sub_4DD720(*(_DWORD *)(a1 + 44));
  }
  v7 = rf_weapon_select_float224_236_248_260(v6 != nullptr, a2, a3, a4);
  if ( v6 && rf_player_get_alt_zoom_in_flag_byte((int)v6) == 1 )
    v7 = 0.0;
  if ( v6 && rf_weapon_matches_special_pair(a2) )
    v7 = v7 * *(float *)(a1 + 5044);
  if ( (*(_DWORD *)(a1 + 2068) & 4) != 0 )
    v7 = 0.0;
  if ( rf_entity_class_flag2_100(a1) )
    return (float)0.0;
  return v7;
}

