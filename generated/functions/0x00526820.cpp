// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526820 rf_light_refresh_receiver_coverage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light,lowBYTE secondaryMode. Gate on globalBYTE rf_fixed_pool_heap_spill_enabled nonzero AND primary contextDWORDD035EC nonNULL; failure skips BOTH primary and additional contexts. Assign coverage on primary with current transform (no sync here). If head-cell pointerD035F0 nonNULL, traverse its circular20-byte nodes in registration order: push instance transform(node.posPtr12,node.orientPtr16), synchronize light alternate coordinates526630, assign coverage(light,node.solid8,sameBYTE), pop transform. No exception cleanup around push/pop and no final resync after restoring transform; alternate light fields retain last synchronized receiver-space data. No active-list build or frame face-mask
// operation. EAX residue not success count. List mutation during traversal not protected.
int __cdecl rf_light_refresh_receiver_coverage(int a1, char a2)
{
  int result; // eax
  _DWORD *v3; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = rf_fixed_pool_heap_spill_enabled[0];
  if ( rf_fixed_pool_heap_spill_enabled[0] )
  {
    if ( dword_D035EC )
    {
      result = rf_light_assign_receiver_coverage(a1, dword_D035EC, a2);
      if ( dword_D035F0 )
      {
        for ( i = (_DWORD *)*dword_D035F0; i; i = v3 )
        {
          rf_renderer_push_instance_transform_dispatch(i[3], i[4]);
          rf_light_sync_receiver_space_transform(a1);
          rf_light_assign_receiver_coverage(a1, i[2], a2);
          rf_renderer_pop_instance_transform_dispatch();
          result = (int)i;
          if ( *i == *dword_D035F0 )
          {
            v3 = nullptr;
          }
          else
          {
            result = (int)i;
            v3 = (_DWORD *)*i;
          }
        }
      }
    }
  }
  return result;
}

