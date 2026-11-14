// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00405BB0 rf_ai_mode16_secondary_route_or_alarm_dispatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One AI block, central mode16 callback. Secondary1: shared alarm nonzero ->random FLOAT10..20 then40AC80(block,*(global
// local-fpgun-player+20),random), without global-player null guard. AlarmAL0 instead calls40ECE0 with native stack(route=block+744,extra1), cleans8bytes; existing callee reads route
// only. Secondary10 ->405C60(block). All other states request mode2(-1,-1), then secondary0; mode helper can remap2 under multiplayer/splitscreen. No same-call execution of new
// state, direct target assignment, own role gate or defined result boolean.
void __cdecl rf_ai_mode16_secondary_route_or_alarm_dispatch(int *Character)
{
  float v1; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  v2 = Character[173];
  if ( v2 == 1 )
  {
    if ( rf_alarm_get_shared_active() )
    {
      v1 = rf_random_float_range(10.0, 20.0);
      sub_40AC80(Character, *(_DWORD *)(rf_local_fpgun_player + 20), v1);
    }
    else
    {
      rf_ai_route_update((int)(Character + 186));
    }
  }
  else if ( v2 == 10 )
  {
    sub_405C60(Character);
  }
  else
  {
    rf_ai_numeric_mode_write(Character, 2, -1, -1);
    rf_ai_secondary_state_write((int)Character, 0);
  }
}

