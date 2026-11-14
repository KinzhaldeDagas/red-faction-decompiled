// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511B30 rf_weapon_preload_impact_vclips
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): CdeclSIGNEDINTEGERweaponindex,caller pops4;corrected storedchar* argument/char* return inference tovoid(int). ALL3 nativecalls in2 callersignoreEAX;thebodytreatsargumentsolelyasanintegerindexandhasno definedsuccessreturn. Require0<=index<911C68,thenfor signedi0..<recordDWORD1104 call507860(recordDWORD[1108+4*i]). Parsermaps$Impact Vclips names totheseeffectIDs;507860 conditionallylazy-loads/warmstheVBMnameat224-byte effectrecord+12,theninvokesits currentlyno-opsecondrepresentationhook whenname+36nonempty. No count3 upperguardhere,even thoughauthoredstoragehasthreeentries;count<=0doesnothing. No validationofpositiveeffectIDs,weaponmutation,listclear,impactspawn orresultaggregation.
// FormerEAXresidue variedbetweenincoming/index/recordbase andwasnot meaningfulpointer.
void __cdecl rf_weapon_preload_impact_vclips(int weapon_index)
{
  char *v1; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( weapon_index >= 0 && weapon_index < dword_911C68 )
  {
    v1 = (char *)&rf_weapon_records + 1360 * weapon_index;
    for ( i = 0; i < *((_DWORD *)v1 + 276); ++i )
      rf_vclip_preload_bitmap_and_vfx_stub(*(_DWORD *)&v1[4 * i + 1108]);
  }
}

