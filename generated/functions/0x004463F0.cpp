// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004463F0 rf_ui_run_panel_stack_frames_recursive
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(raw depth,LOWBYTE frame option). Snapshot panelID=stack6E6DE8[depth] WITHOUT bounds check. Only first flag
// BYTE6E6D98+2*panelID EXACT1 AND signed depth>0 recurses(depth-1,raw second BYTE6E6D99+2*panelID) FIRST. Other nonzero first flag values do not recurse. Afterwards re-read global
// benchmark status DWORD92DE1C: EXACT1 calls515070(captured panelID), ignoring original frame byte; every other value calls4F11E0(capturedID,zero-extended callerLOWBYTE). PanelID is
// captured before older-frame callbacks; benchmark status is not. No depth/ID/cycle/capacity check, modal activation, transition commit or result normalization. Native saved int is
// delegate/EAX residue, not a per-frame success.
void __cdecl rf_ui_run_panel_stack_frames_recursive(int a1, char a2)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = unk_6E6DE8[a1];
  if ( LOBYTE(unk_6E6D98[v2]) == 1 && a1 > 0 )
    rf_ui_run_panel_stack_frames_recursive(a1 - 1, byte_6E6D99[2 * v2]);
  if ( unk_92DE1C == 1 )
    rf_benchmark_panel_dispatch(v2);
  else
    rf_ui_dispatch_panel_frame(v2, a2);
}

