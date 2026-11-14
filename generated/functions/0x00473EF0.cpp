// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00473EF0 rf_object_respawn_apply
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): cdecl(object pointer). NULL skips. Requires common inactive predicate40D190 return AL EXACT1 (predicate checks object+124 bit0x4000);
// invokes in-place reactivate4BC930, then positional gamesound event1 at object+60 with float gain1.0, POINTER17F10B0 and final0, five explicit stack arguments/20-byte cleanup. No
// own multiplayer/authority/timestamp gate, allocation, model replacement or broadcast. Existing event filename note is retained, but native verification here establishes numeric
// event1 and pointer ABI. Reactivation delegate owns emitter/audio/physics side effects.
void __cdecl rf_object_respawn_apply(int a1)
{
  if ( a1 )
  {
    if ( rf_object_has_respawn_inactive_flag(a1) )
    {
      rf_object_reactivate_from_respawn((_DWORD *)a1);
      rf_gamesound_play_positional_event(1, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
    }
  }
}

