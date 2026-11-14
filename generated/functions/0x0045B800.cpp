// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B800 rf_multiplayer_level_rotation_add_all_missing_rows
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Noarg. For each row index0..filteredLevelCount-1,scan entire selected-index array6F2E64 for equality;does NOT break
// when found. Append row only if absent. Both counts queried dynamically each loop. Retains existing rotation order and any preexisting duplicates/invalid entries;appends missing
// rows in ascending filtered-row order. No clear,sort,sound,current-row/scroll reset or level-record pointer storage. Return final level count residue,not number added.
int rf_multiplayer_level_rotation_add_all_missing_rows()
{
  int result; // eax
  int j; // [esp+0h] [ebp-Ch]
  char v2; // [esp+7h] [ebp-5h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(&unk_6F2DC4);
    if ( i >= result )
      break;
    v2 = 0;
    for ( j = 0; j < rf_receiver_get_first_dword(unk_6F2E64); ++j )
    {
      if ( *(_DWORD *)sub_552200(unk_6F2E64, j) == i )
        v2 = 1;
    }
    if ( !v2 )
      rf_pointer_array_append_dword(unk_6F2E64, i);
  }
  return result;
}

