// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441430 rf_foley_registry_choose_sound_441430
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One signed cdecl registry index; index<0 OR>=signed DWORD6E6728 returns EAX-1. Otherwise loads set handle DWORD6E6760+56*index, delegates
// choose-random-sound(set) and returns EAX. No own set/count/resource validation.4030D0 selects this field on401EF0 nonzero; no unsupported speech-category label assigned.
int __cdecl rf_foley_registry_choose_sound_441430(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6760[14 * a1]);
  else
    return -1;
}

