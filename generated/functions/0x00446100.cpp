// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446100 rf_ui_request_panel_immediate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(raw panelID,LOWBYTE force). Acceptance iff force ANY nonzero OR pending DWORD6E6DE0==0 AND push BYTE6E6DDE==0 AND pop
// BYTE6E6DDF==0. Accepted: store pending=rawID, clear push then pop, clear BOTH bytes at6E6D98+2*ID /6E6D99+2*ID; EAX=rawID, including0/negative. No ID/range/stack-capacity
// validation, close-latch reset, immediate transition or callback. Rejection EAX is NOT uniform: existing nonzero pending forcesEAX0; pending0 with push nonzero can preserve
// incomingEAX because pop is never loaded; pending0/push0/pop nonzero retains zero-extended pop byte. XOR/JNZ back-edges after rejection tests are unreachable, not retries. Per-panel
// writes use raw scaled ID and may address outside intended flags. Refused requests leave state unchanged; accepted ID0 can be indistinguishable from refusal by return alone.
int __cdecl rf_ui_request_panel_immediate(int a1, char a2)
{
  int result; // eax

  if ( unk_6E6DE0 )
  {
    result = 0;
    if ( !a2 )
      return result;
    goto LABEL_7;
  }
  if ( !unk_6E6DDE && (result = unk_6E6DDF, !unk_6E6DDF) || a2 )
  {
LABEL_7:
    unk_6E6DE0 = a1;
    unk_6E6DDE = 0;
    unk_6E6DDF = 0;
    LOBYTE(unk_6E6D98[a1]) = 0;
    byte_6E6D99[2 * a1] = 0;
    return a1;
  }
  return result;
}

