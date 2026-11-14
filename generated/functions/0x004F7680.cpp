// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7680 rf_mission_event_unregister_and_track_removal
// UNREALRED VERIFIED [event-registry-crc-20261028]: For event E, clears/frees embedded pointer-array at E+668 and removes first E pointer from global registry0x90B0E0. If byte0x90B055 equals exactly1, appends saved UID E+36 to dword array0x90B058 and increments count0x90B0DC without local capacity guard. Called by object deletion dispatcher. Does not itself free E. E common-object base is E+4.
int __cdecl rf_mission_event_unregister_and_track_removal(int a1)
{
  int result; // eax

  rf_pointer_array_release_storage((void **)(a1 + 668));
  result = rf_pointer_array_remove_first(unk_90B0E0, a1);
  if ( unk_90B055 == 1 )
  {
    unk_90B058[unk_90B0DC++] = *(_DWORD *)(a1 + 36);
    return a1;
  }
  return result;
}

