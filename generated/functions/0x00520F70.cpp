// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520F70 rf_world_reset_room_visibility_state
// UNREALRED VERIFIED [authored-sky-renderer] Resets the two decoded per-room visibility fields before each world traversal.
int __cdecl rf_world_reset_room_visibility_state(int a1)
{
  int result; // eax
  int v2; // ecx
  int v3; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(a1 + 156));
  v3 = result;
  for ( i = 0; i < v3; ++i )
  {
    v2 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 156), i);
    *(_DWORD *)(v2 + 356) = 255;
    *(_BYTE *)(v2 + 353) = 0;
    result = i + 1;
  }
  return result;
}

