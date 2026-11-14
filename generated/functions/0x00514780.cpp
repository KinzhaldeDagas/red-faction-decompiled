// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514780 rf_mesh_decal_project_prism_and_collect
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl80-byte request*,caller pops4;returns pooled48-byte collection orNULL. Construct local176-byte query(defaultsixplanes no-op,payloaddefaults),then if signedcollectionFree9287B8<=0 returnNULL. Copy request80 bytes memberwise intoquery+96. Build six plane4f via normal/point constructor: (-Z,start),(+Z,end),(-X,start-X*radius),(+X,start+X*radius),(+Y,start+Y*radius),(-Y,start-Y*radius),where requeststart12,end24,basis rowsX36,Y48,Z60,radius8. Plane helper setsD=-dot(normal,point),doesnot normalize;vector scale/add/sub useF32temporaries. Call5141A0(query). No basis orthogonality/normalization,radius positivity,finite/endpoint/model checks,transform to world,heap fallback or room
// interaction. Payload80 holds owner0,texture4,radius8,start12,end24,basis36,flags72,selector76.
float *__cdecl rf_mesh_decal_project_prism_and_collect(float *a1)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float v13[3]; // [esp+4h] [ebp-188h] BYREF
  float v14[3]; // [esp+10h] [ebp-17Ch] BYREF
  float v15[3]; // [esp+1Ch] [ebp-170h] BYREF
  float v16[3]; // [esp+28h] [ebp-164h] BYREF
  float v17[3]; // [esp+34h] [ebp-158h] BYREF
  float v18[3]; // [esp+40h] [ebp-14Ch] BYREF
  float v19[3]; // [esp+4Ch] [ebp-140h] BYREF
  float v20[3]; // [esp+58h] [ebp-134h] BYREF
  float sum_result[3]; // [esp+64h] [ebp-128h] BYREF
  float v22[3]; // [esp+70h] [ebp-11Ch] BYREF
  float v23[3]; // [esp+7Ch] [ebp-110h] BYREF
  float v24[3]; // [esp+88h] [ebp-104h] BYREF
  float out_vector[3]; // [esp+94h] [ebp-F8h] BYREF
  float scaled_result[3]; // [esp+A0h] [ebp-ECh] BYREF
  float v27[3]; // [esp+ACh] [ebp-E0h] BYREF
  float v28[3]; // [esp+B8h] [ebp-D4h] BYREF
  float copy_result[3]; // [esp+C4h] [ebp-C8h] BYREF
  float destination[3]; // [esp+D0h] [ebp-BCh] BYREF
  float v31[4]; // [esp+DCh] [ebp-B0h] BYREF
  float v32[4]; // [esp+ECh] [ebp-A0h] BYREF
  float v33[4]; // [esp+FCh] [ebp-90h] BYREF
  float v34[4]; // [esp+10Ch] [ebp-80h] BYREF
  float v35[4]; // [esp+11Ch] [ebp-70h] BYREF
  float v36[4]; // [esp+12Ch] [ebp-60h] BYREF
  float v37[20]; // [esp+13Ch] [ebp-50h] BYREF

  rf_mesh_decal_query176_construct((char *)v31);
  if ( unk_9287B8 <= 0 )
    return nullptr;
  rf_mesh_decal_request80_copy(v37, a1);
  rf_vector3_default_construct_noop(destination);
  rf_vector_copy(destination, copy_result, a1 + 3);
  v2 = rf_vector_negate(a1 + 15, v28);
  rf_plane4_construct_normal_point(v31, v2, destination);
  rf_vector_copy(destination, v27, a1 + 6);
  rf_plane4_construct_normal_point(v32, a1 + 15, destination);
  v3 = rf_vector_multiply_scalar(a1 + 9, scaled_result, a1[2]);
  v4 = rf_vector_subtract(a1 + 3, out_vector, v3);
  rf_vector_copy(destination, v24, v4);
  v5 = rf_vector_negate(a1 + 9, v23);
  rf_plane4_construct_normal_point(v33, v5, destination);
  v6 = rf_vector_multiply_scalar(a1 + 9, v22, a1[2]);
  v7 = rf_vector_add(a1 + 3, sum_result, v6);
  rf_vector_copy(destination, v20, v7);
  rf_plane4_construct_normal_point(v34, a1 + 9, destination);
  v8 = rf_vector_multiply_scalar(a1 + 12, v19, a1[2]);
  v9 = rf_vector_add(a1 + 3, v18, v8);
  rf_vector_copy(destination, v17, v9);
  rf_plane4_construct_normal_point(v35, a1 + 12, destination);
  v10 = rf_vector_multiply_scalar(a1 + 12, v16, a1[2]);
  v11 = rf_vector_subtract(a1 + 3, v15, v10);
  rf_vector_copy(destination, v14, v11);
  v12 = rf_vector_negate(a1 + 12, v13);
  rf_plane4_construct_normal_point(v36, v12, destination);
  return rf_mesh_decal_collect_clipped_model_triangles(v31);
}

