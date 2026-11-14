// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004461C0 rf_ui_process_panel_transition_and_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, fullEAX captured current/new panelID. Capture oldID=stack6E6DE8[depth] if signed depth>=0, else0. Enter
// transition branch ONLY when pendingID ANY nonzero OR popBYTE ANY nonzero. Within it, if close-issued6E6E28==0, call4F0EE0(oldID,pop?raw previous slot6E6DE4[depth]:pendingID,BYTE0),
// then set latch1 AFTER callback. No lower-depth guard for previous-slot read. Still within that request branch, query4F1120(oldID); ANY nonzeroAL clears latch0, commits4462F0,
// captures returned newID, initializes4F0D70(newID,oldID). Delegate failures/state mutations are not rolled back or re-gated. Next query modal raw active46F8A0: ANY nonzero disables
// mouse centering, recursively frames CURRENT global depth with BYTE1, then runs ONE modal frame46F520. Inactive: unconditionally read current stack slot even for negative depth;
// only exactID11 permits centering, then frame CURRENT re-read depth with BYTE0 regardless of ID. No blanket inactive centering disable, valid-depth/capacity/NULL guards, snapshot of
// globals across callbacks or modal recheck after panel frame. Return captured ID from before these later frame/modal effects, not necessarily final global current ID.
int rf_ui_process_panel_transition_and_frame()
{
  int v1; // [esp+0h] [ebp-Ch]
  int v2; // [esp+8h] [ebp-4h]

  if ( dword_6615F8 >= 0 )
    v1 = unk_6E6DE8[dword_6615F8];
  else
    v1 = 0;
  v2 = v1;
  if ( dword_6E6DE0 || unk_6E6DDF )
  {
    if ( !unk_6E6E28 )
    {
      if ( unk_6E6DDF )
        rf_ui_dispatch_panel_begin_close(v1, dword_6E6DE4[dword_6615F8], 0);
      else
        rf_ui_dispatch_panel_begin_close(v1, dword_6E6DE0, 0);
      unk_6E6E28 = 1;
    }
    if ( rf_ui_panel_close_transition_is_ready(v1) )
    {
      unk_6E6E28 = 0;
      v2 = rf_ui_panel_stack_commit_transition();
      rf_ui_dispatch_panel_initialize(v2, v1);
    }
  }
  if ( rf_ui_modal_active_byte_get() )
  {
    rf_mouse_set_centering_disabled(1);
    rf_ui_run_panel_stack_frames_recursive(dword_6615F8, 1);
    rf_ui_modal_run_single_frame();
  }
  else
  {
    if ( unk_6E6DE8[dword_6615F8] == 11 )
      rf_mouse_set_centering_disabled(0);
    rf_ui_run_panel_stack_frames_recursive(dword_6615F8, 0);
  }
  return v2;
}

