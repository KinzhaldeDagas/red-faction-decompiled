// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BD420 rf_particle_instance_integrate_current_interval
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): If no force channels,integrates every particle once with passed deltaSeconds and NULL sample/count0 (gravity remains). Otherwise divides interval using ceil(oldFrame),floor(newFrame),sampling44-byte channel records at relevant frames,rotates source positions/directions into world and adds current emitter origin. Main/fractional interval seconds use frameDelta*0.06666667. IMPORTANT actual inner loop counter increments0.5 while dt=min(1/30,interval-counter); typical one-frame1/15-second interval therefore gets one1/30-second integration,not two. Does not subtract dt from loop counter interval. Special wrapped/disabled-emission paths integrate without sampled fields for whole remaining interval. Arrays hold only3
// sampled records but channel count is not capped. Signed modulo frame count is unchecked; no positive-delta/frame-count guard. Last-frame/particle ages maintained elsewhere.
void __thiscall rf_particle_instance_integrate_current_interval(float *this, float a2, float a3)
{
  float value; // [esp+4h] [ebp-E0h]
  float valuea; // [esp+4h] [ebp-E0h]
  float valueb; // [esp+4h] [ebp-E0h]
  float valuec; // [esp+4h] [ebp-E0h]
  float v7; // [esp+Ch] [ebp-D8h]
  float v8; // [esp+10h] [ebp-D4h]
  float v9; // [esp+1Ch] [ebp-C8h]
  float v10; // [esp+24h] [ebp-C0h]
  int v12; // [esp+34h] [ebp-B0h]
  float v13; // [esp+3Ch] [ebp-A8h]
  float v14; // [esp+3Ch] [ebp-A8h]
  float v15; // [esp+3Ch] [ebp-A8h]
  float v16; // [esp+3Ch] [ebp-A8h]
  int v17; // [esp+40h] [ebp-A4h]
  int v18[35]; // [esp+44h] [ebp-A0h] BYREF
  bool v19; // [esp+D2h] [ebp-12h]
  bool v20; // [esp+D3h] [ebp-11h]
  float v21; // [esp+D4h] [ebp-10h]
  float v22; // [esp+D8h] [ebp-Ch]
  float j; // [esp+DCh] [ebp-8h]
  int i; // [esp+E0h] [ebp-4h]

  if ( (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF) != 0 )
  {
    v22 = *(this + 38);
    v17 = (int)rf_math_ceil_float(*(this + 38));
    v12 = (int)rf_floor_float(a2);
    rf_vector_construct_no_unwind(
      (char *)v18,
      0x2Cu,
      3,
      (void *(__thiscall *)(void *))rf_force_sample44_construct_vectors_noop);
    v19 = v22 > (double)a2;
    v20 = (*(_DWORD *)(this + 4) & 1) != 0;
    if ( a2 <= (double)v22 || a2 >= (double)v17 && v22 <= (double)v12 )
    {
      if ( v22 < (double)v17 )
      {
        for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
        {
          valuea = (float)(int)rf_floor_float(v22);
          rf_scene_frame_channel_build_sample44(*((void **)this + i + 1), (float *)&v18[11 * i], valuea);
          rf_vector_rotate_by_matrix3((float *)&v18[11 * i], this + 14);
          rf_vector_accumulate((float *)&v18[11 * i], this + 8);
          if ( *(_DWORD *)(**((_DWORD **)this + i + 1) + 212) != 1 )
            rf_vector_rotate_by_matrix3((float *)&v18[11 * i + 3], this + 14);
        }
        v21 = ((double)v17 - v22) * 0.06666667014360428;
        for ( j = 0.0; v21 > (double)j; j = j + 0.5 )
        {
          v9 = v21 - j;
          v14 = rf_float_minimum_two_values(0.033333335, v9);
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
            rf_particle_instance_integrate_one(this, i, v18, *(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF, v14);
        }
      }
      while ( v17 % *(_DWORD *)(*(_DWORD *)this + 204) < v12 % *(_DWORD *)(*(_DWORD *)this + 204) )
      {
        if ( v19 && v20 && v17 >= *(_DWORD *)(*(_DWORD *)this + 204) )
        {
          v21 = (double)(v12 - v17) * 0.06666667014360428;
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
            rf_particle_instance_integrate_one(this, i, nullptr, 0, v21);
          break;
        }
        for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
        {
          valueb = (float)(v17 % *(_DWORD *)(*(_DWORD *)this + 204));
          rf_scene_frame_channel_build_sample44(*((void **)this + i + 1), (float *)&v18[11 * i], valueb);
          rf_vector_rotate_by_matrix3((float *)&v18[11 * i], this + 14);
          rf_vector_accumulate((float *)&v18[11 * i], this + 8);
          if ( *(_DWORD *)(**((_DWORD **)this + i + 1) + 212) != 1 )
            rf_vector_rotate_by_matrix3((float *)&v18[11 * i + 3], this + 14);
        }
        v21 = 0.06666667;
        for ( j = 0.0; v21 > (double)j; j = j + 0.5 )
        {
          v8 = v21 - j;
          v15 = rf_float_minimum_two_values(0.033333335, v8);
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
            rf_particle_instance_integrate_one(this, i, v18, *(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF, v15);
        }
        ++v17;
      }
      if ( a2 > (double)v12 )
      {
        if ( v19 && v20 && v12 >= *(_DWORD *)(*(_DWORD *)this + 204) )
        {
          v21 = (a2 - (double)v12) * 0.06666667014360428;
          for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
            rf_particle_instance_integrate_one(this, i, nullptr, 0, v21);
        }
        else
        {
          for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
          {
            valuec = (float)v12;
            rf_scene_frame_channel_build_sample44(*((void **)this + i + 1), (float *)&v18[11 * i], valuec);
            rf_vector_rotate_by_matrix3((float *)&v18[11 * i], this + 14);
            rf_vector_accumulate((float *)&v18[11 * i], this + 8);
            if ( *(_DWORD *)(**((_DWORD **)this + i + 1) + 212) != 1 )
              rf_vector_rotate_by_matrix3((float *)&v18[11 * i + 3], this + 14);
          }
          v21 = (a2 - (double)v12) * 0.06666667014360428;
          for ( j = 0.0; v21 > (double)j; j = j + 0.5 )
          {
            v7 = v21 - j;
            v16 = rf_float_minimum_two_values(0.033333335, v7);
            for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
              rf_particle_instance_integrate_one(this, i, v18, *(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF, v16);
          }
        }
      }
    }
    else
    {
      for ( i = 0; i < (*(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF); ++i )
      {
        value = (float)(int)rf_floor_float(v22);
        rf_scene_frame_channel_build_sample44(*((void **)this + i + 1), (float *)&v18[11 * i], value);
        rf_vector_rotate_by_matrix3((float *)&v18[11 * i], this + 14);
        rf_vector_accumulate((float *)&v18[11 * i], this + 8);
        if ( *(_DWORD *)(**((_DWORD **)this + i + 1) + 212) != 1 )
          rf_vector_rotate_by_matrix3((float *)&v18[11 * i + 3], this + 14);
      }
      v21 = (a2 - v22) * 0.06666667014360428;
      for ( j = 0.0; v21 > (double)j; j = j + 0.5 )
      {
        v10 = v21 - j;
        v13 = rf_float_minimum_two_values(0.033333335, v10);
        for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
          rf_particle_instance_integrate_one(this, i, v18, *(_DWORD *)(*(_DWORD *)this + 148) & 0x7FFFFFFF, v13);
      }
    }
  }
  else
  {
    for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 152); ++i )
      rf_particle_instance_integrate_one(this, i, nullptr, 0, a3);
  }
}

