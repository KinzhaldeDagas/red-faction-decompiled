// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004412E0 sub_4412E0
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Flee selector uses signed persona index[0,count),56-byte stride, Foley handle atrecord+14. Invalid persona returns-1 before Foley lookup/RNG. AI405030 uses this in mode7; AI+4 gate is selectedweapon, not target.
int __cdecl sub_4412E0(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(unk_6E6744[14 * a1]);
  else
    return -1;
}

