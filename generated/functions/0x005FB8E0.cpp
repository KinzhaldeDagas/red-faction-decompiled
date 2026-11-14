// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB8E0 rf_scene_transform_range_sample_between_frames
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This148-byte range,args destination28bytes,float frame. i=floor(frame),j=i+1;returns0 without output writes wheni<start136 ORj>=end140. Else subtracts start fromindices,lerps frame positions and interpolates quaternions byfraction frame-floor(frame),writes dest0/12,returns1. Strict terminal gate excludes frame interval ending atstoredend even for files whose loader stores inclusive end. No direct last-frame sample,clamp,pool/status/output-pointer guard.
char __thiscall rf_scene_transform_range_sample_between_frames(_DWORD *this, float *destination, float a3)
{
  float *v4; // eax
  float *v5; // eax
  float *value; // [esp+8h] [ebp-4Ch]
  float scalar; // [esp+Ch] [ebp-48h]
  float copy_result[3]; // [esp+18h] [ebp-3Ch] BYREF
  float sum_result[3]; // [esp+24h] [ebp-30h] BYREF
  float scaled_result[3]; // [esp+30h] [ebp-24h] BYREF
  float v12[3]; // [esp+3Ch] [ebp-18h] BYREF
  int v13; // [esp+48h] [ebp-Ch]
  int v14; // [esp+4Ch] [ebp-8h]
  float v15; // [esp+50h] [ebp-4h]

  v14 = (int)rf_floor_float(a3);
  v13 = v14 + 1;
  if ( v14 < *(this + 34) || v13 >= *(this + 35) )
    return 0;
  v14 -= *(this + 34);
  v13 -= *(this + 34);
  v15 = a3 - (double)(int)rf_floor_float(a3);
  value = rf_vector_multiply_scalar((const float *)(*(this + 36) + 28 * v13), scaled_result, v15);
  scalar = 1.0 - v15;
  v4 = rf_vector_multiply_scalar((const float *)(*(this + 36) + 28 * v14), v12, scalar);
  v5 = rf_vector_add(v4, sum_result, value);
  rf_vector_copy(destination, copy_result, v5);
  rf_quaternion_interpolate(
    destination + 3,
    (float *)(*(this + 36) + 28 * v14 + 12),
    (float *)(*(this + 36) + 28 * v13 + 12),
    v15);
  return 1;
}

