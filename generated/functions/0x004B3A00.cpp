// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3A00 rf_entity_sample_buffered_position_and_velocity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Stdcall(entity,queryWORD,outPosition,outVelocity),RET16,entity buffer632 required nonNULL here. Count1332<2:outVelocity=shared vector17F10B0,outPosition=COMMON entity60,returns position-copyEAX. Otherwise locate3570 failure copies entity velocity324 and common position60. Success interpolates when curveParameter>=0 OR unordered AND curveParameter<=count-1 OR unordered;NaN enters interpolation. Uses padded curve buffer1424 for position and vector lerp of velocity samples720+12*i and720+12*(i+1),factor=stored fraction,unconditionally reading both sample vectors even fraction0. Unlike orientation sibling,NO last-index shortcut: index=count-1 still reads velocity atlogical index count;at
// count20 this aliases first vector of array960. Range miss with signed count1..20 copies last position sample0/last velocity720;invalid count<=0 OR>20 falls back common entity60/current velocity324. Upper-count guard exists ONLY in range-miss fallback,not interpolation. Returns last helperEAX bits,not success boolean. No own NULL,index/finite/clamp/curve-count checks;outputs written on normal nonfaulting paths.
float *__stdcall rf_entity_sample_buffered_position_and_velocity(
        int a1,
        unsigned __int16 a2,
        float *a3,
        float *destination)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float scalar; // [esp+0h] [ebp-C0h]
  float v9[3]; // [esp+8h] [ebp-B8h] BYREF
  float sum_result[3]; // [esp+14h] [ebp-ACh] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-A0h] BYREF
  float out_vector[3]; // [esp+2Ch] [ebp-94h] BYREF
  float v13[3]; // [esp+38h] [ebp-88h] BYREF
  float v14[3]; // [esp+44h] [ebp-7Ch] BYREF
  float v15[3]; // [esp+50h] [ebp-70h] BYREF
  float v16[3]; // [esp+5Ch] [ebp-64h] BYREF
  float v17[3]; // [esp+68h] [ebp-58h] BYREF
  float v18[3]; // [esp+74h] [ebp-4Ch] BYREF
  float v19[3]; // [esp+80h] [ebp-40h] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-34h] BYREF
  float lhs[3]; // [esp+98h] [ebp-28h] BYREF
  float rhs[3]; // [esp+A4h] [ebp-1Ch] BYREF
  int v23; // [esp+B0h] [ebp-10h]
  float v24; // [esp+B4h] [ebp-Ch] BYREF
  int v25; // [esp+B8h] [ebp-8h] BYREF
  float v26; // [esp+BCh] [ebp-4h] BYREF

  if ( *(int *)(*(_DWORD *)(a1 + 632) + 1332) >= 2 )
  {
    if ( rf_motion_samples_locate_time_segment(*(_DWORD *)(a1 + 632), a2, &v25, &v26, &v24) )
    {
      if ( v24 >= 0.0 && v24 <= (double)*(int *)(*(_DWORD *)(a1 + 632) + 1332) - 1.0 )
      {
        rf_catmull_rom32_evaluate_position((int *)(*(_DWORD *)(a1 + 632) + 1424), a3, v24);
        rf_vector3_copy_return_destination(rhs, (float *)(*(_DWORD *)(a1 + 632) + 12 * v25 + 720));
        rf_vector3_copy_return_destination(lhs, (float *)(*(_DWORD *)(a1 + 632) + 12 * (v25 + 1) + 720));
        scalar = v26;
        v5 = rf_vector_subtract(lhs, out_vector, rhs);
        v6 = rf_vector_multiply_scalar(v5, scaled_result, scalar);
        v7 = rf_vector_add(rhs, sum_result, v6);
        return rf_vector_copy(destination, v9, v7);
      }
      else if ( *(int *)(*(_DWORD *)(a1 + 632) + 1332) <= 0 || *(int *)(*(_DWORD *)(a1 + 632) + 1332) > 20 )
      {
        rf_vector_copy(a3, v14, (const float *)(a1 + 60));
        return rf_vector_copy(destination, v13, (const float *)(a1 + 324));
      }
      else
      {
        v23 = *(_DWORD *)(*(_DWORD *)(a1 + 632) + 1332) - 1;
        rf_vector_copy(a3, v16, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v23));
        return rf_vector_copy(destination, v15, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v23 + 720));
      }
    }
    else
    {
      rf_vector_copy(destination, v18, (const float *)(a1 + 324));
      return rf_vector_copy(a3, v17, (const float *)(a1 + 60));
    }
  }
  else
  {
    rf_vector_copy(destination, copy_result, flt_17F10B0);
    return rf_vector_copy(a3, v19, (const float *)(a1 + 60));
  }
}

