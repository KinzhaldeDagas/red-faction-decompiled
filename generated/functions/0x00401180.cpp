// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00401180 sub_401180
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Fallback history equality is full resolved common-object handle identity, not a weak actor pointer alone. A reborn actor at same host address must not satisfy an older lifetime entry. Host body IDs are a labeled common-lifetime representation; unresolved arbitrary native handles and nonbody domains cannot be silently invented.
// UNREALRED VERIFIED [combat-route-operands-20261111] Fallback scans index0 upward. Erasing an unresolved entry calls unchecked erase then reaches the common loop index increment, so the shifted successor is skipped during THAT call. Reverse prune/erase-all changes observable traversal and must not substitute for native order.
char __cdecl sub_401180(int a1, int a2)
{
  int *v3; // eax
  int i; // [esp+0h] [ebp-10h]
  int v5; // [esp+8h] [ebp-8h]
  char v6; // [esp+Fh] [ebp-1h]

  if ( !a1 || !a2 )
    return 0;
  v6 = byte_661000[4 * *(_DWORD *)(a1 + 504) + *(_DWORD *)(a2 + 504)];
  if ( !v6 )
  {
    for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 1196)); ++i )
    {
      v3 = (int *)sub_552200((_DWORD *)(a1 + 1196), i);
      v5 = rf_object_resolve_handle(*v3);
      if ( v5 )
      {
        if ( *(_DWORD *)(v5 + 44) == *(_DWORD *)(a2 + 44) )
          return 1;
      }
      else
      {
        rf_pointer_array_erase_index_unchecked((_DWORD *)(a1 + 1196), i);
      }
    }
  }
  return v6;
}

