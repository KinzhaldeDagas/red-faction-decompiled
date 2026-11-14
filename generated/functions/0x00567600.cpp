// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567600 rf_initialize_sqrt_rsqrt_lookup_tables_once
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): If byte1808938 already set,does nothing and EAX unspecified. Otherwise sets byte1 BEFORE filling both1024DWORD BSS tables, no lock. Fori0..1023,sampleFloat bits=(i<<14)|3F000000,covering exponent-parity/mantissa range[0.5,2). First table1807938 takes float reciprocal sqrt sample,stores mantissa bits13..22,except exact1 stores007FE000. Second1806938 stores sqrt mantissa bits13..22,exact1 stores0. No exponent stored in entries; lookup helpers reconstruct it separately. Uses CRT sqrt,not lookup recursion; final EAX loopcount.
int rf_initialize_sqrt_rsqrt_lookup_tables_once()
{
  int result; // eax
  float v1; // [esp+0h] [ebp-18h]
  float v2; // [esp+4h] [ebp-14h]
  float v3; // [esp+Ch] [ebp-Ch]
  int i; // [esp+14h] [ebp-4h]
  int j; // [esp+14h] [ebp-4h]

  if ( !unk_1808938 )
  {
    unk_1808938 = 1;
    for ( i = 0; i < 1024; ++i )
    {
      v1 = sqrt(COERCE_FLOAT(((i & 0x3FF) << 14) | COERCE_UNSIGNED_INT(1.0) & 0xFF003FFF));
      v3 = 1.0 / v1;
      if ( v3 == 1.0 )
        dword_1807938[i] = (int)&unk_7FE000;
      else
        dword_1807938[i] = ((LODWORD(v3) >> 13) & 0x3FF) << 13;
      result = i + 1;
    }
    for ( j = 0; j < 1024; ++j )
    {
      v2 = sqrt(COERCE_FLOAT(((j & 0x3FF) << 14) | COERCE_UNSIGNED_INT(1.0) & 0xFF003FFF));
      if ( v2 == 1.0 )
        dword_1806938[j] = 0;
      else
        dword_1806938[j] = ((LODWORD(v2) >> 13) & 0x3FF) << 13;
      result = j + 1;
    }
  }
  return result;
}

