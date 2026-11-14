// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590250 rf_dsound_play_static_3d_sample
// UNREALRED VERIFIED [dsound-creation-20261028]: Seven arguments sample index,world position,velocity,min distance,max distance,volume float,loop byte. Requires initialized and sample>=0. Allocates backend slot,duplicates sample static buffer,requires caps3D,queries3D interface andrequires nonnull. Early failures after duplicate can leave slot resources unreleased. Copies sample metadata+520 to backend+24,sets volume via lookup,sets3D mode+72(value0,flags0),writes position/velocity/distances through0x5ED180. Loop byte EXACTLY1 sets cached flag1 andDS Play loop booltrue. Caches volume+20,source index+8; Play failure delegates release helper then-1. Success assigns play handle from global0x1BA1814 then increments,wrapping negative new counter to0. No sample upper bound,old fade-state cleanup or checking volume/3D setter HRESULTs.
int __cdecl rf_dsound_play_static_3d_sample(int a1, float *a2, float *a3, float a4, float a5, float a6, char a7)
{
  int v8; // eax
  int *v9; // [esp+24h] [ebp-14h]
  int v10; // [esp+34h] [ebp-4h]

  if ( !unk_1BA1810 )
    return -1;
  if ( a1 < 0 )
    return -1;
  v10 = rf_dsound_allocate_or_reclaim_backend_slot();
  if ( v10 == -1 )
    return -1;
  v9 = &unk_1BA1820[11 * v10];
  if ( rf_dsound_duplicate_buffer_into_slot(*((_DWORD *)&unk_1951808 + 148 * a1 + 131), v10) )
    return -1;
  if ( !rf_dsound_buffer_has_3d_capability(*v9) )
    return -1;
  rf_dsound_query_buffer_3d_interface_if_capable(*v9, v9 + 1);
  if ( !v9[1] )
    return -1;
  v9[6] = *((_DWORD *)&unk_1951808 + 148 * a1 + 130);
  v8 = rf_dsound_volume_float_to_lookup_value(a6);
  (*(void (__stdcall **)(int, int))(*(_DWORD *)*v9 + 60))(*v9, v8);
  (*(void (__stdcall **)(int, _DWORD, _DWORD))(*(_DWORD *)v9[1] + 72))(v9[1], 0, 0);
  rf_dsound3d_set_emitter_position_velocity_distances(v10, a4, a5, a2, a3);
  if ( a7 == 1 )
    v9[10] |= 1u;
  *((float *)v9 + 5) = a6;
  v9[2] = a1;
  if ( (*(int (__stdcall **)(int, _DWORD, _DWORD, bool))(*(_DWORD *)*v9 + 48))(*v9, 0, 0, a7 == 1) >= 0 )
  {
    v9[4] = dword_1BA1814++;
    if ( dword_1BA1814 < 0 )
      dword_1BA1814 = 0;
    return v9[4];
  }
  else
  {
    rf_dsound_buffer_slot_stop_release_unless_fading(v10);
    return -1;
  }
}

