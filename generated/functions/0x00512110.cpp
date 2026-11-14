// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512110 rf_player_has_live_designated_projectile
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclplayer*,caller pops4. NULLplayer→AL0;resolveentityfromplayerDWORD20,failedresolve→0. Scanprojectileintrusiveringhead911F74 untilsentinel911CE8,nextDWORD652. FIRSTentrywithweaponIndex664==global911C78,ownerUID48==resolvedEntityUID44,BOTHF32fields668and52ORDERED>0,andobjectflagsDWORD124bit2CLEARreturnsAL1;otherwise0. NaN/zero/negativetimer/healthfieldsreject. Doesnotcountentries,inspectdamageType1324/flag760/selectedweapon/ammo,orproveownershipviapointeridentity. CorruptNULL/ringcyclesnotguarded;no mutation.
char __cdecl rf_player_has_live_designated_projectile(int a1)
{
  char v2; // [esp+3h] [ebp-9h]
  int i; // [esp+4h] [ebp-8h]
  int v4; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return 0;
  v2 = 0;
  v4 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( !v4 )
    return 0;
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 664) == dword_911C78
      && *(_DWORD *)(i + 48) == *(_DWORD *)(v4 + 44)
      && *(float *)(i + 668) > 0.0
      && *(float *)(i + 52) > 0.0
      && (*(_DWORD *)(i + 124) & 2) == 0 )
    {
      return 1;
    }
  }
  return v2;
}

