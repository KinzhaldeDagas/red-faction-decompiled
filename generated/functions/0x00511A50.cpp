// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511A50 rf_weapon_matches_special_pair
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclsignedweaponindex,caller pops4. Firstrequire0<=index<global911C68. ThenreturnnormalizedAL1 iffindex equalsglobal911CBC ORglobal911C6C;else0. Negative configuredsentinelsnevermatchbecauseargumentvalidationcomesfirst. No weaponrecordfields,name/flag comparison,ownership,ammo ormutations;semanticidentities ofthose two mutableglobalsarenot assignedbythisbody.
bool __cdecl rf_weapon_matches_special_pair(int a1)
{
  if ( a1 < 0 || a1 >= dword_911C68 )
    return 0;
  return a1 == dword_911CBC || a1 == unk_911C6C;
}

