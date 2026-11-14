// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7CA0 rf_clip_make_intersection_vertex_extended_uv
// UNREALRED VERIFIED [extended-clip-20261028]: Allocates132-byte scratch vertex via unchecked0x5C81F0. Arguments plane bits,inside endpoint,outside endpoint,attribute mask. Plane precedence2(far z0x18CD370),1(near z0x18CD37C),0x40(custom point0x18CD5DC and normal0x18CD5F4),then lateral. Near/far t=(plane_z-inside.z)/(outside.z-inside.z),denominator0 selects t1. Custom t=-dot(normal,inside-point)/dot(normal,outside-inside),parallel also t1. Lateral bits4/8 use x,16/32 use y; bits4/16 negate coordinate,force output z to signed interpolated axis,and divide without zero guard. No t clamp. Always interpolates float channels at+32+4*i and+80+4*i for i<count from inside DWORD+28,copies count to output+28; attribute mask1/2 does not gate UV channels here. No count<=12 check or endpoint-count equality check. Mask4 interpolates RGB bytes128..130 with integer conversion. Mask8 handles alpha byte131:
// far plane plus global0x18CD368 and outside alpha0 forces0; near plane chooses max endpoint alpha; otherwise linear interpolation. Unrequested attributes stay stale. Calls0x581780 to refresh outcode byte24; return allocated vertex. No allocation failure check.
float *__cdecl rf_clip_make_intersection_vertex_extended_uv(char a1, float *rhs, float *lhs, char a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float scalar; // [esp+0h] [ebp-F4h]
  char v11; // [esp+Fh] [ebp-E5h]
  float v12[3]; // [esp+28h] [ebp-CCh] BYREF
  float sum_result[3]; // [esp+34h] [ebp-C0h] BYREF
  float scaled_result[3]; // [esp+40h] [ebp-B4h] BYREF
  float v15[3]; // [esp+4Ch] [ebp-A8h] BYREF
  float v16[3]; // [esp+58h] [ebp-9Ch] BYREF
  float v17[3]; // [esp+64h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+70h] [ebp-84h] BYREF
  float out_vector[3]; // [esp+7Ch] [ebp-78h] BYREF
  float v20; // [esp+88h] [ebp-6Ch]
  float v21; // [esp+8Ch] [ebp-68h]
  float v22; // [esp+90h] [ebp-64h]
  float v23; // [esp+94h] [ebp-60h]
  float v24; // [esp+98h] [ebp-5Ch]
  float v25; // [esp+9Ch] [ebp-58h]
  float v26; // [esp+A0h] [ebp-54h]
  float v27; // [esp+A4h] [ebp-50h]
  float v28; // [esp+A8h] [ebp-4Ch]
  float v29; // [esp+ACh] [ebp-48h]
  float v30; // [esp+B0h] [ebp-44h]
  float v31; // [esp+B4h] [ebp-40h]
  float destination[3]; // [esp+B8h] [ebp-3Ch] BYREF
  float v33; // [esp+C4h] [ebp-30h]
  float v34[3]; // [esp+C8h] [ebp-2Ch] BYREF
  float v35; // [esp+D4h] [ebp-20h]
  float v36; // [esp+D8h] [ebp-1Ch]
  float v37; // [esp+DCh] [ebp-18h]
  float v38; // [esp+E0h] [ebp-14h]
  float v39; // [esp+E4h] [ebp-10h]
  float *v40; // [esp+E8h] [ebp-Ch]
  int i; // [esp+ECh] [ebp-8h]
  float v42; // [esp+F0h] [ebp-4h]

  v40 = (float *)rf_clip_extended_vertex_pool_allocate();
  if ( (a1 & 2) != 0 )
  {
    v38 = flt_18CD370 - rhs[2];
    v39 = lhs[2] - rhs[2];
    if ( v39 == 0.0 )
      v42 = 1.0;
    else
      v42 = v38 / v39;
    *v40 = (*lhs - *rhs) * v42 + *rhs;
    v40[1] = (lhs[1] - rhs[1]) * v42 + rhs[1];
    v40[2] = flt_18CD370;
  }
  else if ( (a1 & 1) != 0 )
  {
    v36 = flt_18CD37C - rhs[2];
    v37 = lhs[2] - rhs[2];
    if ( v37 == 0.0 )
      v42 = 1.0;
    else
      v42 = v36 / v37;
    *v40 = (*lhs - *rhs) * v42 + *rhs;
    v40[1] = (lhs[1] - rhs[1]) * v42 + rhs[1];
    v40[2] = flt_18CD37C;
  }
  else if ( (a1 & 0x40) != 0 )
  {
    rf_vector3_default_construct_noop(v34);
    rf_vector3_default_construct_noop(destination);
    v4 = rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_copy(destination, copy_result, v4);
    v5 = rf_vector_subtract(rhs, v17, unk_18CD5DC);
    rf_vector_copy(v34, v16, v5);
    v35 = -rf_vector_dot(flt_18CD5F4, destination);
    if ( v35 == 0.0 )
    {
      v42 = 1.0;
    }
    else
    {
      v33 = rf_vector_dot(flt_18CD5F4, v34);
      v42 = v33 / v35;
    }
    scalar = v42;
    v6 = rf_vector_subtract(lhs, v15, rhs);
    v7 = rf_vector_multiply_scalar(v6, scaled_result, scalar);
    v8 = rf_vector_add(rhs, sum_result, v7);
    rf_vector_copy(v40, v12, v8);
  }
  else
  {
    if ( (a1 & 0xC) != 0 )
    {
      v31 = *rhs;
      v28 = *lhs;
    }
    else
    {
      v31 = rhs[1];
      v28 = lhs[1];
    }
    if ( (a1 & 0x14) != 0 )
    {
      v31 = -v31;
      v28 = -v28;
    }
    v30 = v31 - rhs[2];
    v29 = v30 - v28 + lhs[2];
    v42 = v30 / v29;
    *v40 = (*lhs - *rhs) * v42 + *rhs;
    v40[1] = (lhs[1] - rhs[1]) * v42 + rhs[1];
    if ( (a1 & 0x30) != 0 )
      v40[2] = v40[1];
    else
      v40[2] = *v40;
    if ( (a1 & 0x14) != 0 )
      v40[2] = -v40[2];
  }
  for ( i = 0; i < *((_DWORD *)rhs + 7); ++i )
  {
    v40[i + 8] = (lhs[i + 8] - rhs[i + 8]) * v42 + rhs[i + 8];
    v40[i + 20] = (lhs[i + 20] - rhs[i + 20]) * v42 + rhs[i + 20];
  }
  v40[7] = rhs[7];
  if ( (a4 & 4) != 0 )
  {
    v22 = (float)*((unsigned __int8 *)rhs + 128);
    v25 = (float)*((unsigned __int8 *)lhs + 128);
    v24 = (float)*((unsigned __int8 *)rhs + 129);
    v26 = (float)*((unsigned __int8 *)lhs + 129);
    v23 = (float)*((unsigned __int8 *)rhs + 130);
    v27 = (float)*((unsigned __int8 *)lhs + 130);
    *((_BYTE *)v40 + 128) = (int)((v25 - v22) * v42 + v22);
    *((_BYTE *)v40 + 129) = (int)((v26 - v24) * v42 + v24);
    *((_BYTE *)v40 + 130) = (int)((v27 - v23) * v42 + v23);
  }
  if ( (a4 & 8) != 0 )
  {
    if ( unk_18CD368 && !*((_BYTE *)lhs + 131) && (a1 & 2) != 0 )
    {
      *((_BYTE *)v40 + 131) = 0;
    }
    else if ( (a1 & 1) != 0 )
    {
      if ( *((unsigned __int8 *)rhs + 131) <= (int)*((unsigned __int8 *)lhs + 131) )
        v11 = *((_BYTE *)lhs + 131);
      else
        v11 = *((_BYTE *)rhs + 131);
      *((_BYTE *)v40 + 131) = v11;
    }
    else
    {
      v21 = (float)*((unsigned __int8 *)rhs + 131);
      v20 = (float)*((unsigned __int8 *)lhs + 131);
      *((_BYTE *)v40 + 131) = (int)((v20 - v21) * v42 + v21);
    }
  }
  rf_clip_extended_vertex_update_outcode_backend((int)v40);
  return v40;
}

