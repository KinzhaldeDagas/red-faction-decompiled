// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004412B0 rf_registry56_choose_sound_at_6E6740
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): One cdecl signed registry index; full EAX result. Require signed0<=index<DWORD6E6728, else return integer-1
// without Foley/RNG call. Valid path computes index*56 with native32-bit arithmetic, loads DWORD[6E6740+index*56] as Foley-set index, calls447010 exactly once and forwards its full
// sound-ID/-1 result. No direct sound playback, registry write or additional variant draw. This body proves this numeric field only, not its authored gameplay label. Foley helper
// owns its own signed set bounds and native count<=1/index0 behavior.
int __cdecl rf_registry56_choose_sound_at_6E6740(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6740[14 * a1]);
  else
    return -1;
}

