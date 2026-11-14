// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BCFA0 rf_particle_instance_integrate_one
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Thiscall(runtime,index,pointer to44-byte sampled force records,count,dt); third stack argument is POINTER,not float. Negative age skips. Acceleration starts(0,0,0),definition flag2 adds Y=-9.8. Each sampled channel type from channel definition+212:0=plane signed distance along sampled normal;1=radial displacement from sampled origin,length and normalized direction; other type immediately RETURNS,skipping integration. Direction times sampled strength+24,optionally multiplied by exp(-sampledFalloff*distance),with sampledFalloff at sample+28. Despite old decorated log label,4DA160/180 call __CIexp. Nonzero noise amplitude+32 adds three gradient-noise components using
// displacement/0.0254,elapsedSeconds*4800*0.01*sample+36 injected into each axis,spatial scale+40. Field force scaled sequentially0.0001 then0.0625 before adding gravity. vNew=vOld+a*dt;position+=0.5*(vOld+vNew)*dt;stores new velocity. Does not age/kill particles,normalize plane normal or validate pointers/counts/dt/exp range.
void __thiscall rf_particle_instance_integrate_one(void *this, int a2, const void *a3, int a4, float a5)
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
  float v15; // [esp+4h] [ebp-188h] BYREF
  float *v16; // [esp+8h] [ebp-184h]
  float scalar; // [esp+Ch] [ebp-180h]
  float v18; // [esp+10h] [ebp-17Ch]
  int v19; // [esp+14h] [ebp-178h]
  float *v20; // [esp+18h] [ebp-174h]
  float v21[3]; // [esp+1Ch] [ebp-170h] BYREF
  float v22[3]; // [esp+28h] [ebp-164h] BYREF
  float v23; // [esp+34h] [ebp-158h] BYREF
  int v24[3]; // [esp+40h] [ebp-14Ch] BYREF
  float v25[3]; // [esp+4Ch] [ebp-140h] BYREF
  float v26[3]; // [esp+58h] [ebp-134h] BYREF
  float v27; // [esp+64h] [ebp-128h] BYREF
  float v28[3]; // [esp+70h] [ebp-11Ch] BYREF
  int v29[4]; // [esp+7Ch] [ebp-110h] BYREF
  float v30[4]; // [esp+8Ch] [ebp-100h] BYREF
  float v31[4]; // [esp+9Ch] [ebp-F0h] BYREF
  float v32[3]; // [esp+ACh] [ebp-E0h] BYREF
  float v33[3]; // [esp+B8h] [ebp-D4h] BYREF
  float v34[3]; // [esp+C4h] [ebp-C8h] BYREF
  float out_vector[3]; // [esp+D0h] [ebp-BCh] BYREF
  float v36[3]; // [esp+DCh] [ebp-B0h] BYREF
  float v37[3]; // [esp+E8h] [ebp-A4h] BYREF
  float copy_result[3]; // [esp+F4h] [ebp-98h] BYREF
  float scaled_result[3]; // [esp+100h] [ebp-8Ch] BYREF
  int v40[3]; // [esp+10Ch] [ebp-80h] BYREF
  float v41; // [esp+118h] [ebp-74h]
  float vector[3]; // [esp+11Ch] [ebp-70h] BYREF
  float source[3]; // [esp+128h] [ebp-64h] BYREF
  float v44[4]; // [esp+134h] [ebp-58h] BYREF
  float v45[3]; // [esp+144h] [ebp-48h] BYREF
  float v46; // [esp+150h] [ebp-3Ch]
  float destination[3]; // [esp+154h] [ebp-38h] BYREF
  float sum_result[3]; // [esp+160h] [ebp-2Ch] BYREF
  int v49; // [esp+16Ch] [ebp-20h]
  float v50[3]; // [esp+170h] [ebp-1Ch] BYREF
  int i; // [esp+17Ch] [ebp-10h]
  float v52; // [esp+180h] [ebp-Ch] BYREF
  float v53; // [esp+184h] [ebp-8h]

  v20 = (float *)this;
  v49 = *((_DWORD *)this + 36) + 36 * a2;
  if ( *(float *)v49 >= 0.0 )
  {
    rf_vector3_set_components_return_destination(&v52, 0.0, 0.0, 0.0);
    if ( (*(_DWORD *)(*(_DWORD *)v20 + 172) & 2) != 0 )
      v53 = v53 - 9.800000190734863;
    for ( i = 0; i < a4; ++i )
    {
      rf_vector3_default_construct_noop(destination);
      rf_vector3_default_construct_noop(v45);
      v19 = *(_DWORD *)(*(_DWORD *)LODWORD(v20[i + 1]) + 212);
      if ( v19 )
      {
        if ( v19 != 1 )
          return;
        v7 = rf_vector_subtract((const float *)(v49 + 12), out_vector, (const float *)a3 + 11 * i);
        rf_vector_copy(destination, v34, v7);
        v46 = rf_vector3_length(destination);
        rf_vector_copy(v45, v33, destination);
        rf_vector_normalize(v45);
        scalar = *(float *)&a3;
        rf_vector3_scale_in_place_return_self(v45, *((float *)a3 + 11 * i + 6));
      }
      else
      {
        rf_plane_construct_from_normal_point(v44, (float *)a3 + 11 * i + 3, (int)a3 + 44 * i);
        v46 = rf_plane_point_signed_distance(v44, (float *)(v49 + 12));
        v5 = rf_vector_multiply_scalar((const float *)a3 + 11 * i + 3, scaled_result, v46);
        rf_vector_copy(destination, copy_result, v5);
        LODWORD(scalar) = 44 * i;
        v6 = rf_vector_multiply_scalar((const float *)a3 + 11 * i + 3, v37, *((float *)a3 + 11 * i + 6));
        rf_vector_copy(v45, v36, v6);
      }
      if ( *((float *)a3 + 11 * i + 7) != 0.0 )
      {
        v18 = -*((float *)a3 + 11 * i + 7) * v46;
        scalar = rf_exp_float(v18);
        rf_vector3_scale_in_place_return_self(v45, scalar);
      }
      if ( *((float *)a3 + 11 * i + 8) != 0.0 )
      {
        rf_vector3_default_construct_noop(vector);
        rf_vector3_default_construct_noop(v40);
        rf_vector_divide(destination, source, 0.0254);
        v41 = *((float *)a3 + 11 * i + 9) * 0.009999999776482582 * v20[7] * 4800.0;
        rf_vector_copy(vector, v32, source);
        vector[0] = v41;
        rf_vector_multiply_scalar(vector, &v15, *((float *)a3 + 11 * i + 10));
        *(float *)v40 = rf_gradient_noise_3d(v15, *(float *)&v16, scalar);
        rf_vector_copy(vector, v31, source);
        vector[1] = v41;
        rf_vector_multiply_scalar(vector, &v15, *((float *)a3 + 11 * i + 10));
        *(float *)&v40[1] = rf_gradient_noise_3d(v15, *(float *)&v16, scalar);
        rf_vector_copy(vector, v30, source);
        vector[2] = v41;
        rf_vector_multiply_scalar(vector, &v15, *((float *)a3 + 11 * i + 10));
        *(float *)&v40[2] = rf_gradient_noise_3d(v15, *(float *)&v16, scalar);
        scalar = COERCE_FLOAT(v40);
        v16 = (float *)(44 * i);
        v8 = rf_vector_scale((float *)v29, *((float *)a3 + 11 * i + 8), (float *)v40);
        rf_vector_accumulate(v45, v8);
      }
      scalar = 0.0625;
      v16 = &v27;
      v9 = rf_vector_multiply_scalar(v45, v28, 0.000099999997);
      v10 = rf_vector_multiply_scalar(v9, v16, scalar);
      rf_vector_accumulate(&v52, v10);
    }
    v11 = rf_vector_multiply_scalar(&v52, v26, a5);
    rf_vector_add((const float *)(v49 + 24), sum_result, v11);
    scalar = a5;
    v16 = &v23;
    v12 = rf_vector_add((const float *)(v49 + 24), v25, sum_result);
    v13 = rf_vector_scale((float *)v24, 0.5, v12);
    v14 = rf_vector_multiply_scalar(v13, v16, scalar);
    rf_vector_add((const float *)(v49 + 12), v50, v14);
    rf_vector_copy((float *)(v49 + 12), v22, v50);
    rf_vector_copy((float *)(v49 + 24), v21, sum_result);
  }
}

