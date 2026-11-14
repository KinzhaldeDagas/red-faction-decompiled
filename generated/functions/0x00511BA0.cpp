// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511BA0 rf_weapon_is_continuous_fire
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclsignedweaponindex,LOWBYTEaltselector,caller pops8. Rejectinvalidindex. SelectorLOWBYTE0 testsflagsDWORD612mask0x2(namedcontinuous_fire),anynonzeroLOWBYTEtestsmask0x4(namedalt_continuous_fire),returnsnormalizedALbool. OriginalPE token table663A40 verified. Fullinteger256selectsprimary;doesnotcheckalt_firemask0x1,activefiring,delayarrays orammo. No statewrites.
char __cdecl rf_weapon_is_continuous_fire(int a1, char a2)
{
  char *v3; // [esp+0h] [ebp-4h]

  if ( a1 < 0 || a1 >= dword_911C68 )
    return 0;
  v3 = (char *)&rf_weapon_records + 1360 * a1;
  if ( a2 )
  {
    if ( (*((_DWORD *)v3 + 153) & 4) != 0 )
      return 1;
  }
  else if ( (*((_DWORD *)v3 + 153) & 2) != 0 )
  {
    return 1;
  }
  return 0;
}

