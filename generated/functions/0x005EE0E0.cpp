// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EE0E0 rf_ui_slider_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Hidden returns key;blocked feedback sound6 on hovered primary press or bound key,returns. Otherwise traverses children and retains returned key;primary-activation predicate on decrement676 reduces raw position652,increment672 increases. Computes thumb rectangle BEFORE range clamp. Mouse local x/y from global coordinates. Hovered primary press sets deadline628+450,state1 inside thumb (captures position640 and axis coordinate636),else state2page-forward if x>=thumbX AND y>=thumbY,otherwise3backward. Held primary+hover+deadline elapsed rearms150 and triggers paging by step660 in state2/3. State1 drag maps axis delta*(range-1)/(trackExtent-thumbLength),rounded via +/-divisor/2 before signed division,added to captured position640;zero travel skips update,products can overflow. Secondary press
// globally cancels drag1/restores captured position,then releasing primary resets state0. No final position clamp,event notification or automatic keyboard adjustment here;returns child-traversal code. Existing No process/Dot slider parser flags are not tested.
int __thiscall rf_ui_slider_process_input(int this, int a2)
{
  int v4; // [esp+4h] [ebp-24h]
  int v5; // [esp+4h] [ebp-24h]
  int v6; // [esp+4h] [ebp-24h]
  int v7; // [esp+8h] [ebp-20h]
  int v8; // [esp+Ch] [ebp-1Ch] BYREF
  int v9; // [esp+10h] [ebp-18h] BYREF
  char v10; // [esp+17h] [ebp-11h]
  int v11; // [esp+18h] [ebp-10h] BYREF
  int v12; // [esp+1Ch] [ebp-Ch] BYREF
  int v13; // [esp+20h] [ebp-8h]
  int v14; // [esp+24h] [ebp-4h]
  int v15; // [esp+30h] [ebp+8h]

  v10 = 0;
  if ( (*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)this + 16))(this) )
    return a2;
  if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
  {
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target((_DWORD *)this) )
      rf_ui_play_feedback_sound(6);
    if ( rf_ui_gadget_matches_bound_key((_DWORD *)this, a2) )
      rf_ui_play_feedback_sound(6);
    return a2;
  }
  else
  {
    v15 = rf_ui_gadget_process_children_input((_DWORD *)this, a2);
    if ( *(_DWORD *)(this + 676) && rf_ui_button_is_primary_activation_state(*(_DWORD **)(this + 676)) )
      --*(_DWORD *)(this + 652);
    if ( *(_DWORD *)(this + 672) && rf_ui_button_is_primary_activation_state(*(_DWORD **)(this + 672)) )
      ++*(_DWORD *)(this + 652);
    rf_ui_slider_get_thumb_rect_unclamped(this, &v8, &v9, &v12, &v11);
    v13 = dword_1CF7594 - rf_ui_gadget_absolute_x((_DWORD *)this, 0);
    v14 = dword_1CF75C0 - rf_ui_gadget_absolute_y((_DWORD *)this, 0);
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target((_DWORD *)this) )
    {
      rf_clock_deadline_set_wrapped_offset((int *)(this + 628), 450);
      v10 = 1;
      if ( v13 < v8 || v13 >= v12 + v8 || v14 < v9 || v14 >= v11 + v9 )
      {
        if ( v13 >= v8 && v14 >= v9 )
          *(_DWORD *)(this + 632) = 2;
        else
          *(_DWORD *)(this + 632) = 3;
      }
      else
      {
        *(_DWORD *)(this + 632) = 1;
        *(_DWORD *)(this + 640) = *(_DWORD *)(this + 652);
        if ( *(_BYTE *)(this + 664) )
          *(_DWORD *)(this + 636) = v13;
        else
          *(_DWORD *)(this + 636) = v14;
      }
    }
    if ( rf_mouse_get_button_held_byte(0)
      && rf_ui_gadget_is_owner_hover_target((_DWORD *)this)
      && rf_clock_deadline_has_elapsed_half_period((int *)(this + 628)) )
    {
      rf_clock_deadline_set_wrapped_offset((int *)(this + 628), 150);
      v10 = 1;
    }
    if ( v10 && rf_ui_gadget_is_owner_hover_target((_DWORD *)this) )
    {
      if ( *(_DWORD *)(this + 632) == 3 )
        *(_DWORD *)(this + 652) -= *(_DWORD *)(this + 660);
      if ( *(_DWORD *)(this + 632) == 2 )
        *(_DWORD *)(this + 652) += *(_DWORD *)(this + 660);
    }
    if ( *(_DWORD *)(this + 632) == 1 )
    {
      if ( *(_BYTE *)(this + 664) )
      {
        v4 = v13 - *(_DWORD *)(this + 636);
        v7 = *(_DWORD *)(this + 20) - *(_DWORD *)(this + 656);
      }
      else
      {
        v4 = v14 - *(_DWORD *)(this + 636);
        v7 = *(_DWORD *)(this + 24) - *(_DWORD *)(this + 656);
      }
      if ( v7 )
      {
        v5 = v4 * (*(_DWORD *)(this + 648) - 1);
        if ( v5 >= 0 )
          v6 = v5 + v7 / 2;
        else
          v6 = v5 - v7 / 2;
        *(_DWORD *)(this + 652) = *(_DWORD *)(this + 640) + v6 / v7;
      }
    }
    if ( *(_DWORD *)(this + 632) == 1 && unk_1CF7590 )
    {
      *(_DWORD *)(this + 632) = 0;
      *(_DWORD *)(this + 652) = *(_DWORD *)(this + 640);
    }
    if ( !rf_mouse_get_button_held_byte(0) )
      *(_DWORD *)(this + 632) = 0;
    return v15;
  }
}

