// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058A760 rf_mouse_window_message_callback
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, mouse/window writers, frame snapshots and constructor callers): Maps messages513/514 to left button down/up,516/517 to right,519/520 to middle, passing raw0/1 transitions to58AA10. Message522 (wheel) adds SIGNED high word of wParam to cumulative message wheel193A05C under critical section, without dividing by120. Other messages, including native double-click messages, ignored; double clicks are timed by RF. No local initialized guard on wheel path, while button helper has one.
void __cdecl rf_mouse_window_message_callback(int a1, int a2)
{
  switch ( a1 )
  {
    case 513:
      rf_mouse_record_button_transition(0, 1);
      break;
    case 514:
      rf_mouse_record_button_transition(0, 0);
      break;
    case 516:
      rf_mouse_record_button_transition(1, 1);
      break;
    case 517:
      rf_mouse_record_button_transition(1, 0);
      break;
    case 519:
      rf_mouse_record_button_transition(2, 1);
      break;
    case 520:
      rf_mouse_record_button_transition(2, 0);
      break;
    case 522:
      EnterCriticalSection(&unk_193A044);
      dword_193A05C += SHIWORD(a2);
      LeaveCriticalSection(&unk_193A044);
      break;
    default:
      return;
  }
}

