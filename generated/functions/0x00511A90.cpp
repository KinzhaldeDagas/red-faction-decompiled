// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511A90 rf_weapon_has_positive_impact_delay
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclsignedweaponindex,LOWBYTEaltselector,caller pops8. Invalidindex→AL0. Fori0then1,readweaponF32[336+4*i] whenselectorLOWBYTE0,otherwise[344+4*i];returnAL1 onFIRSTORDEREDpositivevalue,else0aftertwoentries. Theseare$Impact Delay and$Alt Impact Delay arrays from508990. NaN/zero/negativeentriesreject;positiveinfinitypasses. Fullinteger256selectsprimarybecauseLOWBYTE0. No timer,countofauthoreddelays oractualimpactstate checked;read-only.
char __cdecl rf_weapon_has_positive_impact_delay(int a1, char a2)
{
  char *v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( a1 < 0 || a1 >= dword_911C68 )
    return 0;
  v3 = (char *)&rf_weapon_records + 1360 * a1;
  for ( i = 0; i < 2; ++i )
  {
    if ( a2 )
    {
      if ( *(float *)&v3[4 * i + 344] > 0.0 )
        return 1;
    }
    else if ( *(float *)&v3[4 * i + 336] > 0.0 )
    {
      return 1;
    }
  }
  return 0;
}

