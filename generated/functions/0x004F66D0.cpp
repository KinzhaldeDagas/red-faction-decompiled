// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F66D0 rf_snapshot_unpack_normalized_vector_s16
// UNREALRED VERIFIED [save-validation-20261028]: Sign-extends three input s16 components, divides each by32767.0 into float vec3, then calls rf_vector_normalize_reciprocal_sqrt in place. Not merely inverse scaling; output is normalized by helper.
float *__cdecl rf_snapshot_unpack_normalized_vector_s16(__int16 *a1, float *a2)
{
  *a2 = (double)*a1 / 32767.0;
  a2[1] = (double)a1[1] / 32767.0;
  a2[2] = (double)a1[2] / 32767.0;
  return rf_vector_normalize_reciprocal_sqrt(a2);
}

