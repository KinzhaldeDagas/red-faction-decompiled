// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046F520 rf_ui_modal_run_single_frame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, history/modal/upsell control chains, original layout/duration constants and native signed/x87/stack/callback
// ABI): Single modal frame, NOT a blocking activation loop. If active, invokes virtual+8 on EVERY focus-list control including disabled controls, ECX=this/no explicit arguments.
// Polls/dispatches event(handler46F5C0,0), then mouse46EAD0, then current focused virtual+4 with no arguments, then modal render46EF60. Does not recheck active/focus validity between
// keyboard, pointer callbacks and focused virtual call; callbacks may clear/create a modal. Inactive entry returns immediately.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Reverified no-argument modal SINGLE-FRAME procedure and caller4461C0. Entry zero-extends raw activeBYTE6F8C84 intoEAX;0 returns
// fullEAX0. ANY nonzero walks signed index0..<LIVE firstDWORD count of focus-list6F8F84, re-reading count each condition; unchecked inline accessor416F70 yields each control and
// virtual+8 is called with ECX control/no stack arguments, including disabled controls. Then4477F0 is supplied TWO raw caller slots(handler46F5C0,0), caller pops8; calls46EAD0
// pointer handling; reads CURRENT global focus6F8C80, gets CURRENT list entry unchecked, invokes virtual+4 with ECX control and NO explicit stack argument (extra pointer in
// pseudocode is an inferred virtual-signature artifact), then46EF60 render. No active/focus/count recheck between keyboard, mouse and focused callback, no snapshot across callbacks,
// focus installation, activation loop or cancellation guard. Active-path return follows render-helper EAX; not normalized success. Existing detailed single-frame contract remains
// valid; replaced stale repeatable activation claim and misleading function name.
int rf_ui_modal_run_single_frame()
{
  int result; // eax
  _DWORD *v1; // eax
  _DWORD *v2; // eax
  int i; // [esp+8h] [ebp-4h]

  result = unk_6F8C84;
  if ( unk_6F8C84 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword(unk_6F8F84); ++i )
    {
      v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, i);
      (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*v1 + 8))(*v1);
    }
    rf_ui_poll_and_dispatch_event(rf_ui_modal_handle_input);
    rf_ui_modal_process_pointer();
    v2 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(unk_6F8F84, unk_6F8C80);
    (*(void (__thiscall **)(_DWORD, _DWORD))(*(_DWORD *)*v2 + 4))(*v2, *v2);
    return rf_ui_modal_render();
  }
  return result;
}

