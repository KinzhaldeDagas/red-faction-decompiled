// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583140 rf_quaternion_unit_log_to_destination
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): r=sqrt(x*x+y*y+z*z),factor=atan2(r,w)/r when r>0,otherwise factor=r(0 for zero vector). Outputs(x*factor,y*factor,z*factor,0),returns output. Unit-quaternion logarithm form:omits real log(norm(q)) component and does not normalize input. No axis recovery for negative-real quaternion with zero vector,finite guard or output alias issue (locals before constructor).
float *__thiscall rf_quaternion_unit_log_to_destination(float *this, float *a2)
{
  float v3; // [esp+10h] [ebp-1Ch]
  float v4; // [esp+14h] [ebp-18h]
  float v5; // [esp+18h] [ebp-14h]
  float v6; // [esp+1Ch] [ebp-10h]
  float v8; // [esp+24h] [ebp-8h]
  float X; // [esp+28h] [ebp-4h]

  v6 = *this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2);
  X = rf_sqrt_float(v6);
  if ( X > 0.0 )
  {
    v8 = atan2f(X, *(this + 3));
    X = v8 / X;
  }
  v5 = X * *(this + 2);
  v4 = X * *(this + 1);
  v3 = X * *this;
  rf_float4_construct_components(a2, v3, v4, v5, 0.0);
  return a2;
}

