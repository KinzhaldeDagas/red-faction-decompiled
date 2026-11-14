// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DE430 rf_player_associate_local_runtime_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player lifecycle, weapon-class selection, team-skin material/profile loops, native string-buffer aliases and caller ABI): Cdecl supplied entity pointer. Writes global current entity681E38, global inventory/AI6663C4=entity+672; calls friendliness setter with numeric code2 (writes common504 and invalidates entity target1376). Copies entity UID44 into GLOBAL local-player record20, then calls class-based weapon selection using inventory DWORD4. No entity/player NULL check, allocation, local-player record creation or success handling. Numeric friendliness2 is verified; no authored faction name assigned.
void __cdecl rf_player_associate_local_runtime_entity(int a1)
{
  dword_681E38 = a1;
  dword_6663C4 = a1 + 672;
  sub_4BBF50(a1, 2);
  *(_DWORD *)(rf_local_fpgun_player + 20) = *(_DWORD *)(a1 + 44);
  rf_player_apply_weapon_selection_by_class(rf_local_fpgun_player, *(_DWORD *)(dword_6663C4 + 4));
}

