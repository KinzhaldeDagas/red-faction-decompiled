// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00426600 rf_entity_preload_live_model_and_weapon_vclips
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No arguments, incidental EAX. Walks intrusive active list from DWORD68211C until sentinel681E90, loading next DWORD record+652 AFTER all
// per-record delegates. Only nonNULL model handle+128 admits work: prepare materials(model), then class pointer+660 DWORD+1784 !=EXACT-1 invokes vclip preload. Selected weapon
// DWORD+676 !=EXACT-1 indexes global912000+1360*weapon WITHOUT sign/range validation. Signed i=0..<weapon DWORD+1104 re-reads count each test; every vclip index weapon+1108+4*i !=-1
// preloads in order. A NULL model skips class and weapon preloads entirely. No own entity/type/class/list/null guards, caching/dedup of duplicate clips, capacity bounds or
// state/timer/pose stores. Traversal and delegates are not a snapshot; no uniform success result.
void rf_entity_preload_live_model_and_weapon_vclips()
{
  int i; // [esp+0h] [ebp-Ch]
  char *v1; // [esp+4h] [ebp-8h]
  int j; // [esp+8h] [ebp-4h]

  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 128) )
    {
      rf_model_handle_prepare_materials_if_nonnull(*(_DWORD **)(i + 128));
      if ( *(_DWORD *)(*(_DWORD *)(i + 660) + 1784) != -1 )
        rf_vclip_preload_bitmap_and_vfx_stub(*(_DWORD *)(*(_DWORD *)(i + 660) + 1784));
      if ( *(_DWORD *)(i + 676) != -1 )
      {
        v1 = (char *)&rf_weapon_records + 1360 * *(_DWORD *)(i + 676);
        for ( j = 0; j < *((_DWORD *)v1 + 276); ++j )
        {
          if ( *(_DWORD *)&v1[4 * j + 1108] != -1 )
            rf_vclip_preload_bitmap_and_vfx_stub(*(_DWORD *)&v1[4 * j + 1108]);
        }
      }
    }
  }
}

