// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00594370 rf_window_message_procedure
// UNREALRED VERIFIED [system-progress-20261028]: stdcall HWND,Msg,wParam,lParam. First invokes all registered observer callbacks from0x1BC2010 count0x1BC2144 with(Msg,wParam,lParam),ignoring their results. Messages2,0x10,0x12 set quit flag0x1BC213C and return0,without DestroyWindow/PostQuitMessage here. WM_ACTIVATE6 and WM_ACTIVATEAPP0x1C update BYTE0x1BC2134; on state transition set stored thread0x1BC2130 priority2 active,0 inactive. Swallows0x7E,0x104,0x105,0x113,0x310,0x311;0x30F returns1. WM_SYSCOMMAND0x112 formats unused diagnostic,swallows exact0xF040/0xF050; exact0xF140 follows paint path. Paint0xF and that path increment0x180A494 in windowed mode. Default processing suppressed while input state index56 or184 is nonzero; otherwise calls DefWindowProcA. Comparisons use exact command DWORDs without masking low bits. No BeginPaint/EndPaint here.
int __stdcall rf_window_message_procedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  int result; // eax
  unsigned __int8 v5; // [esp+Bh] [ebp-111h]
  char Buffer[260]; // [esp+Ch] [ebp-110h] BYREF
  int v7; // [esp+114h] [ebp-8h]
  int *v8; // [esp+118h] [ebp-4h]

  v8 = unk_1BC2010;
  v7 = 0;
  while ( v7 < unk_1BC2144 )
  {
    ((void (__cdecl *)(UINT, WPARAM, LPARAM))*v8)(Msg, wParam, lParam);
    ++v7;
    ++v8;
  }
  if ( Msg <= 0x7E )
  {
    if ( Msg != 126 )
    {
      switch ( Msg )
      {
        case 2u:
        case 0x10u:
        case 0x12u:
          unk_1BC213C = 1;
          return 0;
        case 6u:
        case 0x1Cu:
          v5 = byte_1BC2134[0];
          if ( Msg == 6 )
            byte_1BC2134[0] = (unsigned __int16)wParam == 1 || (unsigned __int16)wParam == 2;
          else
            byte_1BC2134[0] = wParam != 0;
          if ( v5 != byte_1BC2134[0] )
          {
            if ( byte_1BC2134[0] )
              SetThreadPriority(MEMORY[0x1BC2130], 2);
            else
              SetThreadPriority(MEMORY[0x1BC2130], 0);
          }
          return 0;
        case 0xFu:
          goto LABEL_35;
        default:
          goto LABEL_41;
      }
    }
    return 0;
  }
  if ( Msg > 0x30F )
  {
    if ( Msg != 784 && Msg != 785 )
    {
LABEL_41:
      if ( !rf_input_get_scan_code_state_byte(56) && !rf_input_get_scan_code_state_byte(184) )
        return DefWindowProcA(hWnd, Msg, wParam, lParam);
    }
    return 0;
  }
  if ( Msg == 783 )
    return 1;
  switch ( Msg )
  {
    case 0x104u:
    case 0x105u:
    case 0x113u:
      return 0;
    case 0x112u:
      sprintf(Buffer, "Sys command called '%d'\n", wParam);
      if ( wParam == 61504 || wParam == 61520 )
        return 0;
      if ( wParam != 61760 )
        goto LABEL_39;
LABEL_35:
      if ( unk_1BC2140 )
        ++unk_180A494;
      if ( rf_input_get_scan_code_state_byte(56) || rf_input_get_scan_code_state_byte(184) )
        return 0;
LABEL_39:
      result = DefWindowProcA(hWnd, Msg, wParam, lParam);
      break;
    default:
      goto LABEL_41;
  }
  return result;
}

