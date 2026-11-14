// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A7420 rf_replication_decode_hit_samples
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(payload,optional entity). Reads unsigned countBYTE; count>32 returns-1 before changing entity; redundant count>=0 test always passes. Valid
// count: nonnull entity unguardedly dereferences motion buffer+632 and clears its countDWORD2300. Consumes count triples(idBYTE,raw sampleWORD); nonnull entity appends to byte
// array2200 and WORD array2232 while signed stored count<32, then increments stored count. NULL entity still consumes/validates count and triples without storing. Nonnull entity
// always stamps motion-buffer DWORD2296 with performanceClock(1000), even count0. Returns1+3*count. No payload size/null/entity-buffer validation, ID ownership check or rollback
// after earlier writes.
int __cdecl rf_replication_decode_hit_samples(unsigned __int8 *a1, int a2)
{
  __int16 v3; // [esp+0h] [ebp-14h]
  unsigned __int8 v4; // [esp+7h] [ebp-Dh]
  int i; // [esp+8h] [ebp-Ch]
  int v6; // [esp+Ch] [ebp-8h]
  int v7; // [esp+Ch] [ebp-8h]
  unsigned __int8 v8; // [esp+13h] [ebp-1h]

  v8 = *a1;
  v6 = 1;
  if ( *a1 > 0x20u )
    return -1;
  if ( a2 )
    *(_DWORD *)(*(_DWORD *)(a2 + 632) + 2300) = 0;
  for ( i = 0; i < v8; ++i )
  {
    v4 = a1[v6];
    v7 = v6 + 1;
    v3 = *(_WORD *)&a1[v7];
    v6 = v7 + 2;
    if ( a2 )
    {
      if ( *(int *)(*(_DWORD *)(a2 + 632) + 2300) < 32 )
      {
        *(_BYTE *)(*(_DWORD *)(a2 + 632) + *(_DWORD *)(*(_DWORD *)(a2 + 632) + 2300) + 2200) = v4;
        *(_WORD *)(*(_DWORD *)(a2 + 632) + 2 * (*(_DWORD *)(*(_DWORD *)(a2 + 632) + 2300))++ + 2232) = v3;
      }
    }
  }
  if ( a2 )
    *(_DWORD *)(*(_DWORD *)(a2 + 632) + 2296) = rf_performance_clock_elapsed_scaled(1000);
  return v6;
}

