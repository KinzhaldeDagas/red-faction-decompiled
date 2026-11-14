// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045B590 rf_multiplayer_level_list_toggle_row
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Cdecl(x,y). Only when BOTH coordinates signed-negative use current rowDWORD6F2D08;otherwise derive row=scrollDWORD6F2D04 +
// signed(y-truncTowardZero(absoluteY(control6F3334)*scaleY))/rowHeightDWORD6F299C. X otherwise unused; no divisor-zero guard,explicit screen rectangle or floor correction for
// negative y. Require row>=0 and row<firstDWORD of level array6F2DC4;store current row6F2D08 BEFORE scanning selected-index array6F2E64. Scan its firstDWORD count each
// iteration,element address552200 uses backing pointer+8 and4*index. On first stored DWORD==row erase that index and return;otherwise append row. Selection stores row INDEX,not level
// pointer/name;no duplicate-all purge,normalization,sound or scroll update here. Invalid row leaves selection/current row unchanged;return EAX incidental count/index/delegate result.
// Both keyboard(-1,-1) and pointer callback use it.
int __cdecl rf_multiplayer_level_list_toggle_row(int a1, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-Ch]
  int v4; // [esp+Ch] [ebp-4h]

  if ( a1 >= 0 || a2 >= 0 )
  {
    result = (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F3334) * rf_ui_scale_y)) / dword_6F299C;
    v4 = unk_6F2D04 + result;
  }
  else
  {
    result = unk_6F2D08;
    v4 = unk_6F2D08;
  }
  if ( v4 >= 0 )
  {
    result = rf_receiver_get_first_dword(&unk_6F2DC4);
    if ( v4 < result )
    {
      unk_6F2D08 = v4;
      for ( i = 0; i < rf_receiver_get_first_dword(unk_6F2E64); ++i )
      {
        if ( *(_DWORD *)sub_552200(unk_6F2E64, i) == v4 )
          return (int)rf_pointer_array_erase_index_unchecked(unk_6F2E64, i);
      }
      return rf_pointer_array_append_dword(unk_6F2E64, v4);
    }
  }
  return result;
}

