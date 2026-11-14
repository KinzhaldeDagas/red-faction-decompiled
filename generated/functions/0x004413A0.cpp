// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004413A0 rf_registry56_choose_sound_at_6E6750
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): One cdecl signed registry index; full EAX result. Require signed0<=index<DWORD6E6728, else return integer-1
// without Foley/RNG. Otherwise load DWORD[6E6750+index*56] using native32-bit arithmetic, call447010 exactly once and forward its full sound-ID/-1 result. No direct playback, extra
// random selection or registry writes. The native body establishes this distinct numeric field, not an authored gameplay label; delegate bounds/count<=1 behavior is preserved.
int __cdecl rf_registry56_choose_sound_at_6E6750(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6750[14 * a1]);
  else
    return -1;
}

