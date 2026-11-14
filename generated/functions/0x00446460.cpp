// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446460 rf_ui_request_panel_deferred
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): Cdecl(raw panelID,LOWBYTE recursePrevious,LOWBYTE previousFrameOption), EAX=rawID. Unconditionally store
// push6E6DDE=1,pop6E6DDF=0,pending6E6DE0=ID, then raw first argument-byte into flag6E6D98+2*ID and raw second byte into6E6D99+2*ID. First flag is tested EXACT1 by4463F0 to recurse
// older stack frames; second becomes their frame option. No pending-admission/force/range/depth/capacity/close-latch guard or reset; replaces earlier pending state without
// immediately pushing, initializing, closing or framing anything.
int __cdecl rf_ui_request_panel_deferred(int a1, char a2, char a3)
{
  unk_6E6DDE = 1;
  unk_6E6DDF = 0;
  dword_6E6DE0 = a1;
  LOBYTE(unk_6E6D98[a1]) = a2;
  byte_6E6D99[2 * a1] = a3;
  return a1;
}

