// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502BE0 rf_event_state_restore_when_dead
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] For each EXISTING registry event type16, find FIRST matching saved E+0x24 identifier in supplied 24-byte entries. Restore common header and raw byte event+0x2B8 latch at entry+0x14 in reverse direction. No matching entry marks embedded common-object pointer E+4 for deferred deletion; does not allocate replacement events. No saved-entry consumption/deduplication, type restoration or immediate object deletion. Deferred context references remain queued after header restore.
int __cdecl rf_event_state_restore_when_dead(int a1, int a2)
{
  int result; // eax
  int v3; // [esp+4h] [ebp-10h]
  char v4; // [esp+Bh] [ebp-9h]
  int j; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword(unk_90B0E0);
    if ( i >= result )
      break;
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, i) + 656) == 16 )
    {
      v4 = 0;
      v3 = *(_DWORD *)sub_552200(unk_90B0E0, i);
      for ( j = 0; j < a2; ++j )
      {
        if ( *(_DWORD *)(v3 + 36) == *(_DWORD *)(a1 + 24 * j) )
        {
          rf_event_state_unpack_header(v3, a1 + 24 * j);
          *(_BYTE *)(v3 + 696) = *(_BYTE *)(a1 + 24 * j + 20);
          v4 = 1;
          break;
        }
      }
      if ( !v4 )
      {
        if ( v3 )
          rf_object_mark_for_deferred_delete(v3 + 4);
        else
          rf_object_mark_for_deferred_delete(0);
      }
    }
  }
  return result;
}

