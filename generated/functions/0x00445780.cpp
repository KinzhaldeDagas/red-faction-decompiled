// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00445780 sub_445780
// UNREALRED VERIFIED [combat-panic-movement-20261111]: Movement-mode name lookup scans16 canonical names at661598 case-insensitively. Unknown name returns null without445740/global selection. Known name calls445740, which may map an unloaded canonical slot to slot0. Do not map unknown strings directly to run or none, and do not confuse these16 movement descriptors with23 cyclic animation-state names.
char *__cdecl sub_445780(char *String1)
{
  signed int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 16 && _stricmp(String1, (&off_661598)[i]); ++i )
    ;
  if ( i == 16 )
    return nullptr;
  else
    return sub_445740(i);
}

