// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051C5A0 rf_solid_sample_mass_inverse_inertia_and_recenter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mass sampling and inverse inertia,recentering,UV cuts and density,finite epsilon tests,original ECX/stack flow and PE bytes): Thiscall solid,outCenterXYZ,outInverseInertia9,density RET12; x87 floating mass. Zero outputs. Read existing bounds72/84; h=F32(maxExtent/4) stored844,half=h/2; baseZ=F32(-half*4)=-2h, firstXY=F32(-half*3)=-1.5h, cellMass=F32(density*h*h*h). Clear64 occupancy BYTES780 indexed16*i+4*j+k. X/Y scan starts-1.5h and increments h while ORDERED coordinate<bounds.maxX/maxY; no use of min for origin, no i/j<4 cap. For each column segmentZ[-2h,+2h], iterate all faces112: faceAABB pruning, finite segment-plane intersection, projected polygon containment. Fraction f produces q=F32(f*4),k=int(floor(q)),sub=int(floor(F32((q-k)*4))). No k clamp: f==1 can write k4 outside intended column. Normal dot(0,0,1)
// ORDERED positive sets bit(sub+4), otherwise (including NaN) bit(sub), truncating toBYTE. Ascending k0..3 and bits1,2,4,8: if low bit set without corresponding high nibble exit bit, propagate next low bit, crossing into next k bit0 if k+1<4. Low-nibble weight table63FA00 is popcount(mask)/4, exact sixteen values0,.25,.25,.5,.25,.5,.5,.75,.25,.5,.5,.75,.5,.75,.75,1. Sum F32 mass +=cellMass*weight and center via TWO vector scaling passes (center*cellMass then*weight), using coarse cell centerZ=(2k+1)*half+baseZ. Divide center by mass only ORDERED mass>0. Store grid origin848/852/856=(baseZ+half)-center component. Call51C4E0 to SUBTRACT center from solid vertices/bounds; helper enlarges old radius by offset length and does not update center100. Then over FIXED4x4x4 weighted cells, accumulate point-mass inertia diagonal m*(other axes squared), offdiagonal -m*x*y etc, no intrinsic cube inertia
// term; invert in place via55BC30, exact singular leaves matrix. Return mass when positive OR unordered (TEST AH41/JP at51CE9C); otherwise F32(extentX*extentY*extentZ*0.5*density). Fallback does not recalculate center/inertia. No guards for h<=0, uncentered bounds, density, finite arithmetic, loop progress or occupancy bounds. Physics caller4D7785 uses returned mass and inverse inertia and reads grid later.
double __thiscall rf_solid_sample_mass_inverse_inertia_and_recenter(float *this, float *a2, float *a3, float a4)
{
  float *v4; // eax
  float *v5; // eax
  float value; // [esp+8h] [ebp-C8h]
  float valuea; // [esp+8h] [ebp-C8h]
  float v10; // [esp+14h] [ebp-BCh]
  float v11; // [esp+18h] [ebp-B8h]
  float v13[3]; // [esp+20h] [ebp-B0h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-A4h] BYREF
  float v15; // [esp+38h] [ebp-98h]
  float v16; // [esp+3Ch] [ebp-94h]
  int jj; // [esp+40h] [ebp-90h]
  float v18; // [esp+44h] [ebp-8Ch]
  int v19; // [esp+48h] [ebp-88h]
  float v20[3]; // [esp+4Ch] [ebp-84h] BYREF
  float rhs[3]; // [esp+58h] [ebp-78h] BYREF
  float lhs[3]; // [esp+64h] [ebp-6Ch] BYREF
  float v23[4]; // [esp+70h] [ebp-60h] BYREF
  int j; // [esp+80h] [ebp-50h]
  float v25; // [esp+84h] [ebp-4Ch]
  int k; // [esp+88h] [ebp-48h]
  float out_vector; // [esp+8Ch] [ebp-44h] BYREF
  float v28; // [esp+90h] [ebp-40h]
  float v29; // [esp+94h] [ebp-3Ch]
  float v30; // [esp+98h] [ebp-38h]
  float vector; // [esp+9Ch] [ebp-34h] BYREF
  float v32; // [esp+A0h] [ebp-30h]
  float v33; // [esp+A4h] [ebp-2Ch]
  float v34[3]; // [esp+A8h] [ebp-28h] BYREF
  float v35; // [esp+B4h] [ebp-1Ch]
  float *ii; // [esp+B8h] [ebp-18h]
  int i; // [esp+BCh] [ebp-14h]
  float scalar; // [esp+C0h] [ebp-10h]
  float m; // [esp+C4h] [ebp-Ch]
  float n; // [esp+C8h] [ebp-8h]
  float v41; // [esp+CCh] [ebp-4h]

  v35 = 0.0;
  rf_vector3_default_construct_noop(&vector);
  rf_vector3_default_construct_noop(v34);
  rf_vector3_zero_return_destination(a2);
  rf_vector3_zero_return_destination(a3);
  rf_vector3_zero_return_destination(a3 + 3);
  rf_vector3_zero_return_destination(a3 + 6);
  rf_vector_subtract(this + 21, &out_vector, this + 18);
  value = rf_float_maximum_two_values(v28, v29);
  *(this + 211) = rf_float_maximum_two_values(out_vector, value) / 4.0;
  v25 = *(this + 211) / 2.0;
  scalar = a4 * *(this + 211) * *(this + 211) * *(this + 211);
  for ( i = 0; i < 4; ++i )
  {
    for ( j = 0; j < 4; ++j )
    {
      for ( k = 0; k < 4; ++k )
        *((_BYTE *)this + 16 * i + 4 * j + k + 780) = 0;
    }
  }
  v30 = -v25 * 4.0;
  i = 0;
  for ( m = -v25 * 3.0; *(this + 21) > (double)m; m = m + *(this + 211) )
  {
    j = 0;
    for ( n = -v25 * 3.0; *(this + 22) > (double)n; n = n + *(this + 211) )
    {
      rf_vector_prefix_construct_noop(v23);
      rf_vector3_set_components_return_destination(rhs, m, n, v30);
      v11 = *(this + 211) * 4.0 + v30;
      rf_vector3_set_components_return_destination(lhs, m, n, v11);
      for ( ii = (float *)rf_receiver_get_first_dword(this + 28); ii; ii = (float *)rf_solid_face_next_link((int)ii) )
      {
        if ( rf_segment_intersects_aabb(ii + 4, ii + 7, rhs, lhs, v34) )
        {
          rf_vector_subtract(lhs, v20, rhs);
          if ( rf_segment_plane_intersection_point_fraction(v23, (int)rhs, (int)v20, (int)ii) )
          {
            if ( rf_geomod_face_contains_projected_point(ii, (int)v23) )
            {
              v41 = rf_vector3_dot_xyz_by_value(ii, 0.0, 0.0, 1.0);
              v18 = v23[3] * 4.0;
              k = (int)rf_floor_float(v18);
              v18 = v18 - (double)k;
              v10 = v18 * 4.0;
              v19 = (int)rf_floor_float(v10);
              if ( v41 <= 0.0 )
                *((_BYTE *)this + 16 * i + 4 * j + k + 780) |= 1 << v19;
              else
                *((_BYTE *)this + 16 * i + 4 * j + k + 780) |= 1 << (v19 + 4);
            }
          }
        }
      }
      for ( k = 0; k < 4; ++k )
      {
        if ( (*((_BYTE *)this + 16 * i + 4 * j + k + 780) & 0xF) != 0 )
        {
          for ( jj = 1; jj <= 8; jj *= 2 )
          {
            if ( ((unsigned __int8)jj & *((_BYTE *)this + 16 * i + 4 * j + k + 780)) != 0
              && ((16 * jj) & *((unsigned __int8 *)this + 16 * i + 4 * j + k + 780)) == 0 )
            {
              if ( jj >= 8 )
              {
                if ( k + 1 < 4 )
                  *((_BYTE *)this + 16 * i + 4 * j + k + 781) |= 1u;
              }
              else
              {
                *((_BYTE *)this + 16 * i + 4 * j + k + 780) |= 2 * jj;
              }
            }
          }
        }
      }
      vector = m;
      v32 = n;
      for ( k = 0; k < 4; ++k )
      {
        v16 = flt_63FA00[*((_BYTE *)this + 16 * i + 4 * j + k + 780) & 0xF];
        if ( v16 > 0.0 )
        {
          v35 = scalar * v16 + v35;
          v33 = (double)(2 * k + 1) * v25 + v30;
          valuea = v16;
          v4 = rf_vector_multiply_scalar(&vector, scaled_result, scalar);
          v5 = rf_vector_multiply_scalar(v4, v13, valuea);
          rf_vector_accumulate(a2, v5);
        }
      }
      ++j;
    }
    ++i;
  }
  if ( v35 > 0.0 )
    rf_vector3_divide_in_place_reciprocal(a2, v35);
  v41 = v30 + v25;
  *(this + 212) = v41 - *a2;
  *(this + 213) = v41 - a2[1];
  *(this + 214) = v41 - a2[2];
  rf_solid_translate_by_subtracting_offset(this, a2);
  for ( i = 0; i < 4; ++i )
  {
    vector = (double)i * *(this + 211) + *(this + 212);
    for ( j = 0; j < 4; ++j )
    {
      v32 = (double)j * *(this + 211) + *(this + 213);
      for ( k = 0; k < 4; ++k )
      {
        v33 = (double)k * *(this + 211) + *(this + 214);
        v15 = flt_63FA00[*((_BYTE *)this + 16 * i + 4 * j + k + 780) & 0xF];
        if ( v15 > 0.0 )
        {
          v15 = v15 * scalar;
          *a3 = (v32 * v32 + v33 * v33) * v15 + *a3;
          a3[1] = a3[1] - v15 * vector * v32;
          a3[2] = a3[2] - v15 * vector * v33;
          a3[3] = a3[3] - v15 * v32 * vector;
          a3[4] = (vector * vector + v33 * v33) * v15 + a3[4];
          a3[5] = a3[5] - v15 * v32 * v33;
          a3[6] = a3[6] - v15 * v33 * vector;
          a3[7] = a3[7] - v15 * v33 * v32;
          a3[8] = (vector * vector + v32 * v32) * v15 + a3[8];
        }
      }
    }
  }
  rf_matrix3_inverse_in_place_if_nonsingular(a3);
  if ( v35 > 0.0 )
    return v35;
  return (float)(out_vector * v28 * v29 * 0.5 * a4);
}

