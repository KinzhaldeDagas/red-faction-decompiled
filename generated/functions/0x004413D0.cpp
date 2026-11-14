// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004413D0 rf_foley_registry_choose_sound_4413D0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI weighted-target/mode11/15/16/speech/stimulus chains, original dispatch/float constants and native field
// lifetime and native signed/x87/stack/callback ABI): One signed cdecl registry index. Negative or >=signed DWORD6E6728 returns EAX-1. Otherwise loads Foley set DWORD6E6754+56*index,
// delegates choose-random-sound(set), returns its EAX. No own set-null/count/resource validation or deadline writes. Record field distinct from other same-stride registry selectors;
// no unsupported speech-category label assigned.
int __cdecl rf_foley_registry_choose_sound_4413D0(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6754[14 * a1]);
  else
    return -1;
}

