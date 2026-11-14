// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041B820 rf_glare_model_occludes_segment
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl(candidateCommon,glare,cameraPosition), returns AL bool. Requires candidate flags+124 mask0x10, nonnull model+128, candidate pointer!=global0x681E38, and glare owner+48 != candidate UID+44. Broad-phase segment test uses candidate bounds+400/+412 and endpoints glarePos+60,cameraPos; local hit output discarded. After broad hit, no-op constructs model query/result, writes candidate transform, ray start=cameraPos, displacement=glarePos-cameraPos, query radius+72=0,flags+76=1. Calls all-pieces model collision adapter(model,query,result,initializeByte1), booleanizes AL, discards detailed hit. Query constructors do not zero unused scratch. No null/bounds/finite guards or ownership/scene-list mutation.
bool __cdecl rf_glare_model_occludes_segment(_DWORD *a1, int a2, float *rhs)
{
  float *v4; // eax
  float v5[3]; // [esp+0h] [ebp-C4h] BYREF
  float v6[3]; // [esp+Ch] [ebp-B8h] BYREF
  float out_vector[3]; // [esp+18h] [ebp-ACh] BYREF
  float copy_result[3]; // [esp+24h] [ebp-A0h] BYREF
  _BYTE v9[32]; // [esp+30h] [ebp-94h] BYREF
  float v10[3]; // [esp+50h] [ebp-74h] BYREF
  float v11[3]; // [esp+5Ch] [ebp-68h] BYREF
  float v12[9]; // [esp+68h] [ebp-5Ch] BYREF
  float destination[3]; // [esp+8Ch] [ebp-38h] BYREF
  float v14[11]; // [esp+98h] [ebp-2Ch] BYREF

  if ( (a1[31] & 0x10) == 0 )
    return 0;
  if ( !a1[32] || a1 == (_DWORD *)dword_681E38 )
    return 0;
  if ( *(_DWORD *)(a2 + 48) == a1[11] )
    return 0;
  rf_vector3_default_construct_noop(v10);
  if ( !rf_segment_intersects_aabb((float *)a1 + 100, (float *)a1 + 103, (float *)(a2 + 60), rhs, v10) )
    return 0;
  rf_model_collision_query_construct_noop((char *)v11);
  rf_model_collision_result_construct_noop((int)v9);
  rf_vector_copy(destination, copy_result, rhs);
  v4 = rf_vector_subtract((const float *)(a2 + 60), out_vector, rhs);
  rf_vector_copy(v14, v6, v4);
  LODWORD(v14[4]) = 1;
  v14[3] = 0.0;
  rf_matrix3_copy(v12, (const float *)a1 + 18);
  rf_vector_copy(v11, v5, (const float *)a1 + 15);
  return rf_model_handle_collide_all_adapter((_DWORD *)a1[32], (int)v11, (int)v9, 1) != 0;
}

