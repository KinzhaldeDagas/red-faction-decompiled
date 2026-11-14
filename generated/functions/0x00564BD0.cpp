// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564BD0 rf_model_handle_collide_indexed_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, model factories, visibility recursion, render material stack aliases, LOD selection, collision dispatch and floating returns): cdecl(handle,index,query,result,initializeByte). Only initializeByte EXACTLY1 sets result float0=1 and float28=0 before tag dispatch. Tag2 always uses LAST character LOD container(count6588-1), not visual LOD selector, and calls skinned collision. Tag1 index-1 calls all-static-mesh collision, otherwise indexed static helper. Tag3 merely checks definition mesh flags bit1 and ALWAYS returns0; no scene geometry collision helper is invoked even if every flag allows. Unsupported tags0. No null/count/index guards; result reset can occur despite no implemented collision.
char __cdecl rf_model_handle_collide_indexed_dispatch(_DWORD *a1, int a2, void *a3, float *a4, unsigned __int8 a5)
{
  int i; // [esp+0h] [ebp-Ch]

  if ( a5 == 1 )
  {
    *a4 = 1.0;
    a4[7] = 0.0;
  }
  if ( *a1 == 2 )
    return rf_v3c_asset_collide_skinned_wrapper(
             (void *)(a1[2] + 148 * (*(_DWORD *)(a1[2] + 6588) - 1) + 6592),
             (void *)a1[1],
             a3,
             a4,
             a5);
  if ( *a1 == 1 )
  {
    if ( a2 == -1 )
      return rf_v3c_asset_collide_all_static_meshes((void *)a1[1], a3, a4, a5);
    else
      return rf_v3c_asset_collide_static_mesh((void *)a1[1], a2, a3, a4, a5);
  }
  else
  {
    if ( *a1 == 3 )
    {
      if ( a2 == -1 )
      {
        for ( i = 0; i < *(_DWORD *)(a1[2] + 76); ++i )
        {
          if ( (*(_DWORD *)(*(_DWORD *)(a1[2] + 72) + 292 * i + 276) & 1) == 0 )
            return 0;
        }
      }
      else if ( (*(_DWORD *)(*(_DWORD *)(a1[2] + 72) + 292 * a2 + 276) & 1) == 0 )
      {
        return 0;
      }
    }
    return 0;
  }
}

