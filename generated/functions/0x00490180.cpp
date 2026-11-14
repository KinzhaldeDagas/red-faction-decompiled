// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490180 rf_multiplayer_client_timeout_warning_update
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl no arguments. Only mode EXACT1,authority0 AND deadline704F0C armed enters update. Clears stalled DWORD704E90=0 first. If timer elapsed,sets stalled1; if warning
// latchBYTE704BD9==0 and signed timer elapsed_ms>=20000,shows two-choice localized timeout modal(title88E1AC,body88E1B0,labels88E1A4/88E1A8,callback
// table662880,metadata0,flags0),then sets latch1 REGARDLESS modal acceptance/result. If armed timer not elapsed,clears latch0. Disarmed or inadmissible mode leaves BOTH globals
// unchanged. No timer rearm,network send or teardown in this body; return AL incidental,not timeout Boolean.
char rf_multiplayer_client_timeout_warning_update()
{
  int v0; // eax
  _DWORD v2[2]; // [esp+10h] [ebp-8h] BYREF

  LOBYTE(v0) = rf_multiplayer_runtime_mode;
  if ( rf_multiplayer_runtime_mode == 1 && !rf_multiplayer_server_authority )
  {
    LOBYTE(v0) = rf_replicator_is_armed(&unk_704F0C);
    if ( (_BYTE)v0 )
    {
      unk_704E90 = 0;
      LOBYTE(v0) = rf_replicator_has_elapsed(&unk_704F0C);
      if ( (_BYTE)v0 )
      {
        unk_704E90 = 1;
        if ( !unk_704BD9 )
        {
          v0 = rf_timestamp_signed_elapsed_milliseconds(&unk_704F0C);
          if ( v0 >= 20000 )
          {
            v2[0] = unk_88E1A4;
            v2[1] = unk_88E1A8;
            LOBYTE(v0) = rf_ui_show_choice_modal(unk_88E1AC, unk_88E1B0, 2, (int)v2, (int)&unk_662880, 0, 0);
            unk_704BD9 = 1;
          }
        }
      }
      else
      {
        unk_704BD9 = 0;
      }
    }
  }
  return v0;
}

