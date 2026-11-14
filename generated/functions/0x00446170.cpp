// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446170 rf_ui_panel_stack_previous_id
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments, fullEAX. Signed depth6615F8>0 returns raw DWORD[6E6DE4+4*depth], exactly stack6E6DE8[depth-1]. Depth<=0 returns0.
// This is PREVIOUS panel ID, not a current active-game session handle: adjacent446190 reads current stack[depth],4462F0 pushes/pops the same array, and4461C0 uses this previous slot
// as close-transition destination. No upper depth/ID check, dereference, normalization or mutation. Corrected old misleading function name and repeatable comment.
int rf_ui_panel_stack_previous_id()
{
  if ( dword_6615F8 <= 0 )
    return 0;
  else
    return dword_6E6DE4[dword_6615F8];
}

