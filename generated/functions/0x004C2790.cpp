// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C2790 rf_explosion_graph_create_runtime
// UNREALRED VERIFIED [combat-particle-emission-20261104]: Normalize graph axis with559300 (zero RF+X fallback), build normalized55BF00 basis. For each central emitter independently draw TWO planar coordinates in[-randomPositionFactor*size,+factor*size] ONCE, replace prototype source position with graphOrigin+right*u+up*v and direction with graphAxis, then create emitter via4CEC90. Scale prototype speed, particle radius and lifetime only; spawnRadius and source offsets are not size-scaled (authored source position is replaced). Sparks use separate direct prototype4C2690: graphOrigin, graphAxis cone per spark, random speed*size, shared prototype radius*size and unscaled life; no emitter spawnRadius or dirdepend operation in that loop. Full rising-ball graph path is separate.
void __cdecl rf_explosion_graph_create_runtime(
        char *String1,
        float *source,
        float *a3,
        float a4,
        int a5,
        unsigned __int8 a6)
{
  int v6; // eax
  float *v7; // eax
  float *v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // edx
  int v12; // edx
  int v13; // eax
  int v14; // eax
  float *v15; // eax
  float *v16; // eax
  float v17; // [esp-8h] [ebp-1E4h] BYREF
  float v18; // [esp-4h] [ebp-1E0h]
  float *v19; // [esp+0h] [ebp-1DCh]
  float scalar; // [esp+4h] [ebp-1D8h]
  float v21; // [esp+8h] [ebp-1D4h]
  float v22[3]; // [esp+Ch] [ebp-1D0h] BYREF
  float v23[4]; // [esp+18h] [ebp-1C4h] BYREF
  float v24[3]; // [esp+28h] [ebp-1B4h] BYREF
  float v25[3]; // [esp+34h] [ebp-1A8h] BYREF
  float v26[4]; // [esp+40h] [ebp-19Ch] BYREF
  float v27[3]; // [esp+50h] [ebp-18Ch] BYREF
  float v28[3]; // [esp+5Ch] [ebp-180h] BYREF
  float v29[3]; // [esp+68h] [ebp-174h] BYREF
  float v30[3]; // [esp+74h] [ebp-168h] BYREF
  float sum_result[3]; // [esp+80h] [ebp-15Ch] BYREF
  float v32[3]; // [esp+8Ch] [ebp-150h] BYREF
  float copy_result[3]; // [esp+98h] [ebp-144h] BYREF
  float v34; // [esp+A4h] [ebp-138h]
  float v35[3]; // [esp+A8h] [ebp-134h] BYREF
  float v36; // [esp+B4h] [ebp-128h]
  float v37[3]; // [esp+B8h] [ebp-124h] BYREF
  float v38[3]; // [esp+C4h] [ebp-118h] BYREF
  float v39[3]; // [esp+D0h] [ebp-10Ch] BYREF
  float v40; // [esp+DCh] [ebp-100h]
  float v41; // [esp+118h] [ebp-C4h]
  float v42[3]; // [esp+11Ch] [ebp-C0h] BYREF
  float v43[3]; // [esp+128h] [ebp-B4h] BYREF
  float v44; // [esp+134h] [ebp-A8h]
  float v45; // [esp+16Ch] [ebp-70h]
  float rhs[3]; // [esp+170h] [ebp-6Ch] BYREF
  float v47; // [esp+17Ch] [ebp-60h]
  float scaled_result[3]; // [esp+180h] [ebp-5Ch] BYREF
  float v49; // [esp+18Ch] [ebp-50h]
  float v50; // [esp+190h] [ebp-4Ch]
  float v51; // [esp+194h] [ebp-48h]
  float v52; // [esp+198h] [ebp-44h]
  float v53; // [esp+19Ch] [ebp-40h]
  float v54; // [esp+1A0h] [ebp-3Ch]
  float vector[3]; // [esp+1A4h] [ebp-38h] BYREF
  float v56[6]; // [esp+1B0h] [ebp-2Ch] BYREF
  float v57; // [esp+1C8h] [ebp-14h]
  float v58; // [esp+1CCh] [ebp-10h]
  char *v59; // [esp+1D0h] [ebp-Ch]
  float *destination; // [esp+1D4h] [ebp-8h]
  int i; // [esp+1D8h] [ebp-4h]

  v59 = nullptr;
  for ( i = 0; i < unk_814348; ++i )
  {
    if ( !_stricmp(String1, &unk_813C20[152 * i]) )
    {
      v59 = &unk_813C20[152 * i];
      break;
    }
  }
  if ( v59 )
  {
    rf_vector_normalize(a3);
    destination = (float *)unk_814344;
    if ( unk_814344 )
    {
      rf_matrix3_construct((char *)vector);
      *((_DWORD *)destination + 74) = v59;
      rf_vector_copy(destination, copy_result, source);
      rf_vector_copy(destination + 3, v32, a3);
      destination[7] = a4;
      *((_DWORD *)destination + 6) = a5;
      destination[8] = 0.0;
      rf_orientation_matrix_from_normalized_direction(vector, a3);
      if ( ((a6 | (unsigned __int8)*(_DWORD *)(*((_DWORD *)destination + 74) + 32)) & 1) != 0 )
      {
        destination[67] = 0.0;
      }
      else if ( a4 >= 1.0 )
      {
        if ( a4 >= 8.0 )
        {
          *((_DWORD *)destination + 67) = 8;
        }
        else
        {
          v50 = a4 - 1.0;
          v49 = a4 + 1.0;
          v6 = (int)rf_random_float_range(v50, v49);
          *((_DWORD *)destination + 67) = v6;
        }
      }
      else
      {
        destination[67] = 0.0;
      }
      for ( i = 0; i < *((_DWORD *)v59 + 31); ++i )
      {
        if ( *(float *)&v59[4 * i + 76] > (double)a4 )
        {
          destination[i + 68] = 0.0;
        }
        else
        {
          v57 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 32);
          v51 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 36);
          v58 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 64);
          v54 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 68);
          v52 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 56);
          v53 = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 60);
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 32) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 32)
                                                                     * a4;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 36) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 36)
                                                                     * a4;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 64) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 64)
                                                                     * a4;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 68) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 68)
                                                                     * a4;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 56) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 56)
                                                                     * a4;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 60) = *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]]
                                                                                + 60)
                                                                     * a4;
          v47 = *((float *)v59 + 36) * a4;
          v45 = -v47;
          scalar = rf_random_float_range(v45, v47);
          rf_vector_multiply_scalar(vector, rhs, scalar);
          scalar = rf_random_float_range(v45, v47);
          rf_vector_multiply_scalar(v56, scaled_result, scalar);
          v7 = rf_vector_add(source, sum_result, rhs);
          v8 = rf_vector_add(v7, v30, scaled_result);
          rf_vector_copy((float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 4), v29, v8);
          rf_vector_copy((float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 16), v28, a3);
          v9 = rf_particle_emitter_create(
                 -1,
                 (float *)dword_867800[*(_DWORD *)&v59[4 * i + 44]],
                 *((_DWORD *)destination + 6),
                 0,
                 1);
          LODWORD(destination[i + 68]) = v9;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 32) = v57;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 36) = v51;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 64) = v58;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 68) = v54;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 56) = v52;
          *(float *)(dword_867800[*(_DWORD *)&v59[4 * i + 44]] + 60) = v53;
        }
      }
      if ( *((int *)v59 + 32) > -1 )
      {
        rf_particle_descriptor76_construct_noop((int)v42);
        rf_explosion_sample_direct_particle_prototype(dword_867800[*((_DWORD *)v59 + 32)], (int)v42);
        rf_vector_copy(v42, v27, source);
        v44 = v44 * destination[7];
        for ( i = 0; i < *((_DWORD *)v59 + 33); ++i )
        {
          v10 = dword_867800[*((_DWORD *)v59 + 32)];
          scalar = *(float *)&v59;
          scalar = *(float *)(v10 + 28);
          rf_vector3_copy_return_destination(&v17, a3);
          rf_random_unit_vector_in_cone(v43, v17, v18, *(float *)&v19, scalar);
          v11 = dword_867800[*((_DWORD *)v59 + 32)];
          scalar = *((float *)v59 + 32);
          scalar = *(float *)(v11 + 36);
          v12 = dword_867800[*((_DWORD *)v59 + 32)];
          v19 = *((float **)v59 + 32);
          v21 = rf_random_float_range(*(float *)(v12 + 32), scalar) * a4;
          rf_vector3_scale_in_place_return_self(v43, v21);
          rf_particle_allocate_and_initialize(0, (int)v42, *((_DWORD *)destination + 6), 0, -1, nullptr, 0);
        }
      }
      if ( *((int *)v59 + 9) > -1 )
      {
        rf_particle_descriptor76_construct_noop((int)v38);
        v13 = dword_867800[*((_DWORD *)v59 + 9)];
        scalar = *(float *)&v59;
        scalar = *(float *)(v13 + 36);
        v14 = dword_867800[*((_DWORD *)v59 + 9)];
        v19 = (float *)v59;
        v41 = rf_random_float_range(*(float *)(v14 + 32), scalar) * a4;
        for ( i = 0; i < *((_DWORD *)destination + 67); ++i )
        {
          v36 = *((float *)v59 + 37) * a4;
          v34 = -v36;
          scalar = rf_random_float_range(v34, v36);
          rf_vector_multiply_scalar(vector, v35, scalar);
          scalar = rf_random_float_range(v34, v36);
          rf_vector_multiply_scalar(v56, v37, scalar);
          scalar = COERCE_FLOAT(v37);
          v19 = v25;
          v15 = rf_vector_add(source, v26, v35);
          v16 = rf_vector_add(v15, v19, (const float *)LODWORD(scalar));
          rf_vector_copy(&destination[3 * i + 9], v24, v16);
          scalar = 0.69999999;
          rf_vector3_copy_return_destination(&v17, a3);
          rf_random_unit_vector_in_cone(&destination[3 * i + 33], v17, v18, *(float *)&v19, scalar);
          rf_vector3_scale_in_place_return_self(&destination[3 * i + 33], v41);
          *((_BYTE *)destination + i + 260) = 1;
        }
        rf_explosion_sample_direct_particle_prototype(dword_867800[*((_DWORD *)v59 + 9)], (int)v38);
        v40 = v40 * destination[7];
        for ( i = 0; i < *((_DWORD *)destination + 67); ++i )
        {
          rf_vector_copy(v38, v23, &destination[3 * i + 9]);
          rf_vector_copy(v39, v22, &destination[3 * i + 33]);
          rf_particle_allocate_and_initialize(0, (int)v38, *((_DWORD *)destination + 6), 0, -1, &destination[i + 57], 0);
        }
      }
      if ( (float *)unk_814344 == destination )
      {
        if ( *((float **)destination + 75) == destination )
        {
          destination[75] = 0.0;
          destination[76] = 0.0;
          unk_814344 = 0;
          goto LABEL_37;
        }
        unk_814344 = *((_DWORD *)destination + 75);
      }
      *(float *)(*((_DWORD *)destination + 76) + 300) = destination[75];
      *(float *)(*((_DWORD *)destination + 75) + 304) = destination[76];
      destination[75] = 0.0;
      destination[76] = 0.0;
LABEL_37:
      if ( unk_814340 )
      {
        destination[76] = *(float *)(unk_814340 + 304);
        *((_DWORD *)destination + 75) = unk_814340;
        *(_DWORD *)(*(_DWORD *)(unk_814340 + 304) + 300) = destination;
        *(_DWORD *)(unk_814340 + 304) = destination;
      }
      else
      {
        *((_DWORD *)destination + 75) = destination;
        *((_DWORD *)destination + 76) = destination;
        unk_814340 = destination;
      }
    }
  }
}

