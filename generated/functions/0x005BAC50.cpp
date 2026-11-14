// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BAC50 rf_rfa_sample_morph_vertices
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Thiscall arguments: destination float3 array, nominal vertex count, integer tick, optional signed16 remap table, final unused argument. Nominal vertex count and final argument are NOT used for bounds. Raw header+28=morphed vertex count,+32=key count,+72=offset to uint16 source vertex indices,+76=offset to payload. Version SIGNED>=8: payload starts keyCount signed32 ABSOLUTE ticks, min/max float3 then packed unsigned-byte XYZ per key/vertex. Signed tick comparisons clamp to first/last or find first key.tick>sample; decode min+byte*(max-min)/255; interpolate adjacent decoded keys. Earlier versions use raw float3 payload and sampleFrame=keyCount*(tick-start)/(end-start), truncate toward0, next=min(frame+1,keyCount-1); current frame
// is NOT clamped. Exact end yields current=keyCount and can read past payload even though next is clamped. For each uint16 vertex index, optional map supplies signed16 destination; mapped negative skips write. No destination/remap/index/key-count/duration/offset bounds, no vertex normal update. Return register is incidental loop/payload value, not destination/status. CORRECTION: earlier annotation called version8 ticks unsigned; actual JG/JL/JLE branches use signed comparisons.
char *__thiscall rf_rfa_sample_morph_vertices(void *this, int a2, int a3, int a4, int a5, int a6)
{
  int end_tick; // esi
  char *result; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // [esp+Ch] [ebp-188h]
  float *v14; // [esp+14h] [ebp-180h]
  double v15; // [esp+44h] [ebp-150h]
  float v17[3]; // [esp+54h] [ebp-140h] BYREF
  float v18[3]; // [esp+60h] [ebp-134h] BYREF
  float v19[3]; // [esp+6Ch] [ebp-128h] BYREF
  int v20[3]; // [esp+78h] [ebp-11Ch] BYREF
  int v21[3]; // [esp+84h] [ebp-110h] BYREF
  float v22[3]; // [esp+90h] [ebp-104h] BYREF
  float sum_result[3]; // [esp+9Ch] [ebp-F8h] BYREF
  int v24[3]; // [esp+A8h] [ebp-ECh] BYREF
  int v25[3]; // [esp+B4h] [ebp-E0h] BYREF
  float copy_result[3]; // [esp+C0h] [ebp-D4h] BYREF
  int v27; // [esp+CCh] [ebp-C8h]
  char *k; // [esp+D0h] [ebp-C4h]
  float v29; // [esp+D4h] [ebp-C0h]
  int v30[3]; // [esp+D8h] [ebp-BCh] BYREF
  unsigned __int8 *v31; // [esp+E4h] [ebp-B0h]
  int v32[3]; // [esp+E8h] [ebp-ACh] BYREF
  unsigned __int8 *v33; // [esp+F4h] [ebp-A0h]
  int v34; // [esp+F8h] [ebp-9Ch]
  char *j; // [esp+FCh] [ebp-98h]
  unsigned __int8 *v36; // [esp+100h] [ebp-94h]
  int v37; // [esp+104h] [ebp-90h]
  int v38; // [esp+108h] [ebp-8Ch]
  int i; // [esp+10Ch] [ebp-88h]
  int v40; // [esp+110h] [ebp-84h]
  int v41; // [esp+114h] [ebp-80h]
  float lhs[3]; // [esp+118h] [ebp-7Ch] BYREF
  float *v43; // [esp+124h] [ebp-70h]
  _DWORD *v44; // [esp+128h] [ebp-6Ch]
  float *v45; // [esp+12Ch] [ebp-68h]
  float out_vector; // [esp+130h] [ebp-64h] BYREF
  float v47; // [esp+134h] [ebp-60h]
  float v48; // [esp+138h] [ebp-5Ch]
  float v49; // [esp+13Ch] [ebp-58h]
  float rhs[3]; // [esp+140h] [ebp-54h] BYREF
  int v51; // [esp+14Ch] [ebp-48h]
  int n; // [esp+150h] [ebp-44h]
  float v53; // [esp+154h] [ebp-40h]
  char *v54; // [esp+158h] [ebp-3Ch]
  char *v55; // [esp+15Ch] [ebp-38h]
  int v56; // [esp+160h] [ebp-34h]
  char *m; // [esp+164h] [ebp-30h]
  char *v58; // [esp+168h] [ebp-2Ch]
  char *v59; // [esp+16Ch] [ebp-28h]
  int v60; // [esp+170h] [ebp-24h]
  int v61; // [esp+174h] [ebp-20h]
  int v62; // [esp+178h] [ebp-1Ch]
  float v63; // [esp+17Ch] [ebp-18h]
  float v64; // [esp+180h] [ebp-14h]
  int *raw_buffer; // [esp+184h] [ebp-10h]
  int v66; // [esp+188h] [ebp-Ch]
  char *v67; // [esp+18Ch] [ebp-8h]
  int v68; // [esp+190h] [ebp-4h]

  raw_buffer = (int *)rf_rfa_get_or_load_raw_buffer(this);
  v66 = raw_buffer[7];
  v68 = raw_buffer[8];
  v67 = (char *)raw_buffer + raw_buffer[18];
  if ( raw_buffer[1] >= 8 )
  {
    v44 = (int *)((char *)raw_buffer + raw_buffer[19]);
    if ( a4 > *v44 )
    {
      if ( a4 < v44[v68 - 1] )
      {
        for ( i = 0; i < v68 && v44[i] <= a4; ++i )
          ;
        v40 = i - 1;
        v41 = i;
        v37 = v44[i] - v44[i - 1];
        v38 = a4 - v44[i - 1];
        v49 = (double)v38 / (double)v37;
      }
      else
      {
        v41 = v68 - 1;
        v40 = v68 - 1;
        v49 = 0.0;
      }
    }
    else
    {
      v41 = 0;
      v40 = 0;
      v49 = 0.0;
    }
    v45 = (float *)((char *)&raw_buffer[v68] + raw_buffer[19]);
    rf_vector3_copy_return_destination(rhs, v45);
    rf_vector3_copy_return_destination(lhs, v45 + 3);
    rf_vector_subtract(lhs, &out_vector, rhs);
    out_vector = out_vector / 255.0;
    v47 = v47 / 255.0;
    v48 = v48 / 255.0;
    v43 = v45 + 6;
    if ( v40 == v41 )
    {
      v36 = (unsigned __int8 *)v43 + 3 * v66 * v40;
      for ( j = nullptr; ; ++j )
      {
        result = j;
        if ( (int)j >= v66 )
          break;
        v34 = *(unsigned __int16 *)&v67[2 * (_DWORD)j];
        if ( a5 )
          v34 = *(__int16 *)(a5 + 2 * v34);
        if ( v34 > -1 )
        {
          *(float *)(a2 + 12 * v34) = (double)*v36 * out_vector + rhs[0];
          *(float *)(a2 + 12 * v34 + 4) = (double)v36[1] * v47 + rhs[1];
          *(float *)(a2 + 12 * v34 + 8) = (double)v36[2] * v48 + rhs[2];
        }
        v36 += 3;
      }
    }
    else
    {
      v29 = 1.0 - v49;
      v33 = (unsigned __int8 *)v43 + 3 * v66 * v40;
      v31 = (unsigned __int8 *)v43 + 3 * v66 * v41;
      rf_vector3_default_construct_noop(v32);
      rf_vector3_default_construct_noop(v30);
      for ( k = nullptr; ; ++k )
      {
        result = k;
        if ( (int)k >= v66 )
          break;
        v27 = *(unsigned __int16 *)&v67[2 * (_DWORD)k];
        if ( a5 )
          v27 = *(__int16 *)(a5 + 2 * v27);
        if ( v27 > -1 )
        {
          *(float *)v32 = (double)*v33 * out_vector;
          *(float *)&v32[1] = (double)v33[1] * v47;
          *(float *)&v32[2] = (double)v33[2] * v48;
          *(float *)v30 = (double)*v31 * out_vector;
          *(float *)&v30[1] = (double)v31[1] * v47;
          *(float *)&v30[2] = (double)v31[2] * v48;
          v13 = rf_vector_scale((float *)v20, v49, (float *)v30);
          v10 = rf_vector_scale((float *)v21, v29, (float *)v32);
          v11 = rf_vector_add(v10, v19, v13);
          v12 = rf_vector_add(v11, v18, rhs);
          rf_vector_copy((float *)(a2 + 12 * v27), v17, v12);
        }
        v33 += 3;
        v31 += 3;
      }
    }
  }
  else
  {
    v15 = (double)(a4 - rf_rfa_get_start_tick(this));
    end_tick = rf_rfa_get_end_tick(this);
    v63 = v15 / (double)(end_tick - rf_rfa_get_start_tick(this));
    v63 = (double)v68 * v63;
    v61 = (int)v63;
    v60 = v61;
    v62 = v61 + 1;
    if ( v61 + 1 > v68 - 1 )
      v62 = v68 - 1;
    v64 = v63 - (double)v61;
    v59 = (char *)raw_buffer + raw_buffer[19];
    if ( v60 == v62 )
    {
      v58 = &v59[12 * v66 * v60];
      for ( m = nullptr; ; ++m )
      {
        result = m;
        if ( (int)m >= v66 )
          break;
        v56 = *(unsigned __int16 *)&v67[2 * (_DWORD)m];
        if ( a5 )
          v56 = *(__int16 *)(a5 + 2 * v56);
        if ( v56 > -1 )
          rf_vector_copy((float *)(a2 + 12 * v56), copy_result, (const float *)&v58[12 * (_DWORD)m]);
      }
    }
    else
    {
      v53 = 1.0 - v64;
      result = &v59[12 * v66 * v60];
      v55 = result;
      v54 = &v59[12 * v66 * v62];
      for ( n = 0; n < v66; ++n )
      {
        v51 = *(unsigned __int16 *)&v67[2 * n];
        if ( a5 )
          v51 = *(__int16 *)(a5 + 2 * v51);
        if ( v51 > -1 )
        {
          v14 = rf_vector_scale((float *)v24, v64, (float *)&v54[12 * n]);
          v8 = rf_vector_scale((float *)v25, v53, (float *)&v55[12 * n]);
          v9 = rf_vector_add(v8, sum_result, v14);
          rf_vector_copy((float *)(a2 + 12 * v51), v22, v9);
        }
        result = (char *)(n + 1);
      }
    }
  }
  return result;
}

