// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BCC60 rf_particle_instance_integrate_backlog
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Sorts all particle36 records by descending age via5BCF50. Clamps backlog seconds+160 to baseLifetimeTicks*(variation+1)/4800. While backlog>0: sampleFrame=int(newFrame-backlogSeconds)%definitionFrameCount (subtracts seconds directly from frame value),adjust negative remainder once; estimates prior origin=currentOrigin-normalize(emitterVelocity)*backlogSeconds,discarding velocity magnitude. Samples up to definition channel count into THREE local44-byte records,rotates positions/world offsets and nonradial directions; integrates all particles by min(1/30,backlog) through5BCFA0,subtracts that step,clamps backlog>=0. Does not increment ages. Zero velocity normalization uses shared helper behavior; no
// frame-count0/channelCount<=3/lifetime validation.
void __thiscall rf_particle_instance_integrate_backlog(float *this, float a2, float *a3)
{
  float *v3; // eax
  float scalar; // [esp+4h] [ebp-C8h]
  float scaled_result[3]; // [esp+Ch] [ebp-C0h] BYREF
  float vector[3]; // [esp+18h] [ebp-B4h] BYREF
  int v8[35]; // [esp+24h] [ebp-A8h] BYREF
  float v9; // [esp+B0h] [ebp-1Ch]
  float out_vector[3]; // [esp+B4h] [ebp-18h] BYREF
  int v11; // [esp+C0h] [ebp-Ch]
  float v12; // [esp+C4h] [ebp-8h]
  int i; // [esp+C8h] [ebp-4h]

  qsort(
    *((void **)this + 36),
    *(_DWORD *)(*(_DWORD *)this + 152),
    0x24u,
    (_CoreCrtNonSecureSearchSortCompareFunction)rf_particle_compare_age_descending);
  v12 = (double)*(int *)(*(_DWORD *)this + 160) * (*(float *)(*(_DWORD *)this + 164) + 1.0) / 4800.0;
  if ( v12 < (double)*(this + 40) )
    *(this + 40) = v12;
  while ( *(this + 40) > 0.0 )
  {
    v11 = (int)(a2 - *(this + 40)) % *(_DWORD *)(*(_DWORD *)this + 204);
    if ( (double)v11 < 0.0 )
      v11 += *(_DWORD *)(*(_DWORD *)this + 204);
    rf_vector3_copy_return_destination(vector, a3);
    rf_vector_normalize_reciprocal_sqrt(vector);
    v3 = rf_vector_multiply_scalar(vector, scaled_result, *(this + 40));
    rf_vector_subtract(this + 8, out_vector, v3);
    rf_vector_construct_no_unwind(
      (char *)v8,
      0x2Cu,
      3,
      (void *(__thiscall *)(void *))rf_force_sample44_construct_vectors_noop);
    for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
    {
      scalar = (float)v11;
      rf_scene_frame_channel_build_sample44(*((void **)this + i + 1), (float *)&v8[11 * i], scalar);
      rf_vector_rotate_by_matrix3((float *)&v8[11 * i], this + 14);
      rf_vector_accumulate((float *)&v8[11 * i], out_vector);
      if ( *(_DWORD *)(**((_DWORD **)this + i + 1) + 212) != 1 )
        rf_vector_rotate_by_matrix3((float *)&v8[11 * i + 3], this + 14);
    }
    v9 = rf_float_minimum_two_values(0.033333335, *(this + 40));
    for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
      rf_particle_instance_integrate_one(this, i, v8, *(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF, v9);
    *(this + 40) = *(this + 40) - v9;
    if ( *(this + 40) < 0.0 )
      *(this + 40) = 0.0;
  }
}

