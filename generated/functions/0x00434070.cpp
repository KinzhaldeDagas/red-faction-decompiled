// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00434070 sub_434070
// UNREALRED VERIFIED [ai-authored-startup-20261028] Name-based waypoint admission resolves entity handle, clears traversal flag bit1 (mask~1) when multiplayer OR split-screen is active, writes current list AI+0x408 and cursor0/+0x40C, then flags/+0x414. Missing name or 0x40DCA0 route failure returns-1. Success writes secondary1 and selects presentation helper using entity+0x810 bit0x100000. It does not itself write numeric mode4.
int __cdecl sub_434070(int a1, char *String2, int a3)
{
  _DWORD *v4; // [esp+0h] [ebp-4h]

  v4 = (_DWORD *)rf_entity_resolve_handle(a1);
  if ( !v4 )
    return -1;
  if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    a3 &= ~1u;
  v4[426] = sub_487150(String2);
  if ( v4[426] == -1 )
    return -1;
  v4[427] = 0;
  v4[429] = a3;
  if ( !sub_40DCA0(a1) )
    return -1;
  rf_ai_secondary_state_write((int)(v4 + 168), 1);
  if ( (v4[516] & 0x100000) != 0 )
    sub_4355A0((int)v4);
  else
    sub_435500((int)v4, 0);
  return 0;
}

