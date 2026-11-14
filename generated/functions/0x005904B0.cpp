// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005904B0 rf_dsound_allocate_or_reclaim_backend_slot
// UNREALRED VERIFIED [dsound-creation-20261028]: Scans30 slots. First null DS buffer pointer returns slot immediately,without clearing stale fields. Otherwise first slot with flags mask5clear,not hardware playing,andnot cached paused is passed to0x58F3E0 then returned. Release helper can skip fade flag8,so returned slot may STILL own old buffer. No reservation or synchronization; no suitable slot-1.
int __cdecl rf_dsound_allocate_or_reclaim_backend_slot()
{
  int i; // [esp+0h] [ebp-8h]
  int v2; // [esp+4h] [ebp-4h]

  v2 = -1;
  for ( i = 0; i < 30; ++i )
  {
    if ( !unk_1BA1820[11 * i] )
      return i;
    if ( (unk_1BA1848[11 * i] & 5) == 0 && !rf_dsound_buffer_slot_is_playing(i) && !rf_dsound_buffer_slot_pause_mask(i) )
    {
      v2 = i;
      rf_dsound_buffer_slot_stop_release_unless_fading(i);
      return v2;
    }
  }
  return v2;
}

