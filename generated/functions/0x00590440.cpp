// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590440 rf_dsound_volume_float_to_lookup_value
// UNREALRED VERIFIED [dsound-buffers-20261028]: Quantizes float to int(value*100+0.5),clamps integer0..100. If BOTH globals0x193BBE0 and0x1BA1811 nonzero,returns LUT DWORD0x1951670[index],otherwise0x19514D8[index]. No logarithm in body or finite-input validation; caller caches original unclamped float separately.
int __cdecl rf_dsound_volume_float_to_lookup_value(float a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = (int)(a1 * 100.0 + 0.5);
  if ( v2 > 100 )
    v2 = 100;
  if ( v2 < 0 )
    v2 = 0;
  if ( unk_193BBE0 && unk_1BA1811 )
    return dword_1951670[v2];
  else
    return unk_19514D8[v2];
}

