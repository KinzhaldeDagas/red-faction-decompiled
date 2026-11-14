// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00583030 rf_quaternion_normalized_to_destination_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Computes float reciprocal of sum of four component squares,then sqrt of that rounded reciprocal;multiplies each source component by rounded factor into locals,constructs output and returns it. No zero-length/finite/overflow guard. Source unchanged unless aliased with output;all component locals formed before output writes. Unlike s16 normalizer583530,this reciprocal computation is floating point.
float *__thiscall rf_quaternion_normalized_to_destination_unchecked(float *this, float *a2)
{
  float v3; // [esp+10h] [ebp-1Ch]
  float v4; // [esp+14h] [ebp-18h]
  float v5; // [esp+18h] [ebp-14h]
  float v6; // [esp+1Ch] [ebp-10h]
  float v7; // [esp+20h] [ebp-Ch]
  float v9; // [esp+28h] [ebp-4h]

  v7 = 1.0 / (*this * *this + *(this + 1) * *(this + 1) + *(this + 2) * *(this + 2) + *(this + 3) * *(this + 3));
  v9 = rf_sqrt_float(v7);
  v6 = *(this + 3) * v9;
  v5 = *(this + 2) * v9;
  v4 = *(this + 1) * v9;
  v3 = *this * v9;
  rf_float4_construct_components(a2, v3, v4, v5, v6);
  return a2;
}

