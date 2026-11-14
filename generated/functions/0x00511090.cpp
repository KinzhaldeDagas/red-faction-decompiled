// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511090 rf_weapon_has_pilot_flame
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdecl signedweaponindex,caller pops4. ReturnnormalizedAL0 unless index>=0 ANDindex<signedglobalcount911C68;validindex reads weaponrecord at912000+1360*index,flagsDWORD616,tests mask0x200,returnsAL1 iffset. Source namedflag token has_pilot_flame independently matched in originalPE flag table663A40(flags612) or663A9C(flags616). No fixed64-record cap,inventory/ammo/owner check,otherflagtest,allocation orwrites. Genericbool describesLOWBYTE;upperEAXbits not guaranteed onall paths.
bool __cdecl rf_weapon_has_pilot_flame(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && (*((_DWORD *)&rf_weapon_records + 340 * a1 + 154) & 0x200) != 0;
}

