// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C7740 rf_clip_make_intersection_vertex_48
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, complete skinned draw path, clipping control flow, buffer limits, original x87/integer operations and caller arguments): Cdecl plane mask,inside/start vertex,outside/end vertex,attribute mask. Allocates shared48-byte record with5C7C60; NULL allocation returnsNULL before geometry/attribute writes. Computes point=start+t*(end-start),with branch priority mask2(far Z18CD370),mask1(near Z18CD37C),mask40(custom plane through18CD5DC with normal18CD5F4),else lateral. Near/far t=(planeZ-startZ)/(endZ-startZ),denominator exactly0 chooses t1; sets resultZ exactlyplaneZ. Custom t=dot(normal,start-planePoint)/(-dot(normal,end-start)),zero denominator chooses1; vector helpers evaluate float-rounded operations. Lateral picks X if mask0Ch elseY,negates chosen coordinate for
// mask14h,t=(chosenStart-startZ)/(chosenStart-startZ-chosenEnd+endZ),interpolatesXY,then setsZ to resultY for mask30h else resultX and negates Z for mask14h. Lateral denominator has NO zero guard. No one-hot plane validation,finite-value test or clamp of t to[0,1]. Attribute mask1 lerps floats28/32(UV0),mask2 lerps36/40(UV1),mask4 lerps unsigned RGB BYTE44..46 then truncates via ftol and stores low bytes without clamp. Mask8 controls alpha BYTE47: if global18CD368 nonzero AND outside alpha0 AND plane mask2,set0; else if plane mask1,setmax(startAlpha,endAlpha); else interpolate and truncate low byte. Unselected attributes remain stale from pool. Calls backend0x581750 outcode updater on result after writes and returns record; allocator sets BYTE25 exactly4 on success; backend updates BYTE24 only when renderer selector187CC9C equals102,otherwise leaves it stale. No projection/fog calculation
// in this function. Pool failure does not undo earlier intersections owned by caller.
float *__cdecl rf_clip_make_intersection_vertex_48(char a1, float *rhs, float *lhs, char a4)
{
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float scalar; // [esp+0h] [ebp-F0h]
  char v11; // [esp+Fh] [ebp-E1h]
  float v12[3]; // [esp+28h] [ebp-C8h] BYREF
  float sum_result[3]; // [esp+34h] [ebp-BCh] BYREF
  float scaled_result[3]; // [esp+40h] [ebp-B0h] BYREF
  float v15[3]; // [esp+4Ch] [ebp-A4h] BYREF
  float v16[3]; // [esp+58h] [ebp-98h] BYREF
  float v17[3]; // [esp+64h] [ebp-8Ch] BYREF
  float copy_result[3]; // [esp+70h] [ebp-80h] BYREF
  float out_vector[3]; // [esp+7Ch] [ebp-74h] BYREF
  float v20; // [esp+88h] [ebp-68h]
  float v21; // [esp+8Ch] [ebp-64h]
  float v22; // [esp+90h] [ebp-60h]
  float v23; // [esp+94h] [ebp-5Ch]
  float v24; // [esp+98h] [ebp-58h]
  float v25; // [esp+9Ch] [ebp-54h]
  float v26; // [esp+A0h] [ebp-50h]
  float v27; // [esp+A4h] [ebp-4Ch]
  float v28; // [esp+A8h] [ebp-48h]
  float v29; // [esp+ACh] [ebp-44h]
  float v30; // [esp+B0h] [ebp-40h]
  float v31; // [esp+B4h] [ebp-3Ch]
  float destination[3]; // [esp+B8h] [ebp-38h] BYREF
  float v33; // [esp+C4h] [ebp-2Ch]
  float v34[3]; // [esp+C8h] [ebp-28h] BYREF
  float v35; // [esp+D4h] [ebp-1Ch]
  float v36; // [esp+D8h] [ebp-18h]
  float v37; // [esp+DCh] [ebp-14h]
  float v38; // [esp+E0h] [ebp-10h]
  float v39; // [esp+E4h] [ebp-Ch]
  float *checked; // [esp+E8h] [ebp-8h]
  float v41; // [esp+ECh] [ebp-4h]

  checked = (float *)rf_clip_vertex48_pool_allocate_checked();
  if ( !checked )
    return nullptr;
  if ( (a1 & 2) != 0 )
  {
    v38 = flt_18CD370 - rhs[2];
    v39 = lhs[2] - rhs[2];
    if ( v39 == 0.0 )
      v41 = 1.0;
    else
      v41 = v38 / v39;
    *checked = (*lhs - *rhs) * v41 + *rhs;
    checked[1] = (lhs[1] - rhs[1]) * v41 + rhs[1];
    checked[2] = flt_18CD370;
  }
  else if ( (a1 & 1) != 0 )
  {
    v36 = flt_18CD37C - rhs[2];
    v37 = lhs[2] - rhs[2];
    if ( v37 == 0.0 )
      v41 = 1.0;
    else
      v41 = v36 / v37;
    *checked = (*lhs - *rhs) * v41 + *rhs;
    checked[1] = (lhs[1] - rhs[1]) * v41 + rhs[1];
    checked[2] = flt_18CD37C;
  }
  else if ( (a1 & 0x40) != 0 )
  {
    rf_vector3_default_construct_noop(v34);
    rf_vector3_default_construct_noop(destination);
    v5 = rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_copy(destination, copy_result, v5);
    v6 = rf_vector_subtract(rhs, v17, unk_18CD5DC);
    rf_vector_copy(v34, v16, v6);
    v35 = -rf_vector_dot(flt_18CD5F4, destination);
    if ( v35 == 0.0 )
    {
      v41 = 1.0;
    }
    else
    {
      v33 = rf_vector_dot(flt_18CD5F4, v34);
      v41 = v33 / v35;
    }
    scalar = v41;
    v7 = rf_vector_subtract(lhs, v15, rhs);
    v8 = rf_vector_multiply_scalar(v7, scaled_result, scalar);
    v9 = rf_vector_add(rhs, sum_result, v8);
    rf_vector_copy(checked, v12, v9);
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
    v41 = v30 / v29;
    *checked = (*lhs - *rhs) * v41 + *rhs;
    checked[1] = (lhs[1] - rhs[1]) * v41 + rhs[1];
    if ( (a1 & 0x30) != 0 )
      checked[2] = checked[1];
    else
      checked[2] = *checked;
    if ( (a1 & 0x14) != 0 )
      checked[2] = -checked[2];
  }
  if ( (a4 & 1) != 0 )
  {
    checked[7] = (lhs[7] - rhs[7]) * v41 + rhs[7];
    checked[8] = (lhs[8] - rhs[8]) * v41 + rhs[8];
  }
  if ( (a4 & 2) != 0 )
  {
    checked[9] = (lhs[9] - rhs[9]) * v41 + rhs[9];
    checked[10] = (lhs[10] - rhs[10]) * v41 + rhs[10];
  }
  if ( (a4 & 4) != 0 )
  {
    v22 = (float)*((unsigned __int8 *)rhs + 44);
    v25 = (float)*((unsigned __int8 *)lhs + 44);
    v24 = (float)*((unsigned __int8 *)rhs + 45);
    v26 = (float)*((unsigned __int8 *)lhs + 45);
    v23 = (float)*((unsigned __int8 *)rhs + 46);
    v27 = (float)*((unsigned __int8 *)lhs + 46);
    *((_BYTE *)checked + 44) = (int)((v25 - v22) * v41 + v22);
    *((_BYTE *)checked + 45) = (int)((v26 - v24) * v41 + v24);
    *((_BYTE *)checked + 46) = (int)((v27 - v23) * v41 + v23);
  }
  if ( (a4 & 8) != 0 )
  {
    if ( unk_18CD368 && !*((_BYTE *)lhs + 47) && (a1 & 2) != 0 )
    {
      *((_BYTE *)checked + 47) = 0;
    }
    else if ( (a1 & 1) != 0 )
    {
      if ( *((unsigned __int8 *)rhs + 47) <= (int)*((unsigned __int8 *)lhs + 47) )
        v11 = *((_BYTE *)lhs + 47);
      else
        v11 = *((_BYTE *)rhs + 47);
      *((_BYTE *)checked + 47) = v11;
    }
    else
    {
      v21 = (float)*((unsigned __int8 *)rhs + 47);
      v20 = (float)*((unsigned __int8 *)lhs + 47);
      *((_BYTE *)checked + 47) = (int)((v20 - v21) * v41 + v21);
    }
  }
  rf_clip_vertex48_update_outcode_backend((int)checked);
  return checked;
}

