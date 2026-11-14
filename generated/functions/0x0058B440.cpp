// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058B440 rf_input_window_message_callback
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scan-state arrays, timestamps and queue control flow): Samples timeGetTime minus GetMessageTime as signed message lag; negative result clamps0. WM_SETFOCUS7 and WM_KILLFOCUS8 reset all RF key/event state. WM_KEYDOWN256/SYSKEYDOWN260 route to key-down helper; KEYUP257/SYSKEYUP261 to key-up helper with wParam,lParam,lag. Other messages ignored. Does not itself hold input lock or emit characters.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): ADDITIONAL VERIFIED data classification: the apparent undecoded keyboard gap is switch data, not another function. Indirect jump at58B485 reads five DWORD destinations starting58B4CC; byte selector table starts58B4E0 and covers messages7..261. Body handles focus7/8 and key256/257/260/261; remaining selectors route to default. Do not decode these table bytes as instructions. Original PE/text-section byte identity verified.
void __cdecl rf_input_window_message_callback(int a1, int a2, int a3)
{
  DWORD Time; // esi
  int v4; // [esp+8h] [ebp-4h]

  Time = timeGetTime();
  v4 = Time - GetMessageTime();
  if ( v4 < 0 )
    v4 = 0;
  switch ( a1 )
  {
    case 7:
    case 8:
      rf_input_reset_all_key_and_event_state();
      break;
    case 256:
    case 260:
      rf_input_handle_windows_key_down(a2, a3, v4);
      break;
    case 257:
    case 261:
      rf_input_handle_windows_key_up(a2, a3, v4);
      break;
    default:
      return;
  }
}

