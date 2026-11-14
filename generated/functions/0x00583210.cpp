// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583210 rf_quaternion_pure_exp_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered thiscall source quaternion,output. Uses ONLY xyz:r=sqrt(sumxyz2),factor1 if r<=~1e-10 else sin(r)/r;out=(xyz*factor,cos(r)),returns output. Ignores input w,so pure-quaternion exponential form,not full exp(w)*rotation formula. Locals before destination stores permit exact alias. No finite/argument reduction or final normalize beyond trig helpers.
float *__thiscall rf_quaternion_pure_exp_to_destination(const float *this, float *a2)
{
  float v3; // [esp+Ch] [ebp-20h]
  float v4; // [esp+10h] [ebp-1Ch]
  float v5; // [esp+14h] [ebp-18h]
  float v6; // [esp+18h] [ebp-14h]
  float v7; // [esp+1Ch] [ebp-10h]
  float v9; // [esp+24h] [ebp-8h]
  float v10; // [esp+28h] [ebp-4h]

  v7 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  v9 = rf_sqrt_float(v7);
  if ( v9 <= 1.000000013351432e-10 )
    v10 = 1.0;
  else
    v10 = rf_sin_float(v9) / v9;
  v3 = rf_cos_float(v9);
  v6 = v10 * *(this + 2);
  v5 = v10 * *(this + 1);
  v4 = v10 * *this;
  rf_float4_construct_components(a2, v4, v5, v6, v3);
  return a2;
}

