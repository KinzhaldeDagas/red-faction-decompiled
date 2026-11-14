// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2270 rf_model_mesh_decal_slots_clear25
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdeclowner pointer,caller pops4. Ascending25slots atowner+4328(10E8)+4*i;for eachnonnull collection call5149C0 pooledrelease thenzero slot. ReturnsEAX25 fromfinal loopincrement,not releasecount/status. No ownerNULLguard,duplicate pointer protection,heapdeletion or clearing of other ownerstate. Distinct slots containing samepointer would release twice;doesnotdedup.
int __cdecl rf_model_mesh_decal_slots_clear25(int a1)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 25; ++i )
  {
    if ( *(_DWORD *)(a1 + 4 * i + 4328) )
    {
      rf_mesh_decal_collection_release_to_pools(*(_DWORD **)(a1 + 4 * i + 4328));
      *(_DWORD *)(a1 + 4 * i + 4328) = 0;
    }
    result = i + 1;
  }
  return result;
}

