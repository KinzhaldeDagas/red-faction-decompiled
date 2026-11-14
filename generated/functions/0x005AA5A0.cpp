// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005AA5A0 rf_ui_process_frame_input
// UNREALRED VERIFIED [ui-frame-scroll-20261029]: cdecl input code,clear-consumed-mouse byte. Ensures default theme. Samples enabled mouse press/release counts into globals0x1CF7593/91(primary),0x1CF7590/92(secondary;secondary press suppressed when primary press);double-click bytes gated by0x1CF7C19/18 into0x1CF75C4/5. Saves prior pointer XY then reads absolute coordinates and wheel. Press pick walks windows from0x1CF7B60 via+1256;double-click flag retained only for same gadget as prior0x1CF7C14. Otherwise updates hover object0x1CF75E0 by gadget/window hit tests;changed/absent target clears tooltip flag. Clears global focus0x1CF75D8 when hidden predicate or interaction-blocked. Processes each window through0x5B0CA0,threading input code and SAVING next window before callback. If callback alters sampled mouse-event globals,marks consumed and restores originals for subsequent windows. Tooltip:
// primary held or mouse movement clears ready/rearms1000 deadline;stationary hover sets ready when deadline elapsed. Primary release finishes dragged object0x1CF75D0 unless cancel BYTE0x1CF75C7:valid target+1100 distinct from source with source amount+1092+target count+1084<=target limit+1088 sets global drop target0x1CF75D4,updates counts conditionally on nonnegative limits,emits source events17 then16. No target and not owner hover target decrements source count and emits16. Clears drag/cancel/drop globals afterward. If any window consumed mouse flags AND second input byte EXACT1,calls0x58AAE0 to clear physical3-button transitions. Returns final input code. Does not draw windows or poll keyboard queue itself.
int __cdecl rf_ui_process_frame_input(int a1, char a2)
{
  bool v3; // [esp+0h] [ebp-4Ch]
  bool v4; // [esp+4h] [ebp-48h]
  bool v5; // [esp+8h] [ebp-44h]
  int v6; // [esp+Ch] [ebp-40h] BYREF
  bool v7; // [esp+11h] [ebp-3Bh]
  bool v8; // [esp+12h] [ebp-3Ah]
  char v9; // [esp+13h] [ebp-39h]
  int v10; // [esp+14h] [ebp-38h] BYREF
  _DWORD *v11; // [esp+18h] [ebp-34h]
  unsigned __int8 v12; // [esp+1Fh] [ebp-2Dh]
  int v13; // [esp+20h] [ebp-2Ch] BYREF
  _DWORD *i; // [esp+24h] [ebp-28h]
  int v15; // [esp+28h] [ebp-24h] BYREF
  _DWORD *v16; // [esp+2Ch] [ebp-20h]
  char v17; // [esp+31h] [ebp-1Bh]
  char v18; // [esp+32h] [ebp-1Ah]
  unsigned __int8 v19; // [esp+33h] [ebp-19h]
  _DWORD *v20; // [esp+34h] [ebp-18h]
  bool v22; // [esp+3Fh] [ebp-Dh]
  int v23; // [esp+40h] [ebp-Ch] BYREF
  int v24; // [esp+44h] [ebp-8h] BYREF
  unsigned __int8 v25; // [esp+4Bh] [ebp-1h]

  v11 = nullptr;
  v9 = 0;
  v17 = 0;
  v18 = 0;
  rf_ui_initialize_default_theme_once();
  unk_1CF759C = a1;
  unk_1CF7593 = rf_mouse_button_has_press_count(0);
  v25 = unk_1CF7593;
  unk_1CF7591 = rf_mouse_button_has_release_count(0);
  v19 = unk_1CF7591;
  v5 = !unk_1CF7593 && rf_mouse_button_has_press_count(1);
  unk_1CF7590 = v5;
  v8 = v5;
  unk_1CF7592 = rf_mouse_button_has_release_count(1);
  v12 = unk_1CF7592;
  v4 = unk_1CF7C19 && rf_mouse_get_button_double_click_byte(0);
  unk_1CF75C4 = v4;
  v22 = v4;
  v3 = unk_1CF7C18 && unk_1CF7590 && rf_mouse_get_button_double_click_byte(1);
  unk_1CF75C5 = v3;
  v7 = v3;
  if ( unk_1CF7593 || unk_1CF7591 || unk_1CF7590 || unk_1CF7592 || unk_1CF75C4 || unk_1CF75C5 )
    v17 = 1;
  unk_1CF75C8 = dword_1CF7594;
  unk_1CF75CC = dword_1CF75C0;
  rf_mouse_get_absolute_state(&dword_1CF7594, &dword_1CF75C0, &unk_193A03C);
  rf_mouse_get_relative_deltas(&v6, &v24, &dword_1CF7598);
  if ( unk_1CF7593 || unk_1CF7590 )
  {
    for ( i = (_DWORD *)unk_1CF7B60; i != dword_1CF7678; i = (_DWORD *)i[314] )
    {
      v11 = rf_ui_window_hit_test_top_level_tree(i, dword_1CF7594, dword_1CF75C0);
      if ( v11 )
      {
        if ( unk_1CF7593 )
        {
          if ( unk_1CF75C4 && (_DWORD *)unk_1CF7C14 != v11 )
            unk_1CF75C4 = 0;
        }
        else if ( unk_1CF7590 && unk_1CF75C5 && (_DWORD *)unk_1CF7C14 != v11 )
        {
          unk_1CF75C5 = 0;
        }
        unk_1CF7C14 = v11;
        break;
      }
    }
    if ( !v11 )
      unk_1CF7C14 = 0;
    if ( unk_1CF7593 )
      unk_1CF7C19 = unk_1CF75C4 == 0;
    if ( unk_1CF7590 )
      unk_1CF7C18 = unk_1CF75C5 == 0;
  }
  if ( v11 )
  {
    v9 = 1;
    if ( dword_1CF75E0 != v11 )
    {
      unk_1CF75C6 = 0;
      dword_1CF75E0 = v11;
    }
  }
  else
  {
    for ( i = (_DWORD *)unk_1CF7B60; i != dword_1CF7678; i = (_DWORD *)i[314] )
    {
      if ( !(*(unsigned __int8 (__thiscall **)(_DWORD *))(*i + 16))(i) )
      {
        v16 = rf_ui_window_hit_test_top_level_tree(i, dword_1CF7594, dword_1CF75C0);
        if ( v16 )
        {
          v9 = 1;
          if ( dword_1CF75E0 != v16 )
          {
            unk_1CF75C6 = 0;
            dword_1CF75E0 = v16;
          }
        }
        else
        {
          rf_ui_base_get_size(i, &v15, &v10);
          rf_ui_base_get_position(i, &v13, &v23);
          v13 = dword_1CF7594 - v13;
          v23 = dword_1CF75C0 - v23;
          if ( v13 >= 0 && v23 >= 0 && v13 < v15 && v23 < v10 )
          {
            if ( rf_ui_window_hit_mask_value_at_screen_point(i, dword_1CF7594, dword_1CF75C0) )
            {
              v9 = 1;
              if ( dword_1CF75E0 != i )
              {
                unk_1CF75C6 = 0;
                dword_1CF75E0 = i;
              }
            }
          }
        }
      }
    }
  }
  if ( !v9 && dword_1CF75E0 )
  {
    unk_1CF75C6 = 0;
    dword_1CF75E0 = nullptr;
  }
  if ( dword_1CF75D8
    && ((*(unsigned __int8 (__thiscall **)(_DWORD *))(*dword_1CF75D8 + 16))(dword_1CF75D8)
     || rf_ui_gadget_is_interaction_blocked(dword_1CF75D8)) )
  {
    dword_1CF75D8 = nullptr;
  }
  i = (_DWORD *)unk_1CF7B60;
  while ( i != dword_1CF7678 )
  {
    v20 = (_DWORD *)i[314];
    a1 = rf_ui_window_process_input((int)i, a1);
    i = v20;
    if ( v17
      && (unk_1CF7593 != v25
       || unk_1CF7591 != v19
       || unk_1CF7590 != v8
       || unk_1CF7592 != v12
       || unk_1CF75C4 != v22
       || unk_1CF75C5 != v7) )
    {
      v18 = 1;
      unk_1CF7593 = v25;
      unk_1CF7591 = v19;
      unk_1CF7590 = v8;
      unk_1CF7592 = v12;
      unk_1CF75C4 = v22;
      unk_1CF75C5 = v7;
    }
  }
  if ( dword_1CF75E0 )
  {
    if ( !rf_mouse_get_button_held_byte(0) )
    {
      if ( unk_1CF75C6 )
        goto LABEL_90;
      if ( unk_1CF75C8 == dword_1CF7594 && unk_1CF75CC == dword_1CF75C0 )
      {
        unk_1CF75C6 = rf_clock_deadline_has_elapsed_half_period(&unk_1CF7644);
        goto LABEL_90;
      }
    }
    unk_1CF75C6 = 0;
    rf_clock_deadline_set_wrapped_offset(&unk_1CF7644, 1000);
  }
  else
  {
    unk_1CF75C6 = 0;
  }
LABEL_90:
  if ( unk_1CF7591 && dword_1CF75D0 )
  {
    if ( !unk_1CF75C7 )
    {
      if ( *((_DWORD *)dword_1CF75D0 + 275) )
      {
        if ( *((char **)dword_1CF75D0 + 275) != dword_1CF75D0
          && *((_DWORD *)dword_1CF75D0 + 273) + *(_DWORD *)(*((_DWORD *)dword_1CF75D0 + 275) + 1084) <= *(_DWORD *)(*((_DWORD *)dword_1CF75D0 + 275) + 1088) )
        {
          unk_1CF75D4 = *((_DWORD *)dword_1CF75D0 + 275);
          if ( *(int *)(*((_DWORD *)dword_1CF75D0 + 275) + 1088) >= 0 )
            *(_DWORD *)(*((_DWORD *)dword_1CF75D0 + 275) + 1084) += *((_DWORD *)dword_1CF75D0 + 273);
          (*(void (__thiscall **)(char *, int, int))(*(_DWORD *)dword_1CF75D0 + 4))(dword_1CF75D0, 17, -99999);
          if ( *((int *)dword_1CF75D0 + 272) >= 0 )
            *((_DWORD *)dword_1CF75D0 + 271) -= *((_DWORD *)dword_1CF75D0 + 273);
          (*(void (__thiscall **)(char *, int, int))(*(_DWORD *)dword_1CF75D0 + 4))(dword_1CF75D0, 16, -99999);
        }
      }
      else if ( !rf_ui_gadget_is_owner_hover_target(dword_1CF75D0) )
      {
        *((_DWORD *)dword_1CF75D0 + 271) -= *((_DWORD *)dword_1CF75D0 + 273);
        (*(void (__thiscall **)(char *, int, int))(*(_DWORD *)dword_1CF75D0 + 4))(dword_1CF75D0, 16, -99999);
      }
    }
    unk_1CF75C7 = 0;
    dword_1CF75D0 = nullptr;
    unk_1CF75D4 = 0;
  }
  if ( v18 == 1 && a2 == 1 )
    rf_mouse_clear_three_button_transients();
  return a1;
}

