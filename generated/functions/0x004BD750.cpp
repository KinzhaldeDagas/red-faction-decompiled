// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BD750 rf_world_build_model_instance_rgb_packets
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): No-argument cdecl routine; saved ST0 double input was spurious, no native incoming x87 value is consumed. Global662D90 zero does nothing. Otherwise walks clutter then item list in next652 order, requiring model128 nonnull, common flags124 mask2 clear, slice636 nonnull. Refreshes room cache using ECX object and NO FPU/stack argument, then calls five-word RGB-packet builder(model,room DWORD0,position60,matrix72,slice636). Builder EAX0 clears object636 only, without freeing global backing block or rolling back packet writes. Does not test model kind1 here (allocation pass elsewhere does), allocate slices, restore dirty/audio state or cache next across callbacks. No defined status/null/list
// validation.
void __cdecl rf_world_build_model_instance_rgb_packets()
{
  int first_dword; // eax
  int v1; // eax
  _DWORD *v2; // [esp-4h] [ebp-Ch]
  _DWORD *v3; // [esp-4h] [ebp-Ch]
  void *j; // [esp+0h] [ebp-8h]
  void *i; // [esp+4h] [ebp-4h]

  if ( dword_662D90 )
  {
    for ( i = (void *)rf_clutter_list_head; i != &unk_666D18; i = *((void **)i + 163) )
    {
      if ( *((_DWORD *)i + 32) && (*((_DWORD *)i + 31) & 2) == 0 && *((_DWORD *)i + 159) )
      {
        rf_object_refresh_room_cache_and_audio(i);
        v2 = *((_DWORD **)i + 159);
        first_dword = rf_receiver_get_first_dword(i);
        if ( !rf_model_handle_build_lod_vertex_rgb_packets(
                *((_DWORD **)i + 32),
                first_dword,
                (int)i + 60,
                (float *)i + 18,
                v2) )
          *((_DWORD *)i + 159) = 0;
      }
    }
    for ( j = (void *)unk_6FB1C4; j != &unk_6FAF38; j = *((void **)j + 163) )
    {
      if ( *((_DWORD *)j + 32) )
      {
        if ( (*((_DWORD *)j + 31) & 2) == 0 )
        {
          if ( *((_DWORD *)j + 159) )
          {
            rf_object_refresh_room_cache_and_audio(j);
            v3 = *((_DWORD **)j + 159);
            v1 = rf_receiver_get_first_dword(j);
            if ( !rf_model_handle_build_lod_vertex_rgb_packets(
                    *((_DWORD **)j + 32),
                    v1,
                    (int)j + 60,
                    (float *)j + 18,
                    v3) )
              *((_DWORD *)j + 159) = 0;
          }
        }
      }
    }
  }
}

