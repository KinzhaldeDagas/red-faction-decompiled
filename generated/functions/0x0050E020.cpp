// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050E020 rf_projectile_steer_to_target_preserve_speed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile pre/post physics,homing/expiry/render branches,two-argument cone ABI andx87unordered flow,original ECX/stack flow and PE bytes): Resolves projectile target UID+744 as generic object. Missing target returns NULL, leaves supplied distance output and velocity untouched; does not clear target UID. Found target initializes static vector927400=(0,1,0) once through guard92740C bit1, but this vector is unused in steering. Forms target position+60 minus projectile+60; unchecked normalize559280 returns F32 Euclidean distance, written only if optional output pointer non-NULL. Stores oldSpeed=F32(length velocity+324). Scales normalized direction by F32((1/info turnTime+304)*oldSpeed*(frameDelta/DOUBLE0.03333299979567528)), accumulates into velocity, stores newSpeed=F32(length updated velocity), then scales velocity in
// place by F32(oldSpeed/newSpeed). Returns velocity pointer on found-target path. No direct position/orientation write, wakeup/flag gating (caller does those), zero-distance/zero-speed/turnTime/finite guard or clamp. Zero vectors/cancelled velocity can generate NaN; turn coefficient is velocity addition followed by speed renormalization, not angle interpolation.
float *__cdecl rf_projectile_steer_to_target_preserve_speed(int a1, float *a2)
{
  float *result; // eax
  float *v3; // eax
  float v4; // [esp+10h] [ebp-54h]
  float v5; // [esp+14h] [ebp-50h]
  float copy_result[3]; // [esp+18h] [ebp-4Ch] BYREF
  float out_vector[3]; // [esp+24h] [ebp-40h] BYREF
  float v8; // [esp+30h] [ebp-34h]
  float v9; // [esp+34h] [ebp-30h]
  _BYTE v10[12]; // [esp+38h] [ebp-2Ch] BYREF
  float v11; // [esp+44h] [ebp-20h]
  int v12; // [esp+48h] [ebp-1Ch]
  float destination[6]; // [esp+4Ch] [ebp-18h] BYREF

  result = (float *)rf_object_resolve_handle(*(_DWORD *)(a1 + 744));
  v12 = (int)result;
  if ( result )
  {
    if ( (dword_92740C & 1) == 0 )
    {
      dword_92740C |= 1u;
      rf_vector3_set_components_return_destination(flt_927400, 0.0, 1.0, 0.0);
      destination[5] = NAN;
    }
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v10);
    v3 = rf_vector_subtract((const float *)(v12 + 60), out_vector, (const float *)(a1 + 60));
    rf_vector_copy(destination, copy_result, v3);
    v11 = rf_vector3_normalize_return_length(destination);
    if ( a2 )
      *a2 = v11;
    v9 = rf_vector3_length((float *)(a1 + 324));
    v5 = 1.0 / *(float *)(*(_DWORD *)(a1 + 660) + 304) * v9 * (rf_frame_delta_seconds / 0.03333299979567528);
    rf_vector3_scale_in_place_return_self(destination, v5);
    rf_vector_accumulate((float *)(a1 + 324), destination);
    v8 = rf_vector3_length((float *)(a1 + 324));
    v4 = v9 / v8;
    return rf_vector3_scale_in_place_return_self((float *)(a1 + 324), v4);
  }
  return result;
}

