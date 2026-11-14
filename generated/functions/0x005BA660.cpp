// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA660 rf_rfa_sample_rotation_track
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Resolves raw-relative track table at+80+4*index. Signed16 rotation-key count at track+4, keys begin+8,stride16: signed tick+0,quaternion four s16 at+4,ease-in signed byte+12,ease-out signed byte+13. Zero count writes float identity(0,0,0,1). Nonzero: sample<=first selects pair0/1,t=0; sample>=last selects count-2/count-1,t=1; interior finds first key.tick>sample using SIGNED comparisons and divides integer tick differences. Negative previous index takes direct last-key unpack. Otherwise applies easing5BA870(t,previous.easeOut/127,next.easeIn/127), packed-quaternion interpolation584060, then s16-to-float decode41F160. Does NOT normalize final quaternion. Single-key sample<=first still accesses second key through interpolation;
// later sample takes direct key0. No negative-count, sorted-time, denominator, offset or buffer bound validation. Returns output float[4].
float *__thiscall rf_rfa_sample_rotation_track(void *this, float *a2, int a3, int a4)
{
  float v5; // [esp+10h] [ebp-60h]
  float v6; // [esp+18h] [ebp-58h]
  __int16 v7[4]; // [esp+24h] [ebp-4Ch] BYREF
  float v8; // [esp+2Ch] [ebp-44h]
  int v9; // [esp+30h] [ebp-40h]
  int v10; // [esp+34h] [ebp-3Ch]
  unsigned __int8 *v11; // [esp+38h] [ebp-38h]
  unsigned __int8 *v12; // [esp+3Ch] [ebp-34h]
  unsigned __int8 *raw_buffer; // [esp+40h] [ebp-30h]
  float v14; // [esp+44h] [ebp-2Ch]
  unsigned __int8 *v15; // [esp+48h] [ebp-28h]
  float v16[4]; // [esp+4Ch] [ebp-24h] BYREF
  int v17; // [esp+5Ch] [ebp-14h]
  int v18; // [esp+60h] [ebp-10h]
  int v19; // [esp+64h] [ebp-Ch]
  int i; // [esp+68h] [ebp-8h]
  unsigned __int8 *v21; // [esp+6Ch] [ebp-4h]

  raw_buffer = rf_rfa_get_or_load_raw_buffer(this);
  v21 = &raw_buffer[*(_DWORD *)&raw_buffer[4 * a3 + 80]];
  v18 = *((__int16 *)v21 + 2);
  if ( v18 )
  {
    v15 = v21 + 8;
    i = 0;
    if ( a4 > *((_DWORD *)v21 + 2) )
    {
      if ( a4 < *(_DWORD *)&v15[16 * v18 - 16] )
      {
        for ( i = 0; i < v18 && *(_DWORD *)&v15[16 * i] <= a4; ++i )
          ;
        v12 = &v15[16 * i - 16];
        v11 = &v15[16 * i];
        v9 = *(_DWORD *)v11 - *(_DWORD *)v12;
        v10 = a4 - *(_DWORD *)v12;
        v14 = (double)v10 / (double)v9;
      }
      else
      {
        i = v18 - 1;
        v14 = 1.0;
      }
    }
    else
    {
      i = 1;
      v14 = 0.0;
    }
    rf_float4_construct_zero_zero_zero_one(v16);
    v17 = i - 1;
    v19 = i;
    if ( i - 1 >= 0 )
    {
      v8 = v14;
      if ( v17 != v19 )
      {
        v6 = (double)(char)v15[16 * v19 + 12] / 127.0;
        v5 = (double)(char)v15[16 * v17 + 13] / 127.0;
        v8 = rf_rfa_remap_key_alpha_ease(v8, v5, v6);
      }
      rf_short_quaternion_construct_0001(v7);
      rf_short_quaternion_interpolate_wrapped(v7, (__int16 *)&v15[16 * v17 + 4], &v15[16 * v19 + 4], v8);
      rf_snapshot_unpack_quaternion_s16(v16, v7);
    }
    else
    {
      rf_snapshot_unpack_quaternion_s16(v16, (__int16 *)&v15[16 * v19 + 4]);
    }
    rf_float4_assign_components_return_this(a2, v16);
    return a2;
  }
  else
  {
    rf_float4_construct_components(a2, 0.0, 0.0, 0.0, 1.0);
    return a2;
  }
}

