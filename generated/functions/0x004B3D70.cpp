// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B3D70 rf_entity_sample_buffered_euler_and_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Stdcall(entity,queryWORD,outMatrix,outEuler,outOffset),RET20;buffer632 required nonNULL. Count<2 or locator3570 failure copies current entityEuler2148 and viewoffset2172. Locator success index==count-1 first copies last Euler array240 and offset array480 DIRECTLY;this shortcut avoids i+1 read. Otherwise curveParameter>=0 OR unordered AND <=count-1 OR unordered enters independent componentwise lerps of arrays240/480 at i andi+1 using fraction. No shortest-angle path,wrap,clamp or quaternion interpolation;NaN parameter enters lerp. Range-miss with signed count1..20 copies last vectors,invalid count uses current entityEuler/offset. Always constructs outMatrix using
// Euler(pitch=outEulerX,bank=outEulerZ,heading=outEulerY),returns matrix helperEAX. No own pointer/index/count/finite validation on primary paths;every normal branch writes all outputs.
float *__stdcall rf_entity_sample_buffered_euler_and_offset(
        int a1,
        unsigned __int16 a2,
        float *a3,
        float *destination,
        float *a5)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float scalar; // [esp+8h] [ebp-120h]
  float scalara; // [esp+8h] [ebp-120h]
  float v14[3]; // [esp+10h] [ebp-118h] BYREF
  float v15[3]; // [esp+1Ch] [ebp-10Ch] BYREF
  float v16[3]; // [esp+28h] [ebp-100h] BYREF
  float v17[3]; // [esp+34h] [ebp-F4h] BYREF
  float v18[3]; // [esp+40h] [ebp-E8h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-DCh] BYREF
  float scaled_result[3]; // [esp+58h] [ebp-D0h] BYREF
  float out_vector[3]; // [esp+64h] [ebp-C4h] BYREF
  float v22[3]; // [esp+70h] [ebp-B8h] BYREF
  float v23[3]; // [esp+7Ch] [ebp-ACh] BYREF
  float v24[3]; // [esp+88h] [ebp-A0h] BYREF
  float v25[3]; // [esp+94h] [ebp-94h] BYREF
  float v26[3]; // [esp+A0h] [ebp-88h] BYREF
  float v27[3]; // [esp+ACh] [ebp-7Ch] BYREF
  float v28[3]; // [esp+B8h] [ebp-70h] BYREF
  float v29[3]; // [esp+C4h] [ebp-64h] BYREF
  float v30[3]; // [esp+D0h] [ebp-58h] BYREF
  float copy_result[3]; // [esp+DCh] [ebp-4Ch] BYREF
  float v32[3]; // [esp+E8h] [ebp-40h] BYREF
  float rhs[3]; // [esp+F4h] [ebp-34h] BYREF
  float v34[3]; // [esp+100h] [ebp-28h] BYREF
  float lhs[3]; // [esp+10Ch] [ebp-1Ch] BYREF
  int v36; // [esp+118h] [ebp-10h]
  float v37; // [esp+11Ch] [ebp-Ch] BYREF
  int v38; // [esp+120h] [ebp-8h] BYREF
  float v39; // [esp+124h] [ebp-4h] BYREF

  if ( *(int *)(*(_DWORD *)(a1 + 632) + 1332) >= 2 )
  {
    if ( rf_motion_samples_locate_time_segment(*(_DWORD *)(a1 + 632), a2, &v38, &v39, &v37) )
    {
      if ( v38 == *(_DWORD *)(*(_DWORD *)(a1 + 632) + 1332) - 1 )
      {
        rf_vector_copy(destination, v27, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v38 + 240));
        rf_vector_copy(a5, v26, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v38 + 480));
      }
      else if ( v37 >= 0.0 && v37 <= (double)*(int *)(*(_DWORD *)(a1 + 632) + 1332) - 1.0 )
      {
        rf_vector3_copy_return_destination(rhs, (float *)(*(_DWORD *)(a1 + 632) + 12 * v38 + 240));
        rf_vector3_copy_return_destination(lhs, (float *)(*(_DWORD *)(a1 + 632) + 12 * (v38 + 1) + 240));
        scalar = v39;
        v5 = rf_vector_subtract(lhs, out_vector, rhs);
        v6 = rf_vector_multiply_scalar(v5, scaled_result, scalar);
        v7 = rf_vector_add(rhs, sum_result, v6);
        rf_vector_copy(destination, v18, v7);
        rf_vector3_copy_return_destination(v34, (float *)(*(_DWORD *)(a1 + 632) + 12 * v38 + 480));
        rf_vector3_copy_return_destination(v32, (float *)(*(_DWORD *)(a1 + 632) + 12 * (v38 + 1) + 480));
        scalara = v39;
        v8 = rf_vector_subtract(v32, v17, v34);
        v9 = rf_vector_multiply_scalar(v8, v16, scalara);
        v10 = rf_vector_add(v34, v15, v9);
        rf_vector_copy(a5, v14, v10);
      }
      else if ( *(int *)(*(_DWORD *)(a1 + 632) + 1332) <= 0 || *(int *)(*(_DWORD *)(a1 + 632) + 1332) > 20 )
      {
        rf_vector_copy(destination, v23, (const float *)(a1 + 2148));
        rf_vector_copy(a5, v22, (const float *)(a1 + 2172));
      }
      else
      {
        v36 = *(_DWORD *)(*(_DWORD *)(a1 + 632) + 1332) - 1;
        rf_vector_copy(destination, v25, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v36 + 240));
        rf_vector_copy(a5, v24, (const float *)(*(_DWORD *)(a1 + 632) + 12 * v36 + 480));
      }
    }
    else
    {
      rf_vector_copy(destination, v29, (const float *)(a1 + 2148));
      rf_vector_copy(a5, v28, (const float *)(a1 + 2172));
    }
  }
  else
  {
    rf_vector_copy(destination, copy_result, (const float *)(a1 + 2148));
    rf_vector_copy(a5, v30, (const float *)(a1 + 2172));
  }
  return rf_matrix3_set_euler_angles(a3, *destination, destination[2], destination[1]);
}

