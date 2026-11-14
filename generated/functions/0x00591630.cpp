// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591630 rf_dsound_set_group_or_all_slot_volume
// UNREALRED VERIFIED [dsound-playback-20261028]: Arguments metadata/group DWORD,volume float. Clamps local volume0..1 through0x40D620,walks30 backend slots. Nonnull buffer and(slot metadata+24==argument OR argument==-1) receives SetVolume+60 using0x590440 lookup. Stores clamped float atslot+20 regardless HRESULT. Includes stopped/paused slots; no playing check,fade-step adjustment or lock. Does not multiply existing volume; replaces it.
void __cdecl rf_dsound_set_group_or_all_slot_volume(int a1, float a2)
{
  int v2; // eax
  int i; // [esp+8h] [ebp-4h]

  rf_float_clamp_in_place(&a2, 0.0, 1.0);
  for ( i = 0; i < 30; ++i )
  {
    if ( unk_1BA1820[11 * i] && (unk_1BA1838[11 * i] == a1 || a1 == -1) )
    {
      v2 = rf_dsound_volume_float_to_lookup_value(a2);
      (*(void (__cdecl **)(int, int))(*(_DWORD *)unk_1BA1820[11 * i] + 60))(unk_1BA1820[11 * i], v2);
      *((float *)&unk_1BA1834 + 11 * i) = a2;
    }
  }
}

