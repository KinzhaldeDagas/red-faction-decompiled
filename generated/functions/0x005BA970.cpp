// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BA970 rf_rfa_sample_translation_track
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Track offset from raw+80+4*index; signed16 position-key count at track+6. Keys begin track+8+16*rotationKeyCount, stride40: signed tick+0,position+4,incoming control vector+16,outgoing control+28. Zero count returns zero vector. Samples<=first or>=last copy endpoint position. Interior scans first key with signed tick>sample, t=(sample-prev.tick)/(next.tick-prev.tick),u=1-t; evaluates cubic Bezier prev.pos*u^3 + prev.out*3*t*u^2 + next.in*3*t^2*u + next.pos*t^3 through vector temporaries. No easing remap here, no offset/count/order/zero-duration checks. Returns output vector; source controls are not derivative vectors multiplied by interval.
float *__thiscall rf_rfa_sample_translation_track(void *this, float *a2, int a3, int a4)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float v19; // [esp+8h] [ebp-144h]
  float v20; // [esp+8h] [ebp-144h]
  float v21; // [esp+10h] [ebp-13Ch]
  float v22; // [esp+10h] [ebp-13Ch]
  float v23; // [esp+10h] [ebp-13Ch]
  float scalar; // [esp+18h] [ebp-134h]
  float scalara; // [esp+18h] [ebp-134h]
  float *scalarb; // [esp+18h] [ebp-134h]
  float v27; // [esp+20h] [ebp-12Ch]
  float v28; // [esp+20h] [ebp-12Ch]
  float *v29; // [esp+20h] [ebp-12Ch]
  float v30; // [esp+28h] [ebp-124h]
  float *v31; // [esp+28h] [ebp-124h]
  float copy_result[3]; // [esp+30h] [ebp-11Ch] BYREF
  float v33[3]; // [esp+3Ch] [ebp-110h] BYREF
  float v34[3]; // [esp+48h] [ebp-104h] BYREF
  float v35[3]; // [esp+54h] [ebp-F8h] BYREF
  float scaled_result[3]; // [esp+60h] [ebp-ECh] BYREF
  float v37[3]; // [esp+6Ch] [ebp-E0h] BYREF
  float v38[3]; // [esp+78h] [ebp-D4h] BYREF
  float v39[3]; // [esp+84h] [ebp-C8h] BYREF
  float v40[3]; // [esp+90h] [ebp-BCh] BYREF
  float v41[3]; // [esp+9Ch] [ebp-B0h] BYREF
  float sum_result[3]; // [esp+A8h] [ebp-A4h] BYREF
  float v43[3]; // [esp+B4h] [ebp-98h] BYREF
  float v44[3]; // [esp+C0h] [ebp-8Ch] BYREF
  float v45[3]; // [esp+CCh] [ebp-80h] BYREF
  float v46[3]; // [esp+D8h] [ebp-74h] BYREF
  float v47[3]; // [esp+E4h] [ebp-68h] BYREF
  float v48[3]; // [esp+F0h] [ebp-5Ch] BYREF
  float v49[3]; // [esp+FCh] [ebp-50h] BYREF
  int v50; // [esp+108h] [ebp-44h]
  unsigned __int8 *raw_buffer; // [esp+10Ch] [ebp-40h]
  int v52; // [esp+110h] [ebp-3Ch]
  int v53; // [esp+114h] [ebp-38h]
  int v54; // [esp+118h] [ebp-34h]
  int v55; // [esp+11Ch] [ebp-30h]
  int v56; // [esp+120h] [ebp-2Ch]
  float destination[3]; // [esp+124h] [ebp-28h] BYREF
  int v58; // [esp+130h] [ebp-1Ch]
  int v59; // [esp+134h] [ebp-18h]
  float v60; // [esp+138h] [ebp-14h]
  int i; // [esp+13Ch] [ebp-10h]
  int v62; // [esp+140h] [ebp-Ch]
  float v63; // [esp+144h] [ebp-8h]
  unsigned __int8 *v64; // [esp+148h] [ebp-4h]

  v54 = 16;
  v55 = 40;
  v62 = 8;
  raw_buffer = rf_rfa_get_or_load_raw_buffer(this);
  v64 = &raw_buffer[*(_DWORD *)&raw_buffer[4 * a3 + 80]];
  v52 = *((__int16 *)v64 + 3);
  if ( v52 )
  {
    v58 = (int)&v64[16 * *((__int16 *)v64 + 2) + 8];
    if ( a4 > *(_DWORD *)v58 )
    {
      if ( a4 < *(_DWORD *)(v58 + 40 * (v52 - 1)) )
      {
        for ( i = 0; i < v52 && *(_DWORD *)(v58 + 40 * i) <= a4; ++i )
          ;
        v59 = v58 + 40 * (i - 1);
        v56 = v58 + 40 * i;
        v50 = *(_DWORD *)v56 - *(_DWORD *)v59;
        v53 = a4 - *(_DWORD *)v59;
        v60 = (double)v53 / (double)v50;
        rf_vector3_default_construct_noop(destination);
        v63 = 1.0 - v60;
        v30 = v60;
        v27 = v60;
        v5 = rf_vector_multiply_scalar((const float *)(v56 + 4), scaled_result, v60);
        v6 = rf_vector_multiply_scalar(v5, v35, v27);
        v31 = rf_vector_multiply_scalar(v6, v34, v30);
        v28 = v63;
        scalar = v60;
        v21 = v60;
        v7 = rf_vector_multiply_scalar((const float *)(v56 + 16), v41, 3.0);
        v8 = rf_vector_multiply_scalar(v7, v40, v21);
        v9 = rf_vector_multiply_scalar(v8, v39, scalar);
        v29 = rf_vector_multiply_scalar(v9, v38, v28);
        scalara = v63;
        v22 = v63;
        v19 = v60;
        v10 = rf_vector_multiply_scalar((const float *)(v59 + 28), v46, 3.0);
        v11 = rf_vector_multiply_scalar(v10, v45, v19);
        v12 = rf_vector_multiply_scalar(v11, v44, v22);
        scalarb = rf_vector_multiply_scalar(v12, v43, scalara);
        v23 = v63;
        v20 = v63;
        v13 = rf_vector_multiply_scalar((const float *)(v59 + 4), v49, v63);
        v14 = rf_vector_multiply_scalar(v13, v48, v20);
        v15 = rf_vector_multiply_scalar(v14, v47, v23);
        v16 = rf_vector_add(v15, sum_result, scalarb);
        v17 = rf_vector_add(v16, v37, v29);
        v18 = rf_vector_add(v17, v33, v31);
        rf_vector_copy(destination, copy_result, v18);
        rf_vector3_copy_return_destination(a2, destination);
        return a2;
      }
      else
      {
        rf_vector3_copy_return_destination(a2, (float *)(v58 + 40 * (v52 - 1) + 4));
        return a2;
      }
    }
    else
    {
      rf_vector3_copy_return_destination(a2, (float *)(v58 + 4));
      return a2;
    }
  }
  else
  {
    rf_vector3_set_components_return_destination(a2, 0.0, 0.0, 0.0);
    return a2;
  }
}

