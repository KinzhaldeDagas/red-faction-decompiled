// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EF190 rf_ui_button_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall button,input key code;returns code unless consumed to0. State632 transitions:0idle,1key flash deadline100ms,2primary held,3secondary held,4active drag,5drop target,6primary activation,7secondary activation,8primary double,9secondary double. At entry6/7 become corresponding held state only when physical button held and repeat flag2;otherwise0;8/9 reset0. Hidden returns code after these resets. Blocked emits feedback sound2 on hover press(primary or secondary allowed flag0x400),or matching bound key;returns code. Idle bound key (unless global keyboard focus type6) or navigation-target Enter28 starts key deadline+896 offset100,state1,code0. Hover prioritizes primary double,secondary double(flag400),primary press,secondary press(flag400),then acceptable drag. Press captures global mouse
// x/y into900/904;repeat mode sets deadline892 offset450 and immediately activates6/7,otherwiseheld2/3. Held-hover release activates unless repeat (thenidle);repeat deadlines thereafter150ms. Primary held away starts drag only flag10,offer-mask1076!=0 and(capacity1088<0 or count1084>=amount1092);stores global source. Drop-target state5 on primary release sets globaltarget1CF75D4=this,adds source amount to target count iff targetcapacity>=0,emits17,target;subtracts amount from source count iff sourcecapacity>=0,emits16,source;sets1CF75C7=1,clears source,state0. Activation6/7 invokes0x5EEFF0;double8/9 emits14/15,arg-99999. Processes transitions until v4 cleared;unknown state outside0..9 has no escape from switch loop. Timers use wrapped clock helpers;callback mutation/lifetime not protected.
int __thiscall rf_ui_button_process_input(int *this, int a2)
{
  char v4; // [esp+Bh] [ebp-1h]

  v4 = 1;
  switch ( *(this + 158) )
  {
    case 6:
      if ( rf_mouse_get_button_held_byte(0) && (*(this + 157) & 2) != 0 )
        *(this + 158) = 2;
      else
        *(this + 158) = 0;
      break;
    case 7:
      if ( rf_mouse_get_button_held_byte(1) && (*(this + 157) & 2) != 0 )
        *(this + 158) = 3;
      else
        *(this + 158) = 0;
      break;
    case 8:
    case 9:
      *(this + 158) = 0;
      break;
  }
  if ( (*(unsigned __int8 (__thiscall **)(int *))(*this + 16))(this) )
    return a2;
  if ( rf_ui_gadget_is_interaction_blocked(this) )
  {
    if ( (unk_1CF7593 || (*(this + 157) & 0x400) != 0 && unk_1CF7590) && rf_ui_gadget_is_owner_hover_target(this) )
      rf_ui_play_feedback_sound(2);
    if ( rf_ui_gadget_matches_bound_key(this, a2) )
      rf_ui_play_feedback_sound(2);
    return a2;
  }
  else
  {
    while ( v4 )
    {
      switch ( *(this + 158) )
      {
        case 0:
          if ( (!dword_1CF75D8 || rf_ui_gadget_get_type(dword_1CF75D8) != 6) && rf_ui_gadget_matches_bound_key(this, a2)
            || rf_ui_gadget_is_owner_navigation_target(this) && a2 == 28 )
          {
            rf_clock_deadline_set_wrapped_offset(this + 224, 100);
            *(this + 158) = 1;
            a2 = 0;
          }
          else if ( rf_ui_gadget_is_owner_hover_target(this) )
          {
            if ( unk_1CF75C4 )
            {
              *(this + 158) = 8;
            }
            else if ( (*(this + 157) & 0x400) != 0 && unk_1CF75C5 )
            {
              *(this + 158) = 9;
            }
            else if ( unk_1CF7593 )
            {
              *(this + 225) = dword_1CF7594;
              *(this + 226) = dword_1CF75C0;
              if ( (*(this + 157) & 2) != 0 )
              {
                rf_clock_deadline_set_wrapped_offset(this + 223, 450);
                *(this + 158) = 6;
              }
              else
              {
                *(this + 158) = 2;
              }
            }
            else if ( (*(this + 157) & 0x400) != 0 && unk_1CF7590 )
            {
              *(this + 225) = dword_1CF7594;
              *(this + 226) = dword_1CF75C0;
              if ( (*(this + 157) & 2) != 0 )
              {
                rf_clock_deadline_set_wrapped_offset(this + 223, 450);
                *(this + 158) = 7;
              }
              else
              {
                *(this + 158) = 3;
              }
            }
            else if ( rf_ui_button_can_accept_active_drag(this) )
            {
              *(this + 158) = 5;
            }
            else
            {
              v4 = 0;
            }
          }
          else
          {
            v4 = 0;
          }
          break;
        case 1:
          if ( rf_clock_deadline_has_elapsed_half_period(this + 224) )
            *(this + 158) = 6;
          else
            v4 = 0;
          break;
        case 2:
          if ( rf_ui_gadget_is_owner_hover_target(this) )
          {
            if ( unk_1CF7591 )
            {
              if ( (*(this + 157) & 2) != 0 )
                *(this + 158) = 0;
              else
                *(this + 158) = 6;
            }
            else if ( (*(this + 157) & 2) != 0 )
            {
              if ( rf_clock_deadline_has_elapsed_half_period(this + 223) )
              {
                rf_clock_deadline_set_wrapped_offset(this + 223, 150);
                *(this + 158) = 6;
              }
              else
              {
                v4 = 0;
              }
            }
            else
            {
              v4 = 0;
            }
          }
          else if ( unk_1CF7591 )
          {
            *(this + 158) = 0;
          }
          else if ( (*(this + 157) & 0x10) != 0
                 && *(this + 269)
                 && (*(this + 272) < 0 || *(this + 271) >= *(this + 273)) )
          {
            *(this + 158) = 4;
            dword_1CF75D0 = (char *)this;
          }
          else
          {
            v4 = 0;
          }
          break;
        case 3:
          if ( rf_ui_gadget_is_owner_hover_target(this) )
          {
            if ( unk_1CF7592 )
            {
              if ( (*(this + 157) & 2) != 0 )
                *(this + 158) = 0;
              else
                *(this + 158) = 7;
            }
            else if ( (*(this + 157) & 2) != 0 )
            {
              if ( rf_clock_deadline_has_elapsed_half_period(this + 223) )
              {
                rf_clock_deadline_set_wrapped_offset(this + 223, 150);
                *(this + 158) = 7;
              }
              else
              {
                v4 = 0;
              }
            }
            else
            {
              v4 = 0;
            }
          }
          else if ( unk_1CF7592 )
          {
            *(this + 158) = 0;
          }
          else
          {
            v4 = 0;
          }
          break;
        case 4:
          if ( unk_1CF7591 )
            *(this + 158) = 0;
          else
            v4 = 0;
          break;
        case 5:
          if ( rf_ui_gadget_is_owner_hover_target(this) )
          {
            if ( unk_1CF7591 )
            {
              unk_1CF75D4 = this;
              if ( *(this + 272) >= 0 )
                *(this + 271) += *((_DWORD *)dword_1CF75D0 + 273);
              (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 17, -99999);
              if ( *((int *)dword_1CF75D0 + 272) >= 0 )
                *((_DWORD *)dword_1CF75D0 + 271) -= *((_DWORD *)dword_1CF75D0 + 273);
              (*(void (__thiscall **)(char *, int, int))(*(_DWORD *)dword_1CF75D0 + 4))(dword_1CF75D0, 16, -99999);
              unk_1CF75C7 = 1;
              dword_1CF75D0 = nullptr;
              *(this + 158) = 0;
            }
            else
            {
              v4 = 0;
            }
          }
          else
          {
            *(this + 158) = 0;
          }
          break;
        case 6:
          rf_ui_button_emit_click(this, 0);
          v4 = 0;
          break;
        case 7:
          rf_ui_button_emit_click(this, 1);
          v4 = 0;
          break;
        case 8:
          (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 14, -99999);
          v4 = 0;
          break;
        case 9:
          (*(void (__thiscall **)(int *, int, int))(*this + 4))(this, 15, -99999);
          v4 = 0;
          break;
        default:
          continue;
      }
    }
    return a2;
  }
}

