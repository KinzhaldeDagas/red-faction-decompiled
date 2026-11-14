// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055CE30 rf_motion_profile_step_toward_distance
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(v0,maxSpeed,distance,acceleration,dt,outV,clampStoppingSpeed), float displacement viaST0. acceleration0 writes v0 and returns v0*dt. Optional stopping clamp replaces local v0 with sqrt(2*a*distance) when v0^2>2.1*a*distance. Uses retail1.9/2.1 stopping-distance bands: near braking band integrates v1=v0-a*dt or snaps v1=0/displacement=distance if it would go negative; farther-distance branch chooses acceleration/peak/maxSpeed behavior using peakSpeedSquared=a*distance+0.5*v0^2. Overspeed branch uses1.05*a, may call reverse profile with negated velocity after crossing correction. MaxSpeed is not a universal post-step clamp and some branches use trapezoid over entire dt after reaching a cap. No
// general finite/negative-limit/time guard; branch formulas preserved, no simplification to constant-acceleration clamp.
double __cdecl rf_motion_profile_step_toward_distance(
        float a1,
        float a2,
        float a3,
        float a4,
        float a5,
        float *a6,
        int a7)
{
  float v8; // [esp+0h] [ebp-50h]
  float v9; // [esp+1Ch] [ebp-34h]
  float v10; // [esp+28h] [ebp-28h]
  float v11; // [esp+2Ch] [ebp-24h]
  float v12; // [esp+30h] [ebp-20h]
  float v13; // [esp+34h] [ebp-1Ch]
  float v14; // [esp+38h] [ebp-18h]
  float v15; // [esp+3Ch] [ebp-14h]
  float v16; // [esp+40h] [ebp-10h]
  float v17; // [esp+44h] [ebp-Ch]
  float v18; // [esp+48h] [ebp-8h]
  float v20; // [esp+4Ch] [ebp-4h]
  float v21; // [esp+4Ch] [ebp-4h]
  float v22; // [esp+4Ch] [ebp-4h]
  float v26; // [esp+4Ch] [ebp-4h]
  float v29; // [esp+58h] [ebp+8h]

  if ( a4 == 0.0 )
  {
    *a6 = a1;
    return (float)(a1 * a5);
  }
  else
  {
    if ( a7 && a4 * 2.099999904632568 * a3 < a1 * a1 )
    {
      v11 = a4 * 2.0 * a3;
      a1 = rf_sqrt_float(v11);
    }
    if ( a4 * 2.099999904632568 * a3 >= a1 * a1 )
    {
      if ( a4 * 1.899999976158142 * a3 <= a1 * a1 )
      {
        if ( a1 - a4 * a5 >= 0.0 )
        {
          *a6 = a1 - a4 * a5;
          return (float)((a1 + *a6) * 0.5 * a5);
        }
        else
        {
          *a6 = 0.0;
          return a3;
        }
      }
      else
      {
        v16 = a4 * a3 + a1 * 0.5 * a1;
        if ( v16 <= a2 * a2 )
        {
          if ( v16 <= (a4 * a5 + a1) * (a4 * a5 + a1) )
          {
            v13 = rf_sqrt_float(v16);
            v14 = (v13 - a1) / a4;
            *a6 = v13;
            v26 = (a1 + *a6) * 0.5 * v14;
            v12 = a5 - v14;
            *a6 = *a6 - a4 * v12;
            if ( *a6 >= 0.0 )
            {
              return (float)((v13 + *a6) * 0.5 * v12 + v26);
            }
            else
            {
              *a6 = 0.0;
              return a3;
            }
          }
          else
          {
            *a6 = a4 * a5 + a1;
            return (float)((a1 + *a6) * 0.5 * a5);
          }
        }
        else
        {
          v15 = (a2 - a1) / a4;
          if ( v15 >= 0.0 )
          {
            if ( a5 >= (double)v15 )
              *a6 = a2;
            else
              *a6 = a4 * a5 + a1;
            return (float)((a1 + *a6) * 0.5 * a5);
          }
          else
          {
            *a6 = a1 - a4 * a5;
            if ( *a6 < 0.0 )
              *a6 = 0.0;
            return (float)((a1 + *a6) * 0.5 * a5);
          }
        }
      }
    }
    else
    {
      v18 = a4 * 1.049999952316284;
      v20 = a1 * a5 - v18 * 0.5 * a5 * a5;
      if ( a3 >= (double)v20 )
      {
        if ( v20 >= 0.0 )
        {
          *a6 = a1 - v18 * a5;
          return v20;
        }
        else
        {
          *a6 = 0.0;
          return a3;
        }
      }
      else
      {
        v10 = a1 * a1 + v18 * 2.0 * a3;
        v17 = (rf_sqrt_float(v10) - a1) / v18;
        v29 = a1 - v18 * v17;
        v21 = v29 * v17 + v18 * 0.5 * v17 * v17;
        v9 = a5 - v17;
        v8 = -v29;
        v22 = v21 - rf_motion_profile_step_reversing_velocity(v8, a2, 0.0, a4, v9, a6, a7);
        *a6 = -*a6;
        return v22;
      }
    }
  }
}

