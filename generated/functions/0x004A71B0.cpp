// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A71B0 rf_replication_encode_forward_hit_samples
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, networking packet registry and native codecs, motion history, original mask/quantization constants and native
// signed/x87/stack/callback ABI): cdecl(destination pointer only consumed); callers also push ignored entity argument. If global local entity681E38 isNULL writes countBYTE0,
// returns1. Else walks circular player list87C324, skips local player, requires net4608 nonnull, resolved entity from player+20 and motion buffer entity+632 nonnull. Normalizes
// candidatePos60-localPos60, computes dot with local entity+2040 and stores binary32; ordered thresholdFLOAT662C2C<=dot admits (original threshold0.5). Collects player net BYTE20 and
// motion-buffer WORD1324 into stack arrays using unsigned BYTE count; increments BYTE without capacity guard. ONLY AFTER collection caps count to32; earlier array overrun/count wrap
// is not prevented. Emits countBYTE plus repeated(idBYTE,sampleWORD), packed little endian, returns1+3*count. No distance/occlusion/connection-state/team/death gate or destination
// capacity. Count/max32 does not change one-byte peer ID or raw low16 sample.
int __cdecl rf_replication_encode_forward_hit_samples(int a1)
{
  float *v2; // eax
  _DWORD *v3; // [esp+0h] [ebp-B0h]
  float copy_result[3]; // [esp+4h] [ebp-ACh] BYREF
  float out_vector[3]; // [esp+10h] [ebp-A0h] BYREF
  __int16 v6; // [esp+1Ch] [ebp-94h]
  char v7; // [esp+21h] [ebp-8Fh]
  unsigned __int8 v8; // [esp+22h] [ebp-8Eh]
  unsigned __int8 v9; // [esp+23h] [ebp-8Dh]
  int v10; // [esp+24h] [ebp-8Ch]
  float destination[3]; // [esp+28h] [ebp-88h] BYREF
  int j; // [esp+34h] [ebp-7Ch]
  _BYTE v13[32]; // [esp+38h] [ebp-78h]
  _DWORD *i; // [esp+58h] [ebp-58h]
  unsigned __int8 v15; // [esp+5Fh] [ebp-51h]
  _WORD v16[34]; // [esp+60h] [ebp-50h]
  float v17; // [esp+A8h] [ebp-8h]
  int v18; // [esp+ACh] [ebp-4h]

  v15 = 0;
  v10 = 0;
  if ( dword_681E38 )
  {
    rf_vector3_default_construct_noop(destination);
    for ( i = (_DWORD *)dword_87C324; i; i = v3 )
    {
      if ( i != (_DWORD *)rf_local_fpgun_player )
      {
        if ( i[1152] )
        {
          v18 = rf_entity_resolve_handle(i[5]);
          if ( v18 )
          {
            if ( *(_DWORD *)(v18 + 632) )
            {
              v2 = rf_vector_subtract((const float *)(v18 + 60), out_vector, (const float *)(dword_681E38 + 60));
              rf_vector_copy(destination, copy_result, v2);
              rf_vector_normalize_reciprocal_sqrt(destination);
              v17 = rf_vector_dot((float *)(dword_681E38 + 2040), destination);
              if ( flt_662C2C <= (double)v17 )
              {
                v13[v15] = *(_BYTE *)(i[1152] + 20);
                v16[v15++] = *(_WORD *)(*(_DWORD *)(v18 + 632) + 1324);
              }
            }
          }
        }
      }
      if ( *i == dword_87C324 )
        v3 = nullptr;
      else
        v3 = (_DWORD *)*i;
    }
    if ( v15 > 0x20u )
      v15 = 32;
    v8 = v15;
    *(_BYTE *)(v10 + a1) = v15;
    ++v10;
    for ( j = 0; j < v15; ++j )
    {
      v7 = v13[j];
      *(_BYTE *)(v10 + a1) = v7;
      ++v10;
      v6 = v16[j];
      *(_WORD *)(v10 + a1) = v6;
      v10 += 2;
    }
    return v10;
  }
  else
  {
    v9 = v15;
    *(_BYTE *)(v10 + a1) = v15;
    return v10 + 1;
  }
}

