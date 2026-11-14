// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00526630 rf_light_sync_receiver_space_transform
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light. Use renderer typeDWORD8 and row-matrix global18CD5B8; global translation vector18CD804. Type1 transform original vector12 by matrix ONLY ->alternate92 (direction-like, no translation). Type2 position:subtract translation from12 then transform ->92. Type3 same origin operation and matrix-only original direction36 ->alternate116. Type4 subtract translation and transform BOTH original endpoints12/24 ->alternate92/104. Other type leaves data unchanged. F32 vector-helper stores at each step, no normalization or cone-plane rebuild, no bit masks/coverage/cache serial updates. Return declared float* is vector-copy/local-result EAX residue for known types and light pointer for default; output
// side effects are authoritative, not a stable returned vector pointer.
float *__cdecl rf_light_sync_receiver_space_transform(int a1)
{
  float *v1; // eax
  float *result; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float v12[3]; // [esp+4h] [ebp-114h] BYREF
  float v13[3]; // [esp+10h] [ebp-108h] BYREF
  float v14[3]; // [esp+1Ch] [ebp-FCh] BYREF
  float v15[3]; // [esp+28h] [ebp-F0h] BYREF
  float v16[3]; // [esp+34h] [ebp-E4h] BYREF
  float v17[3]; // [esp+40h] [ebp-D8h] BYREF
  float v18[3]; // [esp+4Ch] [ebp-CCh] BYREF
  float v19[3]; // [esp+58h] [ebp-C0h] BYREF
  float v20[3]; // [esp+64h] [ebp-B4h] BYREF
  float v21[3]; // [esp+70h] [ebp-A8h] BYREF
  float v22[3]; // [esp+7Ch] [ebp-9Ch] BYREF
  float v23[3]; // [esp+88h] [ebp-90h] BYREF
  float v24[3]; // [esp+94h] [ebp-84h] BYREF
  float v25[3]; // [esp+A0h] [ebp-78h] BYREF
  float v26[3]; // [esp+ACh] [ebp-6Ch] BYREF
  float v27[3]; // [esp+B8h] [ebp-60h] BYREF
  float v28[3]; // [esp+C4h] [ebp-54h] BYREF
  float out_vector[3]; // [esp+D0h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+DCh] [ebp-3Ch] BYREF
  float v31[3]; // [esp+E8h] [ebp-30h] BYREF
  float v32[3]; // [esp+F4h] [ebp-24h] BYREF
  float v33[3]; // [esp+100h] [ebp-18h] BYREF
  float destination[3]; // [esp+10Ch] [ebp-Ch] BYREF

  switch ( *(_DWORD *)(a1 + 8) )
  {
    case 1:
      v1 = rf_vector3_transform_by_matrix_rows((float *)(a1 + 12), v31, &flt_18CD5B8);
      result = rf_vector_copy((float *)(a1 + 92), copy_result, v1);
      break;
    case 2:
      rf_vector3_default_construct_noop(destination);
      v3 = rf_vector_subtract((const float *)(a1 + 12), out_vector, unk_18CD804);
      rf_vector_copy(destination, v28, v3);
      v4 = rf_vector3_transform_by_matrix_rows(destination, v27, &flt_18CD5B8);
      result = rf_vector_copy((float *)(a1 + 92), v26, v4);
      break;
    case 3:
      rf_vector3_default_construct_noop(v33);
      v5 = rf_vector_subtract((const float *)(a1 + 12), v25, unk_18CD804);
      rf_vector_copy(v33, v24, v5);
      v6 = rf_vector3_transform_by_matrix_rows(v33, v23, &flt_18CD5B8);
      rf_vector_copy((float *)(a1 + 92), v22, v6);
      v7 = rf_vector3_transform_by_matrix_rows((float *)(a1 + 36), v21, &flt_18CD5B8);
      result = rf_vector_copy((float *)(a1 + 116), v20, v7);
      break;
    case 4:
      rf_vector3_default_construct_noop(v32);
      v8 = rf_vector_subtract((const float *)(a1 + 12), v19, unk_18CD804);
      rf_vector_copy(v32, v18, v8);
      v9 = rf_vector3_transform_by_matrix_rows(v32, v17, &flt_18CD5B8);
      rf_vector_copy((float *)(a1 + 92), v16, v9);
      v10 = rf_vector_subtract((const float *)(a1 + 24), v15, unk_18CD804);
      rf_vector_copy(v32, v14, v10);
      v11 = rf_vector3_transform_by_matrix_rows(v32, v13, &flt_18CD5B8);
      result = rf_vector_copy((float *)(a1 + 104), v12, v11);
      break;
    default:
      result = (float *)a1;
      break;
  }
  return result;
}

