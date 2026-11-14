// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00446FB0 rf_foley_group_sound_count
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(signed group index), fullEAX. Only signed index>=0 AND index<live global group count6EDC30 admits;
// otherwise explicit-1. Admitted returns RAW DWORD[6E6E54+44*index] without nonnegative clamp, pointer/list consistency or active-variant check. No RNG, allocation, sound playback,
// upper capacity bound beyond live count, or mutation. Zero/negative raw count remains distinct from invalid group-1 only by provenance.
int __cdecl rf_foley_group_sound_count(int a1)
{
  if ( a1 >= 0 && a1 < unk_6EDC30 )
    return unk_6E6E54[11 * a1];
  else
    return -1;
}

