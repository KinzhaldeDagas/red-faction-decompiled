// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005112A0 rf_weapon_is_semiautomatic
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdecl signedweaponindex,caller pops4. ReturnnormalizedAL0 unless index>=0 ANDindex<signedglobalcount911C68;validindex reads weaponrecord at912000+1360*index,flagsDWORD612,tests mask0x100000,returnsAL1 iffset. Source namedflag token semi_automatic independently matched in originalPE flag table663A40(flags612) or663A9C(flags616). No fixed64-record cap,inventory/ammo/owner check,otherflagtest,allocation orwrites. Genericbool describesLOWBYTE;upperEAXbits not guaranteed onall paths.
bool __cdecl rf_weapon_is_semiautomatic(int a1)
{
  return a1 >= 0 && a1 < dword_911C68 && (unk_912264[340 * a1] & 0x100000) != 0;
}

