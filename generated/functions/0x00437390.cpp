// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00437390 rf_entity_apply_type9_damage_and_play_sound
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(required entity), fullEAX positional sound result. Calls4BB070 with EIGHT stack slots(raw entity
// handle44,FLOAT1000000,-1,-1,DWORD9,DWORD0,-1,LOWBYTE0); discards floating damage result with FSTP ST. No damage-success/death/authority check or original-pointer re-resolution
// before suffix. AFTER damage, re-read entity class660 DWORD372 Foley group;447010 chooses random sound, then568250(event,RE-READ entity COMMON
// position60,FLOAT1,address17F10B0,DWORD0), with no event-1 guard. Returns sound helper fullEAX, not applied damage or kill success; does not store returned voice on owner.
// Entity/class/position must remain readable after damage side effects. No NULL/ownership/state check, repeated damage, own health write, cleanup or rollback.
int __cdecl rf_entity_apply_type9_damage_and_play_sound(int a1)
{
  int v2; // [esp+1Ch] [ebp-8h]

  rf_damage_dispatch(*(_DWORD *)(a1 + 44), 1000000.0, -1, -1, 9, 0, -1, 0);
  v2 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 372));
  return rf_gamesound_play_positional_event(v2, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
}

