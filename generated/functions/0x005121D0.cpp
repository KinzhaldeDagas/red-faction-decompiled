// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005121D0 rf_entity_has_live_designated_projectile
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclentity*,caller pops4. NULLentity→AL0. Sameprojectilering911F74/sentinel911CE8/next652 predicateas512110,butcomparesownerUID48directlytoinputentityUID44 WITHOUThandle-resolution/playerindirection. RequireweaponIndex664==mutableglobal911C78,F32fields668and52ORDERED>0,flags124bit2clear;firstmatchAL1else0. No info/damageType/selectedweapon check,destruction orupdates. DistinctinputABIfromplayerwrapper;NaNpositivefieldtestsreject.
char __cdecl rf_entity_has_live_designated_projectile(int a1)
{
  char v2; // [esp+3h] [ebp-5h]
  int i; // [esp+4h] [ebp-4h]

  v2 = 0;
  if ( !a1 )
    return 0;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 664) == dword_911C78
      && *(_DWORD *)(i + 48) == *(_DWORD *)(a1 + 44)
      && *(float *)(i + 668) > 0.0
      && *(float *)(i + 52) > 0.0
      && (*(_DWORD *)(i + 124) & 2) == 0 )
    {
      return 1;
    }
  }
  return v2;
}

