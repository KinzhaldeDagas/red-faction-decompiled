// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055CD20 rf_motion_profile_step_reversing_velocity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(v0,maxSpeed,nonnegativeDistance,acceleration,dt,outV,clampStoppingSpeed), floating ST0 displacement. Intended v0<=0 moving away. If -v0<float1e-5 AND distance<float1e-5, writes outV0 and returns distance. acceleration0 writes v0/returns v0*dt. Else timeToZero=-v0/acceleration: if dt<time, integrates v1=v0+a*dt and trapezoid distance; otherwise integrates negative braking segment then delegates55CE30 from velocity0 with increased remaining distance and remaining time. No negative/zero dt, sign, maximum-speed or pointer validation.
double __cdecl rf_motion_profile_step_reversing_velocity(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float *a6,
        int a7)
{
  float v8; // [esp+1Ch] [ebp-Ch]
  float v9; // [esp+20h] [ebp-8h]
  float v12; // [esp+24h] [ebp-4h]
  float v13; // [esp+38h] [ebp+10h]

  if ( -a1 >= 0.000009999999747378752 || a3 >= 0.000009999999747378752 )
  {
    if ( a4 == 0.0 )
    {
      *a6 = a1;
      return (float)(a1 * a5);
    }
    else
    {
      v8 = -a1 / a4;
      if ( a5 >= (double)v8 )
      {
        v12 = a1 * 0.5 * v8;
        v13 = a3 - v12;
        v9 = a5 - v8;
        return (float)(rf_motion_profile_step_toward_distance(0.0, a2, v13, a4, v9, a6, a7) + v12);
      }
      else
      {
        *a6 = a4 * a5 + a1;
        return (float)((a1 + *a6) * 0.5 * a5);
      }
    }
  }
  else
  {
    *a6 = 0.0;
    return a3;
  }
}

