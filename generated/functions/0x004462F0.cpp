// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004462F0 rf_ui_panel_stack_commit_transition
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. Push BYTE6E6DDE ANY nonzero has precedence: increment wrapped global depth6615F8 FIRST, then store raw
// pending6E6DE0 into stack6E6DE8[depth]. Otherwise popBYTE ANY nonzero decrements depth without empty guard. Otherwise replacement: decrement depth to discard old current level;
// while live signed depth>-1, capture stack[depth], decrement global depth BEFORE4F0EE0(capturedID,FRESH pendingID,BYTE1), and re-read depth at next condition. Then set depth0 and
// stack[0]=FRESH pendingID. Every branch next clears pendingDWORD, pushBYTE,popBYTE; if CURRENT depth==0, clear ONLY first per-panel flag byte6E6D98+2*stack[0], retaining second
// byte. Finally return raw stack[CURRENT depth] fullEAX, with no negative/capacity/ID guard (underflow reads adjacent storage). No own close-ready poll/init/frame or rollback.
// Callback mutations of pending/depth participate literally in remaining loop and final stores; no saved original stack snapshot.
int rf_ui_panel_stack_commit_transition()
{
  int v1; // [esp+0h] [ebp-4h]

  if ( unk_6E6DDE )
  {
    unk_6E6DE8[++dword_6615F8] = dword_6E6DE0;
  }
  else if ( unk_6E6DDF )
  {
    --dword_6615F8;
  }
  else
  {
    --dword_6615F8;
    while ( dword_6615F8 > -1 )
    {
      v1 = unk_6E6DE8[dword_6615F8--];
      rf_ui_dispatch_panel_begin_close(v1, dword_6E6DE0, 1);
    }
    dword_6615F8 = 0;
    unk_6E6DE8[0] = dword_6E6DE0;
  }
  dword_6E6DE0 = 0;
  unk_6E6DDE = 0;
  unk_6E6DDF = 0;
  if ( !dword_6615F8 )
    LOBYTE(unk_6E6D98[unk_6E6DE8[0]]) = 0;
  return unk_6E6DE8[dword_6615F8];
}

