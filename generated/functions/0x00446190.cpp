// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446190 rf_ui_panel_stack_current_id
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, fullEAX. Signed depth6615F8>=0 returns raw DWORD[6E6DE8+4*depth]; every negative depth returns0. No upper bounds,
// panel-ID validation, session-handle resolution, mutation or normalization. Reads CURRENT panel slot, unlike446170 previous-slot getter.
int __cdecl rf_ui_panel_stack_current_id()
{
  if ( dword_6615F8 <= -1 )
    return 0;
  else
    return unk_6E6DE8[dword_6615F8];
}

