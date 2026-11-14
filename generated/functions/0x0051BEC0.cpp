// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051BEC0 rf_solid_compute_vertex_mean
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,outMean3f,RET4. Zeros output before reading vertex-array120 count. Count0 returnsNULL with output zero. Nonzero count:for signed i<count,accumulates every vertex position into output with float stores,then scales by float(1.0/count),returns output pointer. Arithmetic vertex mean,not AABB midpoint or area/volume-weighted centroid. Negative corrupted count skips accumulation but still applies negative reciprocal;no count,pointer,alias,finite or duplicate filtering. Corrected old int return to float*;physical ECX/one-stack-argument ABI unchanged.
float *__thiscall rf_solid_compute_vertex_mean(void *solid, float *mean)
{
  float *result; // eax
  float **v3; // eax
  float *v5; // [esp+8h] [ebp-Ch]
  float v6; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  rf_vector3_zero_return_destination(mean);
  result = (float *)rf_receiver_get_first_dword((char *)solid + 120);
  v5 = result;
  if ( result )
  {
    for ( i = 0; i < (int)v5; ++i )
    {
      v3 = (float **)sub_552200((_DWORD *)solid + 30, i);
      rf_vector_accumulate(mean, *v3);
    }
    v6 = 1.0 / (double)(int)v5;
    return rf_vector3_scale_in_place_return_self(mean, v6);
  }
  return result;
}

