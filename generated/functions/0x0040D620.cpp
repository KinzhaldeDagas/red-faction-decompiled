// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D620 rf_float_clamp_in_place
// UNREALRED VERIFIED [stream-serializers-20261029]: cdecl float pointer,lower,upper. For ordered values: if value<lower stores lower;else if value>upper stores upper;else unchanged. Does not swap inverted bounds,validate pointer or return destination. No defined application-level NaN policy asserted here.
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weaponflag/accessor provenance,particle descriptors,trails,ricochet/piercing andx87unorderedbranches,original ECX/stack flow and PE bytes): CdeclvalueF32*,lowerF32,upperF32,caller pops12,void. FirstcompareLOWERagainstvalue;storelowerONLYonORDEREDlower>value(TESTAH41/JNZskipsstoreonless/equal/unordered). OtherwisecompareUPPERagainstvalue;storeupperONLYonORDEREDupper<value(TESTAH5/JPskipsstoreon>=/unordered). ThusNaNvalueisleftUNCHANGED;NaNlowerdisableslowerclamp,NaNupperdisablesupperclamp. Doesnotnormalizeinvertedbounds:orderedvaluebelowlowerisreplacedbylowerandreturnswithoutuppercheck. No pointer/finiteguard ordefinedsuccessvalue. Existingordered-onlycommentretained;freshrawmasksrefineactualNaNbehaviorusedbytrailcountandricochetcone.
void __cdecl rf_float_clamp_in_place(float *a1, float a2, float a3)
{
  if ( a2 <= (double)*a1 )
  {
    if ( a3 < (double)*a1 )
      *a1 = a3;
  }
  else
  {
    *a1 = a2;
  }
}

