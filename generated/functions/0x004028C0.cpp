// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004028C0 sub_4028C0
// UNREALRED VERIFIED [ai-health-goals-20261028] Stores selected waypoint-list index at AI+0x408, point cursor0 at+0x40C and supplied traversalflags at+0x414 BEFORE calling0x40DCA0 with entityhandle. Failure returns0 after these writes; successful route admission requests secondary state1 and animation transition. Do not describe this as a rollback-atomic goal selection.
char __cdecl sub_4028C0(int *a1, int a2, int a3)
{
  a1[258] = a2;
  a1[259] = 0;
  a1[261] = a3;
  if ( !sub_40DCA0(*(_DWORD *)(*a1 + 44)) )
    return 0;
  rf_ai_secondary_state_write((int)a1, 1);
  if ( (*(_DWORD *)(*a1 + 2064) & 0x100000) != 0 )
    sub_4355A0(*a1);
  else
    sub_435500(*a1, 0);
  return 1;
}

