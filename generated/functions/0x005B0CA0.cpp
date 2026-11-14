// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B0CA0 rf_ui_window_process_input
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: Thiscall window,input code. Blocked or virtual hidden predicate true STILL threads code through root child virtual+20 and returns. Normal branch sets global0x1CF7C24=1,reads relative motion;motion,release flags or forced BYTE+1244 enable navigation-target refresh. Gets gadget hit0x5B0700. Flag0x10 with no navigation target+1228 attempts last registered gadget+1204:BUG loop0x5B0DA4..DD4 NEVER advances candidate when virtual+32 false,so stable ineligible last gadget can stall. When neither button0 nor1 held and refresh requested,chooses eligible hit or retained target(flag0x10),emits events8 old/7 new. Hover+1224 follows hit and old hover gets event5. Processes root children. Primary click on window background releases global keyboard focus and consumes primary press;flags0xC optionally process window keyboard navigation0x5AF4C0. Gadget/window
// hit consumes6 global mouse flags;clears active0x1CF7C24 afterward. Flag bit31 set calls own virtual slot0. Saves no queue and does not draw;returns final code.
int __thiscall rf_ui_window_process_input(int this, int a2)
{
  _DWORD *v4; // [esp+4h] [ebp-18h]
  char v5; // [esp+Bh] [ebp-11h]
  _DWORD *v6; // [esp+Ch] [ebp-10h]
  _DWORD *i; // [esp+10h] [ebp-Ch]
  int v8; // [esp+10h] [ebp-Ch]
  _DWORD *j; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h] BYREF
  int v11; // [esp+18h] [ebp-4h] BYREF

  v5 = 0;
  if ( rf_ui_window_is_interaction_blocked((_DWORD *)this)
    || (*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)this + 16))(this) )
  {
    for ( i = *(_DWORD **)(this + 1220); i; i = (_DWORD *)i[156] )
      a2 = (*(int (__thiscall **)(_DWORD *, int))(*i + 20))(i, a2);
    return a2;
  }
  else
  {
    unk_1CF7C24 = 1;
    rf_mouse_get_relative_deltas(&v10, &v11, &unk_193A03C);
    if ( v10 || v11 || unk_1CF7591 || unk_1CF7592 || *(_BYTE *)(this + 1244) )
    {
      v5 = 1;
      *(_BYTE *)(this + 1244) = 0;
    }
    v6 = rf_ui_window_hit_test_top_level_tree((_DWORD *)this, dword_1CF7594, dword_1CF75C0);
    if ( (*(_DWORD *)(this + 584) & 0x10) != 0 && !*(_DWORD *)(this + 1228) )
    {
      v8 = *(_DWORD *)(this + 1204);
      while ( v8 != this + 592 )
      {
        if ( (*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)v8 + 32))(v8) )
        {
          *(_DWORD *)(this + 1228) = v8;
          break;
        }
      }
    }
    if ( !rf_mouse_get_button_held_byte(0) && !rf_mouse_get_button_held_byte(1) && v5 )
    {
      v4 = nullptr;
      if ( v6 && (*(unsigned __int8 (__thiscall **)(_DWORD *))(*v6 + 32))(v6) )
      {
        v4 = v6;
      }
      else if ( (*(_DWORD *)(this + 584) & 0x10) != 0 )
      {
        v4 = *(_DWORD **)(this + 1228);
      }
      if ( *(_DWORD **)(this + 1228) != v4 )
      {
        if ( *(_DWORD *)(this + 1228) )
          (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1228) + 4))(
            *(_DWORD *)(this + 1228),
            8,
            -99999);
        *(_DWORD *)(this + 1228) = v4;
        if ( *(_DWORD *)(this + 1228) )
          (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1228) + 4))(
            *(_DWORD *)(this + 1228),
            7,
            -99999);
      }
    }
    if ( v6 != *(_DWORD **)(this + 1224) )
    {
      if ( *(_DWORD *)(this + 1224) )
        (*(void (__thiscall **)(_DWORD, int, int))(**(_DWORD **)(this + 1224) + 4))(*(_DWORD *)(this + 1224), 5, -99999);
      *(_DWORD *)(this + 1224) = v6;
    }
    for ( j = *(_DWORD **)(this + 1220); j; j = (_DWORD *)j[156] )
      a2 = (*(int (__thiscall **)(_DWORD *, int))(*j + 20))(j, a2);
    if ( !v6 && rf_ui_window_contains_point_if_visible((_DWORD *)this, dword_1CF7594, dword_1CF75C0) && unk_1CF7593 )
    {
      rf_ui_gadget_release_keyboard_focus(dword_1CF75D8);
      unk_1CF7593 = 0;
    }
    if ( (*(_DWORD *)(this + 584) & 0xC) != 0 )
      a2 = rf_ui_window_navigate_selection_by_scan_code(this, a2);
    if ( v6 || rf_ui_window_contains_point_if_visible((_DWORD *)this, dword_1CF7594, dword_1CF75C0) )
    {
      unk_1CF7593 = 0;
      unk_1CF7591 = 0;
      unk_1CF7590 = 0;
      unk_1CF7592 = 0;
      unk_1CF75C4 = 0;
      unk_1CF75C5 = 0;
    }
    unk_1CF7C24 = 0;
    if ( *(int *)(this + 584) < 0 )
      (**(void (__thiscall ***)(int))this)(this);
    return a2;
  }
}

