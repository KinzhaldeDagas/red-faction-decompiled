// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511190 rf_weapon_choose_geomod_sound
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclsignedweaponindex,caller pops4. Invalidnegative orindex>=911C68 returnsEAX-1. Otherwise callfoley random-sound selector withrawDWORD weaponrecord+504 andforwardreturn. Parser508990 assignsfield504 from optional$Geomod Sound lookup,default-1. Doesnotvalidate that soundset,reserve/play audio,checkequippedweapon oruse ordinaryfire/impact soundfields. Recordstride1360,base912000;sourceindexnotpointer.
int __cdecl rf_weapon_choose_geomod_sound(int a1)
{
  if ( a1 >= 0 && a1 < dword_911C68 )
    return rf_foley_choose_random_sound(*((_DWORD *)&rf_weapon_records + 340 * a1 + 126));
  else
    return -1;
}

