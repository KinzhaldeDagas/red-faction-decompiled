// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC330 rf_particle_instance_emit_between_frames
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Emitter runtime: definition pointer0,particle36 array+144,live count+148,last frame+152,emission fraction+156. Emits only when new local frame is strictly greater than definition emission-start+156 and strictly less than frame count+204. Integrates per-frame key52 rate+48 over partial/full crossed frame ranges with literal scale320.0000305,using ceil(oldFrame),floor(newFrame),signed remainder by frame count. Adds to fractional accumulator; floors positive accumulated count,subtracts ENTIRE requested integer count before scanning pool. For each age==-1 slot calls spawn5BC660 with remainingRequested/originalRequested,new deltaSeconds,emitter velocity; decrements requested budget even if spawn is disabled. Excess
// over free slots is dropped,not deferred. Does not advance last-frame field itself. No frame-count-zero,index/rate/finite validation.
void __thiscall rf_particle_instance_emit_between_frames(void *this, float value, float a3, const float *a4)
{
  double v4; // st7
  double v5; // st7
  float v6; // [esp+Ch] [ebp-50h]
  float v8; // [esp+18h] [ebp-44h]
  float v9; // [esp+2Ch] [ebp-30h]
  float v10; // [esp+38h] [ebp-24h]
  int v11; // [esp+40h] [ebp-1Ch]
  int v12; // [esp+48h] [ebp-14h]
  int v13; // [esp+4Ch] [ebp-10h]
  int i; // [esp+4Ch] [ebp-10h]
  float v15; // [esp+50h] [ebp-Ch]
  int v16; // [esp+54h] [ebp-8h]
  int j; // [esp+58h] [ebp-4h]

  if ( value < (double)*(int *)(*(_DWORD *)this + 204) && value > (double)*(int *)(*(_DWORD *)this + 156) )
  {
    v15 = *((float *)this + 38);
    v13 = (int)rf_math_ceil_float(v15);
    v11 = (int)rf_floor_float(value);
    if ( value <= (double)v15 || value >= (double)v13 && v15 <= (double)v11 )
    {
      if ( v15 < (double)v13 )
      {
        v5 = rf_floor_float(v15);
        v9 = (double)v13 - v15;
        *((float *)this + 39) = v9
                              * 320.0000305175781
                              * *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * rf_int_max((int)v5, 0) + 48)
                              + *((float *)this + 39);
      }
      for ( i = v13 % *(_DWORD *)(*(_DWORD *)this + 204);
            i < v11 % *(_DWORD *)(*(_DWORD *)this + 204);
            i = (i + 1) % *(_DWORD *)(*(_DWORD *)this + 204) )
      {
        *((float *)this + 39) = *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * rf_int_max(i, 0) + 48)
                              * 320.0000305175781
                              + *((float *)this + 39);
      }
      if ( value > (double)v11 )
      {
        v8 = value - (double)v11;
        *((float *)this + 39) = v8
                              * 320.0000305175781
                              * *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * rf_int_max(v11, 0) + 48)
                              + *((float *)this + 39);
      }
    }
    else
    {
      v4 = rf_floor_float(v15);
      v10 = value - v15;
      *((float *)this + 39) = v10
                            * 320.0000305175781
                            * *(float *)(*(_DWORD *)(*(_DWORD *)this + 208) + 52 * rf_int_max((int)v4, 0) + 48)
                            + *((float *)this + 39);
    }
    v16 = (int)rf_floor_float(*((float *)this + 39));
    v12 = v16;
    if ( v16 > 0 )
    {
      *((float *)this + 39) = *((float *)this + 39) - (double)v16;
      for ( j = 0; j < *(_DWORD *)(*(_DWORD *)this + 152) && v16 > 0; ++j )
      {
        if ( *(float *)(*((_DWORD *)this + 36) + 36 * j) == -1.0 )
        {
          v6 = (double)v16 / (double)v12;
          rf_particle_instance_spawn_one((char *)this, j, v6, a3, (int)a4);
          --v16;
        }
      }
    }
  }
}

