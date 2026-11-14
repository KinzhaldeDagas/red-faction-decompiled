// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00462370 rf_browser_list_press_or_join
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, browser cache/favorites and UI call chains, query flags/timers, original endpoint layouts and native callback
// ABI): Cdecl(x,y). Either coordinate<=0 ->join-selected(-1,-1),no double-click timer arm. Positive coordinates:subtract truncated scaled absolute
// listX/Y;row=(y-listY)/pixelRowHeight via signed IDIV. Compare VISIBLE ordinal directly with selected DISPLAY index6F52E0 (includes scroll):same and400ms deadline5554 not elapsed
// ->join. Otherwise require row<visibleRows and row+scroll<visibleCount,then mapped raw index>=0/<liveCount;there is NO row>=0 or row+scroll>=0 guard before index dereference. Store
// displayselection=row+scroll and rawselection=indexArray[displayselection]. If unscaled column bounds661FA0<xRelative<661FA4 strictly,toggle favorite by high flag. Every
// positive-coordinate path arms400ms,even invalid bounds/double-click join. No own list active/sort/rebuild guard;timer comparison uses elapsed helper directly.
void __cdecl rf_browser_list_press_or_join(int a1, int a2)
{
  int v2; // [esp+Ch] [ebp-8h]
  int v3; // [esp+10h] [ebp-4h]

  if ( a1 <= 0 || a2 <= 0 )
  {
    rf_multiplayer_menu_join_selected_server();
  }
  else
  {
    v2 = a1 - (int)((double)rf_ui_control_absolute_x(&dword_6F57B4) * rf_ui_scale_x);
    v3 = (a2 - (int)((double)rf_ui_control_absolute_y(&dword_6F57B4) * rf_ui_scale_y)) / dword_6F299C;
    if ( v3 != unk_6F52E0 || rf_clock_deadline_has_elapsed_half_period(&dword_6F5554) )
    {
      if ( v3 < unk_6F508C
        && v3 + unk_6F52E4 < (int)MEMORY[0x6F5088]
        && *((int *)MEMORY[0x6F52D4] + v3 + unk_6F52E4) >= 0
        && *((_DWORD *)MEMORY[0x6F52D4] + v3 + unk_6F52E4) < unk_6F51A8 )
      {
        unk_6F52E0 = v3 + unk_6F52E4;
        dword_661F9C = *((_DWORD *)MEMORY[0x6F52D4] + v3 + unk_6F52E4);
        if ( v2 > dword_661FA0 && v2 < dword_661FA4 )
        {
          if ( *((int *)dword_6F52CC + 27 * dword_661F9C + 26) >= 0 )
            rf_browser_add_favorite_row(dword_661F9C);
          else
            rf_browser_remove_favorite_row(dword_661F9C);
        }
      }
    }
    else
    {
      rf_multiplayer_menu_join_selected_server();
    }
    rf_clock_deadline_set_wrapped_offset(&dword_6F5554, 400);
  }
}

