// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613C16 ___ascii_stricmp
// UNREALRED VERIFIED [combat-native-weapon-layout-20261111]: Default-C ASCII byte comparison: load unsigned bytes, fold only ASCII A..Z by+32, continue equal untilNUL; highbytes unchanged. It does not trim, decode UTF8 or use Unicode case folding. Weapon lookup50FB80 via560960 callsCRT_stricmp, whose zero-locale-flag path delegates here. Alternate CRT locale path exists in613D24 and remains distinct.
int __cdecl __ascii_stricmp(unsigned __int8 *a1, unsigned __int8 *a2)
{
  int v4; // eax
  int v5; // ecx

  do
  {
    v4 = *a1++;
    if ( (unsigned int)(v4 - 65) <= 0x19 )
      v4 += 32;
    v5 = *a2++;
    if ( (unsigned int)(v5 - 65) <= 0x19 )
      v5 += 32;
  }
  while ( v4 && v4 == v5 );
  return v4 - v5;
}

