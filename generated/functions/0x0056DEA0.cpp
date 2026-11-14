// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056DEA0 rf_console_process_input_event
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl NO arguments; callee-saved registers not input parameters. Dequeues one event,increments dirty counter if event>0,clears bit8000. Codes1/41 close console only when press-count>0 and animation flag false;14 backspaces;15 completes command;28 commits displayed prompt with LF and executes input. Only successful dispatch0 enters8-slot history:append at incremented last-index until7,then shifts slots1..7 down and stores latest at7;clears input/cursor/navigation and attempts history save.61 recalls latest;200/208 cycle history;201/209 scroll output by16 with500-slot wrapping;207 returns live tail;199 leaves line unchanged. Clipboard codes4306/16431 fetch at most127 bytes into128B local,append
// ASCII<128 printable non-CR/LF bytes WITHOUT checking remaining256B input capacity. Ordinary key translation rejectsFF and requires strlen(input)<253 before one append. Clipboard/completion can exceed that limit. Always rebuilds prompt180A4A0 via unbounded sprintf("] %s",input),returns incidental sprintf count. Stored input cursor180A48C/history index180A490 must remain consistent;no locks.
int __cdecl rf_console_process_input_event()
{
  signed int v0; // kr04_4
  char v2; // [esp+23h] [ebp-12Dh]
  char *v3; // [esp+28h] [ebp-128h]
  char *v4; // [esp+2Ch] [ebp-124h]
  char v5; // [esp+33h] [ebp-11Dh]
  char *v6; // [esp+38h] [ebp-118h]
  char *v7; // [esp+3Ch] [ebp-114h]
  char v8; // [esp+43h] [ebp-10Dh]
  char *v9; // [esp+48h] [ebp-108h]
  char *v10; // [esp+4Ch] [ebp-104h]
  char v11; // [esp+63h] [ebp-EDh]
  _BYTE *v12; // [esp+68h] [ebp-E8h]
  char *v13; // [esp+6Ch] [ebp-E4h]
  char v14; // [esp+83h] [ebp-CDh]
  _BYTE *v15; // [esp+88h] [ebp-C8h]
  char *v16; // [esp+8Ch] [ebp-C4h]
  char v17; // [esp+A3h] [ebp-ADh]
  _BYTE *v18; // [esp+A8h] [ebp-A8h]
  char *v19; // [esp+ACh] [ebp-A4h]
  unsigned __int8 v20; // [esp+B7h] [ebp-99h]
  signed int j; // [esp+BCh] [ebp-94h]
  char v22[128]; // [esp+C0h] [ebp-90h] BYREF
  int i; // [esp+144h] [ebp-Ch]
  int v24; // [esp+148h] [ebp-8h]
  int v25; // [esp+14Ch] [ebp-4h]

  v25 = rf_input_dequeue_event();
  if ( v25 > 0 )
    ++unk_180A494;
  v25 &= ~0x8000u;
  if ( v25 > 4306 )
  {
    if ( v25 != 16431 )
    {
LABEL_72:
      v20 = rf_input_keycode_to_character(v25);
      if ( v20 != 255 && strlen((const char *)&unk_180A2C0) < 0xFD )
      {
        *((_BYTE *)&unk_180A2C0 + dword_180A48C++) = v20;
        *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
      }
      return sprintf((char *const)&unk_180A4A0, "] %s", (const char *)&unk_180A2C0);
    }
  }
  else if ( v25 != 4306 )
  {
    switch ( v25 )
    {
      case 1:
      case 41:
        if ( rf_input_take_press_count(v25) > 0 && !rf_console_get_animation_byte() )
          rf_console_begin_close_animation_and_reset_input();
        break;
      case 14:
        if ( dword_180A48C > 0 )
        {
          --dword_180A48C;
          *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
        }
        break;
      case 15:
        rf_console_complete_unique_longer_command_prefix();
        break;
      case 28:
        rf_console_prompt_append_character_or_commit_line(10);
        if ( !rf_console_execute_command_line((const char *)&unk_180A2C0) )
        {
          v24 = 0;
          if ( dword_663EE4 >= 7 )
          {
            for ( i = 0; i < dword_663EE4; ++i )
            {
              v7 = &unk_1809AC0[256 * i + 256];
              v6 = &unk_1809AC0[256 * i];
              do
              {
                v5 = *v7;
                *v6++ = *v7++;
              }
              while ( v5 );
            }
            v4 = (char *)&unk_180A2C0;
            v3 = &unk_1809AC0[256 * dword_663EE4];
            do
            {
              v2 = *v4;
              *v3++ = *v4++;
            }
            while ( v2 );
          }
          else
          {
            ++dword_663EE4;
            v10 = (char *)&unk_180A2C0;
            v9 = &unk_1809AC0[256 * dword_663EE4];
            do
            {
              v8 = *v10;
              *v9++ = *v10++;
            }
            while ( v8 );
          }
          dword_180A48C = 0;
          unk_180A2C0 = 0;
          dword_180A490 = 0;
          rf_console_history_save_if_enabled();
        }
        break;
      case 61:
        if ( dword_663EE4 > -1 )
        {
          v19 = &unk_1809AC0[256 * dword_663EE4];
          v18 = &unk_180A2C0;
          do
          {
            v17 = *v19;
            *v18++ = *v19++;
          }
          while ( v17 );
          dword_180A48C = (_UNKNOWN *)((char *)&unk_180A2C0 + strlen((const char *)&unk_180A2C0) + 1) - &unk_180A2C1;
          *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
        }
        break;
      case 199:
        return sprintf((char *const)&unk_180A4A0, "] %s", (const char *)&unk_180A2C0);
      case 200:
        if ( --dword_180A490 < 0 )
          dword_180A490 = dword_663EE4;
        if ( dword_180A490 > -1 )
        {
          v16 = &unk_1809AC0[256 * dword_180A490];
          v15 = &unk_180A2C0;
          do
          {
            v14 = *v16;
            *v15++ = *v16++;
          }
          while ( v14 );
          dword_180A48C = (_UNKNOWN *)((char *)&unk_180A2C0 + strlen((const char *)&unk_180A2C0) + 1) - &unk_180A2C1;
          *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
        }
        break;
      case 201:
        if ( dword_1809ABC == -1 )
        {
          dword_1809ABC = dword_1809920 - 18;
          dword_1809ABC += dword_1809ABC < 0 ? 0x1F4 : 0;
        }
        else
        {
          dword_1809ABC -= 16;
          if ( dword_1809ABC < 0 )
            dword_1809ABC = 499;
        }
        break;
      case 207:
        dword_1809ABC = -1;
        break;
      case 208:
        if ( ++dword_180A490 > dword_663EE4 )
          dword_180A490 = 0;
        if ( dword_180A490 > dword_663EE4 )
          dword_180A490 = -1;
        if ( dword_180A490 > -1 )
        {
          v13 = &unk_1809AC0[256 * dword_180A490];
          v12 = &unk_180A2C0;
          do
          {
            v11 = *v13;
            *v12++ = *v13++;
          }
          while ( v11 );
          dword_180A48C = (_UNKNOWN *)((char *)&unk_180A2C0 + strlen((const char *)&unk_180A2C0) + 1) - &unk_180A2C1;
          *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
        }
        break;
      case 209:
        if ( dword_1809ABC >= 0 )
        {
          dword_1809ABC += 16;
          if ( dword_1809ABC >= 500 )
            dword_1809ABC = 0;
          if ( dword_1809ABC == dword_1809920 )
            dword_1809ABC = -1;
        }
        break;
      default:
        goto LABEL_72;
    }
    return sprintf((char *const)&unk_180A4A0, "] %s", (const char *)&unk_180A2C0);
  }
  rf_clipboard_copy_ansi_text(v22, 127);
  v0 = strlen(v22);
  for ( j = 0; j < v0; ++j )
  {
    if ( (unsigned int)v22[j] < 0x80 && v22[j] != 10 && v22[j] != 13 && isprint(v22[j]) )
    {
      *((_BYTE *)&unk_180A2C0 + dword_180A48C++) = v22[j];
      *((_BYTE *)&unk_180A2C0 + dword_180A48C) = 0;
    }
  }
  return sprintf((char *const)&unk_180A4A0, "] %s", (const char *)&unk_180A2C0);
}

