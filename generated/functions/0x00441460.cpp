// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00441460 sub_441460
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Panic selector uses signed persona index[0,count),56-byte stride, Foley handle atrecord+34. Invalid persona returns-1 before Foley lookup/RNG. Valid row calls447010; registered sound IDs, not persona/HUD cue IDs or filename aliases.
int __cdecl sub_441460(int a1)
{
  if ( a1 >= 0 && a1 < unk_6E6728 )
    return rf_foley_choose_random_sound(dword_6E6764[14 * a1]);
  else
    return -1;
}

