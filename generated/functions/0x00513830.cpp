// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513830 rf_projected_shadow_compute_view_fade
// UNREALRED VERIFIED [general-gap-20260830]: Computes view-distance admission and alpha: full below 7.5 RF units, linear (13-distance)/5.5 through 13, and rejected at or beyond 13.
int __cdecl rf_projected_shadow_compute_view_fade(int a1, float *a2, _DWORD *a3)
{
  float *v3; // eax
  float out_vector[3]; // [esp+0h] [ebp-10h] BYREF
  float v6; // [esp+Ch] [ebp-4h]

  *a3 = 0;
  v3 = rf_vector_subtract(unk_18CD4A8, out_vector, (const float *)(a1 + 60));
  v6 = rf_vector3_length(v3);
  *a2 = 1.0;
  if ( flt_663ADC <= (double)v6 )
    return 0;
  if ( flt_663AE0 <= (double)v6 )
    *a2 = 1.0 - (v6 - flt_663AE0) / (flt_663ADC - flt_663AE0);
  if ( flt_663AE4 <= (double)v6 )
    *a3 = 1;
  return 1;
}

