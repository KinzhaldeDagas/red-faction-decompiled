// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00588070 rf_character_record_reset_header
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Clears name[0], animation-handle count+3928, primary-bone count+72, auxiliary-binding count+4792 and model count+6588. For one descriptor at+6592 clears selected-mesh pointer+144 through588860. Sets root-bone index+6740=-1 and flags+68=0; returns owner pointer bits. Does NOT free existing arrays/handles, zero fixed bone/binding storage or reset descriptor allocation pointers.
int __cdecl rf_character_record_reset_header(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  *(_BYTE *)a1 = 0;
  *(_DWORD *)(a1 + 3928) = 0;
  *(_DWORD *)(a1 + 72) = 0;
  *(_DWORD *)(a1 + 4792) = 0;
  *(_DWORD *)(a1 + 6588) = 0;
  for ( i = 0; i < 1; ++i )
    rf_v3c_asset148_clear_selected_mesh((_DWORD *)(a1 + 148 * i + 6592));
  *(_DWORD *)(a1 + 6740) = -1;
  *(_DWORD *)(a1 + 68) = 0;
  return a1;
}

