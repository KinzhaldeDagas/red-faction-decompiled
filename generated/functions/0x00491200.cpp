// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491200 rf_entity_publish_latest_buffered_pose
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Cdecl entity pointer. NULL entity,buffer632NULL or signed buffer count1332<=0 returns. Reads timeWORD atbuffer1278+2*count (equivalent last slot in time array1280),no upper-count
// guard. Samples matrix/Euler/offset and position/velocity with that unsignedWORD. Copies sampled position to COMMON entity60,matrix toCOMMON72,builds pitch/heading linear-horizontal
// basis from sampled Euler+offset,stores atentity2016,then calls420870(entity). Sampled velocity ignored. Does not directly install physics current228/predicted240,bounds400 or
// physical orientation252. No full-buffer count validation,quaternion interpolation or sampling-status result check.
void __cdecl rf_entity_publish_latest_buffered_pose(int a1)
{
  const float *v1; // eax
  _BYTE v2[36]; // [esp+0h] [ebp-94h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-70h] BYREF
  float source[3]; // [esp+30h] [ebp-64h] BYREF
  __int16 v5; // [esp+3Ch] [ebp-58h]
  float lhs[3]; // [esp+40h] [ebp-54h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-48h] BYREF
  float rhs[3]; // [esp+58h] [ebp-3Ch] BYREF
  float v9[3]; // [esp+64h] [ebp-30h] BYREF
  float v10[9]; // [esp+70h] [ebp-24h] BYREF

  if ( a1 && *(_DWORD *)(a1 + 632) && *(int *)(*(_DWORD *)(a1 + 632) + 1332) > 0 )
  {
    v5 = *(_WORD *)(*(_DWORD *)(a1 + 632) + 2 * *(_DWORD *)(*(_DWORD *)(a1 + 632) + 1332) + 1278);
    rf_matrix3_construct((char *)v10);
    rf_vector3_default_construct_noop(lhs);
    rf_vector3_default_construct_noop(rhs);
    rf_vector3_default_construct_noop(source);
    rf_vector3_default_construct_noop(v9);
    rf_entity_sample_buffered_euler_and_offset(a1, v5, (int)v10, lhs, rhs);
    rf_entity_sample_buffered_position_and_velocity(a1, v5, source, v9);
    rf_vector_copy((float *)(a1 + 60), copy_result, source);
    rf_matrix3_copy((float *)(a1 + 72), v10);
    rf_vector_add(lhs, sum_result, rhs);
    v1 = (const float *)rf_matrix3_build_pitch_heading_linear_horizontal_basis((int)v2, sum_result);
    rf_matrix3_copy((float *)(a1 + 2016), v1);
    sub_420870(a1);
  }
}

