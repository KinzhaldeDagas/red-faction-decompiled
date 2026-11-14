// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046B5C0 rf_gameplay_difficulty_group_press_apply
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, video/performance/gameplay call chains, original gamma constants and compiled labels, native
// x87/byte/stack/callback ABI): Cdecl(x,y). Hit-test child pointers6F7FC8/count6F8048;nonnegative hit/nonnull callback32 ->TWO ORIGINAL(x,y),cleanup8. Then selected
// difficultyDWORD6F7F54 ->configured difficulty6612A8 ALWAYS;ONLY multiplayer_runtime_mode BYTE==0 also writes active difficulty6612A4. Any nonzero runtime byte suppresses active
// update. No choice-range/player/state9/changed-choice validation,rollback or configuration save;no hit/callback skips commit. Native gameplay builder Difficulty Level label,4
// choices easy/medium/hard/insane and callback binding verified.
int __cdecl rf_gameplay_difficulty_group_press_apply(int physical_x, int physical_y)
{
  int result; // eax

  result = rf_ui_hit_test_enabled_buttons(physical_x, physical_y, (void *const *)unk_6F7FC8, dword_6F8048);
  if ( result >= 0 && *(_DWORD *)(unk_6F7FC8[result] + 32) )
  {
    result = (*(int (__cdecl **)(int, int))(unk_6F7FC8[result] + 32))(physical_x, physical_y);
    dword_6612A8 = unk_6F7F54;
    if ( !rf_multiplayer_runtime_mode )
    {
      dword_6612A4 = dword_6612A8;
      return dword_6612A8;
    }
  }
  return result;
}

