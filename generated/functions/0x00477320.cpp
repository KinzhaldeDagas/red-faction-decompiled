// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477320 rf_flag_nibble_quadratic_attenuation
// UNREALRED VERIFIED [cutscene-playback-20261028]: Reads nibble n=(record dword+8 &0xF0000)>>16. If n==0 returns1.0; otherwise rounds n/64 through float, returns float-rounded1-(n/64)^2. No other flag bits contribute. Domain n0..15 yields positive factor; broader use of record is not established here.
double __cdecl rf_flag_nibble_quadratic_attenuation(int a1)
{
  float v2; // [esp+4h] [ebp-4h]
  float v3; // [esp+4h] [ebp-4h]

  v2 = 1.0;
  if ( (*(_DWORD *)(a1 + 8) & 0xF0000) != 0 )
  {
    v3 = (double)((*(_DWORD *)(a1 + 8) & 0xF0000u) >> 16) / 64.0;
    return (float)(1.0 - v3 * v3);
  }
  return v2;
}

