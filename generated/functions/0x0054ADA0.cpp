// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054ADA0 rf_scratch_arena_rewind_and_clear_owners
// UNREALRED VERIFIED [resource-pools-20261028]: Resets cursor0x1482004 to arena base0x1426C70; for each tracked owner pointer in0x1494718[0..count0x1426C74) clears owner+4; then clears count. Does not free arena, zero arena bytes or update arena end.
void *__cdecl rf_scratch_arena_rewind_and_clear_owners()
{
  void *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = MEMORY[0x1426C70];
  unk_1482004 = MEMORY[0x1426C70];
  for ( i = 0; i < dword_1426C74; ++i )
  {
    result = (void *)i;
    *(_DWORD *)(unk_1494718[i] + 4) = 0;
  }
  dword_1426C74 = 0;
  return result;
}

