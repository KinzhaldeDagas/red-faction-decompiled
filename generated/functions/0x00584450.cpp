// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584450 rf_quaternion_squad_wrapped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, quaternion arithmetic, signed integer normalization, matrix conversion and custom variadic formatting): Recovered cdecl(out,A,B,C,D,t). Computes Q=interpolate(A,D,t),R=interpolate(B,C,t),out=interpolate(Q,R,2*(1-t)*t). Local temporaries precede output,allowing output/input alias. Uses RF wrapped interpolation583D20 including its nonstandard near-identical/w-forcing behavior;does NOT globally clamp/wrap t before computing blend scalar,and no final normalization. Infinite/huge input t inherits interpolation loop hazards;not a replacement with textbook clamped SQUAD.
void __cdecl rf_quaternion_squad_wrapped(
        float *a1,
        const float *a2,
        const float *a3,
        const float *a4,
        const float *a5,
        float a6)
{
  float v6; // [esp+4h] [ebp-24h]
  float v7[4]; // [esp+8h] [ebp-20h] BYREF
  float v8[4]; // [esp+18h] [ebp-10h] BYREF

  rf_float4_construct_zero_zero_zero_one(v7);
  rf_float4_construct_zero_zero_zero_one(v8);
  rf_quaternion_interpolate(v7, (float *)a2, (float *)a5, a6);
  rf_quaternion_interpolate(v8, (float *)a3, (float *)a4, a6);
  v6 = (1.0 - a6) * 2.0 * a6;
  rf_quaternion_interpolate(a1, v7, v8, v6);
}

