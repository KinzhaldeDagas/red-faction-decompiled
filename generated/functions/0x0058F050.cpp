// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F050 rf_dsound_build_volume_lookup_tables
// UNREALRED VERIFIED [dsound-creation-20261028]: Builds101-entry table0x1951670: int((1-i/100.0)*-10000+0.5) for i0..100. Default table0x19514D8 sets index0=-10000; indices1..100 use float-rounded log(i/100)/log(2)*1000+0.5 then integer truncation. Actual log wrapper0x591780 delegates natural-log leaf0x5917A0. The two tables differ substantially and negative-value +0.5 rounding is asymmetric. Does not select active table;0x590440 chooses according to globals.
void rf_dsound_build_volume_lookup_tables()
{
  double v0; // [esp+4h] [ebp-10h]
  int i; // [esp+Ch] [ebp-8h]
  int j; // [esp+Ch] [ebp-8h]
  float v3; // [esp+10h] [ebp-4h]

  for ( i = 0; i <= 100; ++i )
    dword_1951670[i] = (int)((1.0 - (double)i / 100.0) * -10000.0 + 0.5);
  unk_19514D8[0] = -10000;
  for ( j = 1; j <= 100; ++j )
  {
    v3 = (double)j / 100.0;
    v0 = log(v3);
    unk_19514D8[j] = (int)(v0 / log(2.0) * 1000.0 + 0.5);
  }
}

