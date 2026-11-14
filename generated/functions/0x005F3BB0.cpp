// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F3BB0 rf_ui_inputbox_process_input
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Hidden returns code;blocked gives feedback sound4 on hovered primary press then returns. Hovered primary press takes global keyboard focus. Only globally focused object handles nonzero key:emits virtual+4 event20,arg-99999 before dispatch. Escape1 clears text unless flag2 Ignore esc;Home199 always clears;both emit21 when clearing,consume. Backspace14,Left203,Delete211 all remove LAST byte (no caret);empty gives sound5,nonempty emits21. Enter28 consumed without21. Other codes with mask0x6000 consumed;otherwise keypad conversion0x5F39E0,0/255 ignored+consumed. Reject-character helper returning0 leaves original code UNCONSUMED. Accepted char at signed length>=max1408 emits22,consumes;otherwise builds tentative text in256-byte stack buffer with no hard256 cap,measures(font1400),flag4 No scroll
// rejects measuredWidth>width20-cursorWidth1432-2*margin1420 with event22;success unbounded copies to632 and emits21. Returns0 for handled/default-invalid paths. No post-callback lifetime or buffer-capacity protection;focused code0 returns0.
int __thiscall rf_ui_inputbox_process_input(int this, int a2)
{
  int result; // eax
  unsigned __int8 v3; // [esp+3h] [ebp-185h]
  _BYTE *v4; // [esp+8h] [ebp-180h]
  unsigned __int8 *v5; // [esp+Ch] [ebp-17Ch]
  unsigned __int8 v6; // [esp+33h] [ebp-155h]
  unsigned __int8 *v7; // [esp+38h] [ebp-150h]
  unsigned __int8 *v8; // [esp+3Ch] [ebp-14Ch]
  unsigned __int8 v10[256]; // [esp+78h] [ebp-110h] BYREF
  int v11; // [esp+17Ch] [ebp-Ch]
  int v12; // [esp+180h] [ebp-8h] BYREF
  int v13; // [esp+184h] [ebp-4h] BYREF

  if ( (*(unsigned __int8 (__thiscall **)(int))(*(_DWORD *)this + 16))(this) )
    return a2;
  if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
  {
    if ( unk_1CF7593 )
    {
      if ( rf_ui_gadget_is_owner_hover_target((_DWORD *)this) )
        rf_ui_play_feedback_sound(4);
    }
    return a2;
  }
  else
  {
    if ( unk_1CF7593 && rf_ui_gadget_is_owner_hover_target((_DWORD *)this) )
      rf_ui_gadget_take_keyboard_focus((_DWORD *)this);
    if ( dword_1CF75D8 == (_DWORD *)this )
    {
      if ( a2 )
      {
        (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 20, -99999);
        switch ( a2 )
        {
          case 1:
            if ( (*(_DWORD *)(this + 628) & 2) != 0 )
              goto LABEL_37;
            goto LABEL_20;
          case 14:
          case 203:
          case 211:
            if ( this + 632 + strlen((const char *)(this + 632)) + 1 == this + 633 )
            {
              rf_ui_play_feedback_sound(5);
            }
            else
            {
              *(_BYTE *)(this + strlen((const char *)(this + 632)) + 631) = 0;
              (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 21, -99999);
            }
            goto LABEL_37;
          case 28:
            goto LABEL_37;
          case 199:
LABEL_20:
            *(_BYTE *)(this + 632) = 0;
            (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 21, -99999);
            goto LABEL_37;
          default:
            if ( (a2 & 0x6000) != 0 )
              goto LABEL_37;
            v11 = rf_ui_inputbox_keycode_to_character_with_keypad(a2);
            if ( !v11 || v11 == 255 )
              goto LABEL_37;
            if ( rf_ui_inputbox_accept_character(this, v11) )
            {
              if ( (signed int)strlen((const char *)(this + 632)) >= *(_DWORD *)(this + 1408) )
              {
                (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 22, -99999);
              }
              else
              {
                v8 = (unsigned __int8 *)(this + 632);
                v7 = v10;
                do
                {
                  v6 = *v8;
                  *v7++ = *v8++;
                }
                while ( v6 );
                v10[strlen((const char *)(this + 632))] = v11;
                v10[strlen((const char *)(this + 632)) + 1] = 0;
                rf_font_measure_text_extent(&v13, &v12, v10, -1, *(_DWORD *)(this + 1400));
                if ( (*(_DWORD *)(this + 628) & 4) != 0
                  && v13 > *(_DWORD *)(this + 20) - *(_DWORD *)(this + 1432) - 2 * *(_DWORD *)(this + 1420) )
                {
                  (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 22, -99999);
                }
                else
                {
                  v5 = v10;
                  v4 = (_BYTE *)(this + 632);
                  do
                  {
                    v3 = *v5;
                    *v4++ = *v5++;
                  }
                  while ( v3 );
                  (*(void (__thiscall **)(int, int, int))(*(_DWORD *)this + 4))(this, 21, -99999);
                }
              }
LABEL_37:
              result = 0;
            }
            else
            {
              result = a2;
            }
            break;
        }
      }
      else
      {
        return 0;
      }
    }
    else
    {
      return a2;
    }
  }
  return result;
}

