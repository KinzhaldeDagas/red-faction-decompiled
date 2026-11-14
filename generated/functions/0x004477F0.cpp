// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004477F0 rf_ui_poll_and_dispatch_event
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(optional cdecl callback(event)), one DWORD. Calls window lifecycle no-op and reads active AL; AL0 calls448B30, sleeps1000
// milliseconds, then calls448B20. Polls mouse, then samples console-visible byte ONCE: EXACT AL1 skips the entire input loop, while every other value enters it. Each iteration
// dequeues one event, captures full EAX, clears bytes6EDD3E and6EDD3F, then invokes nonnull callback with the captured event EVEN when it is zero. Callback return never changes
// dispatch decisions. Captured zero exits; captured nonzero calls446190 and ignores its returned panel, then event41 opens console and event183 calls4490B0(NULL); each sets only its
// local captured event0 and STILL continues dequeuing. Other values also continue. The console visibility gate is not re-tested, so callback or event41 mutations do not stop this
// drain. No queue-iteration bound or callback reentrancy/mutation protection; delegates may add further events. Final EAX is path-dependent: visible-gate return, terminating dequeue0
// when no callback, or last callback result when invoked for terminating0; not a dispatched-event count or boolean.
char __cdecl rf_ui_poll_and_dispatch_event(int (__cdecl *a1)(int))
{
  int v1; // eax
  int v3; // [esp+8h] [ebp-4h]

  rf_window_noop_lifecycle_adapter();
  if ( !rf_window_get_active_byte() )
  {
    rf_game_clock_pause_depth_increment_adapter();
    rf_thread_sleep_milliseconds(0x3E8u);
    rf_game_clock_pause_depth_decrement_adapter();
  }
  rf_mouse_poll_frame_snapshot_and_motion();
  LOBYTE(v1) = rf_console_get_visible_byte();
  if ( (unsigned __int8)v1 != 1 )
  {
    while ( 1 )
    {
      v1 = rf_input_dequeue_event();
      v3 = v1;
      unk_6EDD3E = 0;
      unk_6EDD3F = 0;
      if ( a1 )
        LOBYTE(v1) = a1(v1);
      if ( !v3 )
        break;
      rf_ui_panel_stack_current_id();
      if ( v3 == 41 )
      {
        rf_console_begin_open_animation();
      }
      else if ( v3 == 183 )
      {
        rf_screenshot_schedule_first_unresolved_date_path(nullptr);
      }
    }
  }
  return v1;
}

