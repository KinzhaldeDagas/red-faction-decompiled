// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502900 rf_event_state_restore_generic_headers
// UNREALRED VERIFIED [event-state-registry-continuation-20261027] For each supplied20-byte entry, linearly search current registry for first event with E+0x24 equal input saved-id dword; apply0x502880 then stop inner search. Missing saved id is ignored, no new event created or unmatched registry record removed. Does not filter event type beyond whatever input set caller supplies; input order permits repeated application to same event.
void __cdecl rf_event_state_restore_generic_headers(int a1, int a2)
{
  int *v2; // eax
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    for ( j = 0; j < rf_receiver_get_first_dword(unk_90B0E0); ++j )
    {
      if ( *(_DWORD *)(*(_DWORD *)sub_552200(unk_90B0E0, j) + 36) == *(_DWORD *)(a1 + 20 * i) )
      {
        v2 = (int *)sub_552200(unk_90B0E0, j);
        rf_event_state_unpack_header(*v2, a1 + 20 * i);
        break;
      }
    }
  }
}

