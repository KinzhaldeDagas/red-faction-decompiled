// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C4B40 rf_geomod_impact_chunk_motion_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl(chunk,launchOrigin). Computes chunk.position8-origin and normalizes using559300 (zero/NaN length ->unitX), then samples unit cone around it with min-dot F32.5. Native
// radius56 comparison to DOUBLE0.12999999523162842: ordered <threshold uses sequential F32 vector*6 then*2 (speed12 for finite unit). Ordered>= OR unordered takes large branch,
// unlike pseudocode ordered >=/else NaN interpretation: sequential vector*6, *F32(1-scalar60), *F32approximately1.4. Each vector helper stores components binary32; do not collapse
// products without preserving rounding. Stores velocity72 and returns vector-copy result chunk+72. Does NOT change bounce budget, age, flags, pose matrix, axis/spin or room. No
// clamping of scalar60 or finite validation; large branch can invert velocity if scalar>1.
float *__cdecl rf_geomod_impact_chunk_motion_init(int a1, float *rhs)
{
  float *v2; // eax
  float *v3; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // [esp+4h] [ebp-78h] BYREF
  float scalar; // [esp+8h] [ebp-74h]
  float *v10; // [esp+Ch] [ebp-70h]
  float v11; // [esp+10h] [ebp-6Ch]
  float v12; // [esp+14h] [ebp-68h]
  float v13[3]; // [esp+18h] [ebp-64h] BYREF
  float v14[3]; // [esp+24h] [ebp-58h] BYREF
  float v15[3]; // [esp+30h] [ebp-4Ch] BYREF
  float v16[3]; // [esp+3Ch] [ebp-40h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-34h] BYREF
  float v18[3]; // [esp+54h] [ebp-28h] BYREF
  float scaled_result[4]; // [esp+60h] [ebp-1Ch] BYREF
  float out_vector[3]; // [esp+70h] [ebp-Ch] BYREF

  rf_vector_subtract((const float *)(a1 + 8), out_vector, rhs);
  rf_vector_normalize(out_vector);
  v11 = 0.5;
  rf_vector3_copy_return_destination((float *)&v8, out_vector);
  rf_random_unit_vector_in_cone(out_vector, *(float *)&v8, scalar, *(float *)&v10, v11);
  if ( *(float *)(a1 + 56) >= 0.1299999952316284 )
  {
    v11 = 1.4;
    v10 = v14;
    v12 = 1.0 - *(float *)(a1 + 60);
    scalar = v12;
    v8 = v15;
    v5 = rf_vector_multiply_scalar(out_vector, v16, 6.0);
    v6 = rf_vector_multiply_scalar(v5, v8, scalar);
    v7 = rf_vector_multiply_scalar(v6, v10, v11);
    return rf_vector_copy((float *)(a1 + 72), v13, v7);
  }
  else
  {
    v11 = 2.0;
    v10 = v18;
    v2 = rf_vector_multiply_scalar(out_vector, scaled_result, 6.0);
    v3 = rf_vector_multiply_scalar(v2, v10, v11);
    return rf_vector_copy((float *)(a1 + 72), copy_result, v3);
  }
}

