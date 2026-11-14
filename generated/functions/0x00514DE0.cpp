// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514DE0 rf_benchmark_start_level_and_reset_stats
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): Cdecl levelPathCString,caller pops4. Construct EMPTY save-path RFString from63F758 and level-path RFString fromargument DIRECTLY as two8-byte by-value stack objects;call4798E0 with16bytes total,callee assigns level/save globals and destroys BOTH temporaries. Former three-int signature was incomplete;shared4798E0 prototype now exposesfour rawDWORD fields for two logicalRFStrings. If multiplayer-mode BYTE nonzero,teardown multiplayer;clear level-state cache. Set benchmark statusDWORD92DE1C=1;F32global max92DDF4,global min92DE14,sumOfNavMeans92DE00,currentMax92DE0C,currentMin663AE8,currentFPSsum92DE08
// all+0;completedNavCount92DE04=0,navIndex92DDF8=0,rotationDegrees92DE20=0,stepDegrees92DDFC=1,navModeBYTE92DE10=0. Request panel5,force0;no immediate file-existence test,level parsing,guaranteed transition or source-name buffer update here. Does not change command-line state663AF0 or navCount92DE18. EAX is delegated panel-call residue,not verified load-success Boolean. NoNULLinput,allocation or string capacity guard.
int __cdecl rf_benchmark_start_level_and_reset_stats(char *Source)
{
  int v2[2]; // [esp-8h] [ebp-34h] BYREF
  int v3[5]; // [esp+0h] [ebp-2Ch] BYREF
  _DWORD *v4; // [esp+14h] [ebp-18h]
  int *v5; // [esp+18h] [ebp-14h]
  void *v6; // [esp+1Ch] [ebp-10h]
  int v7; // [esp+28h] [ebp-4h]

  v6 = v3;
  v4 = rf_string_construct_from_cstr(v3, (char *)byte_63F758);
  v3[4] = (int)v4;
  v7 = 0;
  v5 = v2;
  v3[3] = (int)rf_string_construct_from_cstr(v2, Source);
  v7 = -1;
  rf_level_transition_assign_level_and_save_strings(v2[0], (char *)v2[1], v3[0], (char *)v3[1]);
  if ( rf_multiplayer_runtime_mode )
    rf_multiplayer_runtime_teardown();
  rf_level_state_cache_clear();
  unk_92DE1C = 1;
  unk_92DDF4 = 0.0;
  unk_92DE14 = 0.0;
  unk_92DE00 = 0.0;
  unk_92DE0C = 0.0;
  flt_663AE8 = 0.0;
  unk_92DE08 = 0.0;
  unk_92DE04 = 0;
  unk_92DDF8 = 0;
  unk_92DE20 = 0;
  dword_92DDFC = 1;
  byte_92DE10 = 0;
  return rf_ui_request_panel_immediate(5, 0);
}

