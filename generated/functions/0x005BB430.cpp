// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB430 rf_rfa_compute_total_rotation_for_seconds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, animation-clip pool, raw-buffer callers, key sampling branches and interpolation helpers): Lazily gets raw header; alpha=seconds/((end-start)/160/30), roundedfloat; interpolates identity toward TotalRotation float4 at+44 through583D20, normalizes result with5832E0 and copies to output. Shared interpolation wraps alpha by repeated +/-1 instead of clamping and has unusual near-identical branch. No duration, finite-value or failed-load guard. No image xrefs observed; do not infer dead code solely from this.
float *__thiscall rf_rfa_compute_total_rotation_for_seconds(void *this, float *a2, float a3)
{
  float *v3; // eax
  float *v5; // [esp-4h] [ebp-38h]
  float v6; // [esp+4h] [ebp-30h]
  float v7[4]; // [esp+10h] [ebp-24h] BYREF
  unsigned __int8 *raw_buffer; // [esp+20h] [ebp-14h]
  float v9[4]; // [esp+24h] [ebp-10h] BYREF

  raw_buffer = rf_rfa_get_or_load_raw_buffer(this);
  rf_float4_construct_zero_zero_zero_one(v9);
  v6 = 1.0 / ((double)(*((_DWORD *)raw_buffer + 5) - *((_DWORD *)raw_buffer + 4)) / 160.0 / 30.0) * a3;
  v5 = (float *)(raw_buffer + 44);
  v3 = rf_float4_construct_zero_zero_zero_one(v7);
  rf_quaternion_interpolate(v9, v3, v5, v6);
  rf_quaternion_normalize_in_place_unchecked(v9);
  rf_float4_assign_components_return_this(a2, v9);
  return a2;
}

