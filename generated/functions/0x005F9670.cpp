// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F9670 rf_gradient_noise_initialize_tables
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Builds shared256-entry permutation and gradient arrays using global CRT rand():p0x1F67118[i]=i,scalar gradient0x1F6A148=(rand()%512-256)/256.0;2Dgrad0x1F69138 and3Dgrad0x1F67920 get2/3 such random components then normalized via0x5F98C0/0x5F9920 WITHOUT zero-length guard. Shuffle i255down1 swaps p[i] with p[rand()%256],not shrinking-range Fisher-Yates. Copies258 entries to extension starting p+256,scalar+256,2D+256vectors,3D+256vectors. Last two source reads refer to extension entries already copied,so repeat original indices0/1. Produces duplicated tables for sums up to511. Does not seed rand,clear lazy flag0x664B84 itself or synchronize;noise callers clear flag before calling. Zero random vector can create NaN gradients.
void rf_gradient_noise_initialize_tables()
{
  int v0; // eax
  int j; // [esp+10h] [ebp-Ch]
  int k; // [esp+10h] [ebp-Ch]
  int n; // [esp+10h] [ebp-Ch]
  int ii; // [esp+10h] [ebp-Ch]
  int v5; // [esp+14h] [ebp-8h]
  int i; // [esp+18h] [ebp-4h]
  int m; // [esp+18h] [ebp-4h]

  for ( i = 0; i < 256; ++i )
  {
    dword_1F67118[i] = i;
    flt_1F6A148[i] = (double)(rand() % 512 - 256) / 256.0;
    for ( j = 0; j < 2; ++j )
      flt_1F69138[2 * i + j] = (double)(rand() % 512 - 256) / 256.0;
    rf_noise_gradient2_normalize_unchecked((float *)(8 * i + 32936248));
    for ( k = 0; k < 3; ++k )
      unk_1F67920[3 * i + k] = (double)(rand() % 512 - 256) / 256.0;
    rf_noise_gradient3_normalize_unchecked(&unk_1F67920[3 * i]);
  }
  while ( --i )
  {
    v5 = dword_1F67118[i];
    v0 = rand() % 256;
    dword_1F67118[i] = dword_1F67118[v0];
    dword_1F67118[v0] = v5;
  }
  for ( m = 0; m < 258; ++m )
  {
    unk_1F67518[m] = dword_1F67118[m];
    unk_1F6A548[m] = flt_1F6A148[m];
    for ( n = 0; n < 2; ++n )
      flt_1F69138[2 * m + 512 + n] = flt_1F69138[2 * m + n];
    for ( ii = 0; ii < 3; ++ii )
      unk_1F67920[3 * m + 768 + ii] = unk_1F67920[3 * m + ii];
  }
}

