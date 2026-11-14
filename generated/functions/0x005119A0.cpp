// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005119A0 rf_projectile_flag2_damage_type_is_1_or_2
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclobject*,caller pops4. NULLobject returnsAL0. Otherwise requireobjectDWORD760&2,theninfo=objectDWORD660 andinfoDWORD1324 EXACT1 OR2. ReturnnormalizedAL1 iff bothconditions,else0. Field1324 is parser$Damage Type lookupoutput,not weaponindex orammo. Short-circuit avoidsinfoderefwhenbit2clear,butnonnullinfo isnotvalidatedwhenbit2set. Doesnotreadlife668,health52,owner48,position orremainingdistance752;read-only.
bool __cdecl rf_projectile_flag2_damage_type_is_1_or_2(int a1)
{
  if ( !a1 )
    return 0;
  return (*(_DWORD *)(a1 + 760) & 2) != 0
      && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) == 1 || *(_DWORD *)(*(_DWORD *)(a1 + 660) + 1324) == 2);
}

