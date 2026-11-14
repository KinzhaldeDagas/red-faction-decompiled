// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00447080 rf_foley_group_sound_array
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(signed group index), fullEAX raw sound-array address. Require signed index>=0 AND index<live global
// group count6EDC30; otherwise explicit0. Admitted returns RAW DWORD pointer[6E6E58+44*index], possiblyNULL, without checking group sound count, storage extent, selected variant or
// pointer validity. No dereference of returned array, RNG, copy/allocation, playback or mutation. Pairs with446FB0 but neither helper guarantees a usable nonempty list.
int __cdecl rf_foley_group_sound_array(int a1)
{
  if ( a1 >= 0 && a1 < unk_6EDC30 )
    return dword_6E6E58[11 * a1];
  else
    return 0;
}

