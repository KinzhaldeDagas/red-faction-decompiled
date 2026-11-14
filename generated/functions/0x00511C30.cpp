// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00511C30 rf_weapon_derive_flags2_threshold_bits
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): Cdeclnoargs. Signedascendingi<globalweaponcount911C68;stride1360. If ORDERED F32record192>=double100,setflags2DWORD616bit0x800;NaNdoesnotsetit. Ifbit800is set (includingpreexisting),primarymode:whenflagsDWORD612 continuousbit2clear AND(semiautomaticbit100000set ORORDERED firewaitF32+208<=double.25),ORflags2bit1000. Altmode samewithcontinuousbit4 andaltfirewait+212,ORbit2000. NaNfirewaitdoesnotqualifyunlesssemiautomaticbypassescomparison. AllchangesareOR-only;neverclearstale800/1000/2000wheninputschange,preservesotherbits. DerivedbitslieABOVE11authoredFlags2tokens;field192producer/semanticmeaningnotclaimedhere. No recordcapacity64cap,finite/rangevalidation orcallingweaponmethods.
// ForpositivecountnormalcompletionEAX=countfromfinalloopincrement;nonpositivecountdoesnotprovideastable0return.
int rf_weapon_derive_flags2_threshold_bits()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_911C68; ++i )
  {
    if ( *((float *)&unk_9120C0 + 340 * i) >= 100.0 )
      rf_weapon_records_flags2[340 * i] |= 0x800u;
    if ( (rf_weapon_records_flags2[340 * i] & 0x800) != 0 )
    {
      if ( (unk_912264[340 * i] & 2) == 0
        && ((unk_912264[340 * i] & 0x100000) != 0 || *((float *)&unk_9120D0 + 340 * i) <= 0.25) )
      {
        rf_weapon_records_flags2[340 * i] |= 0x1000u;
      }
      if ( (unk_912264[340 * i] & 4) == 0
        && ((unk_912264[340 * i] & 0x100000) != 0 || *((float *)&unk_9120D4 + 340 * i) <= 0.25) )
      {
        rf_weapon_records_flags2[340 * i] |= 0x2000u;
      }
    }
    result = i + 1;
  }
  return result;
}

