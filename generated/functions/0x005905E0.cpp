// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005905E0 rf_dsound_start_buffer_voice
// UNREALRED VERIFIED [mission-mover-effects-20261013] Allocates a backend voice, installs the loaded sound buffer, gain and pan, then invokes buffer vtable+0x30 Play with flags=(argument4!=0). Zero is one-shot; one is looping. Also marks the loop flag in backend voice metadata when argument4==1. Looping is therefore resource-driven, not inferred from mover slot1.
int __cdecl rf_dsound_start_buffer_voice(int a1, float a2, float a3, char a4)
{
  int v5; // eax
  int *v6; // [esp+10h] [ebp-14h]
  int v7; // [esp+20h] [ebp-4h]

  if ( !unk_1BA1810 )
    return -1;
  if ( a1 < 0 )
    return -1;
  v7 = rf_dsound_allocate_or_reclaim_backend_slot();
  if ( v7 == -1 )
    return -1;
  v6 = &unk_1BA1820[11 * v7];
  if ( rf_dsound_duplicate_buffer_into_slot(*((_DWORD *)&unk_1951808 + 148 * a1 + 131), v7) )
    return -1;
  if ( rf_dsound_buffer_has_3d_capability(*v6) )
  {
    rf_dsound_query_buffer_3d_interface_if_capable(*v6, v6 + 1);
    if ( v6[1] )
      (*(void (__stdcall **)(int, int, _DWORD))(*(_DWORD *)v6[1] + 72))(v6[1], 2, 0);
  }
  if ( a4 == 1 )
    unk_1BA1848[11 * v7] |= 1u;
  v5 = rf_dsound_volume_float_to_lookup_value(a2);
  (*(void (__stdcall **)(int, int))(*(_DWORD *)*v6 + 60))(*v6, v5);
  *((float *)v6 + 5) = a2;
  v6[6] = *((_DWORD *)&unk_1951808 + 148 * a1 + 130);
  (*(void (__stdcall **)(int, int))(*(_DWORD *)*v6 + 64))(*v6, (int)(a3 * 1000.0));
  v6[2] = a1;
  if ( (*(int (__stdcall **)(int, _DWORD, _DWORD, bool))(*(_DWORD *)*v6 + 48))(*v6, 0, 0, a4 != 0) >= 0 )
  {
    v6[4] = dword_1BA1814++;
    if ( dword_1BA1814 < 0 )
      dword_1BA1814 = 0;
    return v6[4];
  }
  else
  {
    rf_dsound_buffer_slot_stop_release_unless_fading(v7);
    return -1;
  }
}

