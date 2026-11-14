// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441370 rf_registry56_choose_sound_at_6E674C
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): One cdecl signed registry index; full EAX result. Require signed0<=index<DWORD6E6728, else integer-1 before
// any Foley/RNG call. Valid path loads DWORD[6E674C+index*56] with native32-bit index arithmetic, calls447010 once and forwards its full sound-ID/-1 result. No direct sound playback
// or registry mutation. Field differs from4412B0/4413A0; no authored label inferred. Foley helper retains native bounds/count/RNG rules, including index0 dereference for count<=1
// rather than a new empty-set rejection.
int __cdecl rf_registry56_choose_sound_at_6E674C(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E674C[14 * a1]);
  else
    return -1;
}

