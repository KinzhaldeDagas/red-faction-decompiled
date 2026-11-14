// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00513F60 rf_mesh_decal_clip_polygon_take_pool_records
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Cdecl query176*,inputVertexXYZ*,signedcount,caller pops12;return36-byte pooled polygon orNULL. Before mutation require signed global polygonFree9287BC>0,clip against six consecutive16-byte planes atquery0 using5C8E30 into local16-vector scratch,require nonzero returned count AND count<=signed vertexFree9287C0 (equality allowed). No extra16-output cap here;normal caller passes triangle3. Pop free polygon from sentinel92DD68 via links28/32;initialize circular vertex sentinel withhead20=tail24=polygon;--polygonFree. ComputeF32 s=1/(2*query.radius104),no zero/finite guard. For each clipped point pop global free vertexhead9287D8 (28-byte record),copy mesh-local xyz0..8 unchanged;form F32
// local=point-query.start108 then row-dot inverse-rotate byquery.matrix132;writeUV12/16=local.xy*s+double0.5 asF32,without clamp/wrap. Unlink vertex from free ring20/24 and tailappend to polygon ring usingpolygon itself as sentinel. Subtract total output count fromvertexFree once afterloop. No heap fallback,world coordinate transform,polygon-area/normal test,rollback or per-record validation. Does not attach polygon to a collection;5141A0 does that. Dead XOR/JNZ pairs are never-taken remnants.
float *__cdecl rf_mesh_decal_clip_polygon_take_pool_records(int a1, int a2, int a3)
{
  float *v4; // eax
  float v5[3]; // [esp+0h] [ebp-100h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-F4h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-E8h] BYREF
  float *v8; // [esp+24h] [ebp-DCh]
  float lhs[48]; // [esp+28h] [ebp-D8h] BYREF
  float v10; // [esp+E8h] [ebp-18h]
  int i; // [esp+ECh] [ebp-14h]
  float *destination; // [esp+F0h] [ebp-10h]
  float v13[3]; // [esp+F4h] [ebp-Ch] BYREF
  int v14; // [esp+110h] [ebp+10h]

  rf_vector_construct_no_unwind((char *)lhs, 0xCu, 16, rf_vector3_default_construct_noop);
  rf_vector3_default_construct_noop(v13);
  if ( dword_9287BC <= 0 )
    return nullptr;
  v14 = rf_clip_polygon_against_planes(a3, a2, (int)lhs, a1, 6);
  if ( !v14 )
    return nullptr;
  if ( v14 > dword_9287C0 )
    return nullptr;
  v8 = (float *)unk_92DD84;
  *(_DWORD *)(*(_DWORD *)(unk_92DD84 + 32) + 28) = *(_DWORD *)(unk_92DD84 + 28);
  *(float *)(*((_DWORD *)v8 + 7) + 32) = v8[8];
  v8[7] = 0.0;
  v8[8] = 0.0;
  *((_DWORD *)v8 + 5) = v8;
  *((_DWORD *)v8 + 6) = v8;
  --dword_9287BC;
  v10 = 1.0 / (*(float *)(a1 + 104) + *(float *)(a1 + 104));
  for ( i = 0; i < v14; ++i )
  {
    destination = dword_9287D8;
    rf_vector_copy(dword_9287D8, copy_result, &lhs[3 * i]);
    v4 = rf_vector_subtract(&lhs[3 * i], out_vector, (const float *)(a1 + 108));
    rf_vector_copy(v13, v5, v4);
    rf_matrix3_inverse_rotate_vector(v13, (float *)(a1 + 132));
    destination[3] = v13[0] * v10 + 0.5;
    destination[4] = v13[1] * v10 + 0.5;
    *(float *)(*((_DWORD *)destination + 6) + 20) = destination[5];
    *(float *)(*((_DWORD *)destination + 5) + 24) = destination[6];
    destination[5] = 0.0;
    destination[6] = 0.0;
    destination[6] = v8[6];
    *((_DWORD *)destination + 5) = v8;
    *(_DWORD *)(*((_DWORD *)v8 + 6) + 20) = destination;
    *((_DWORD *)v8 + 6) = destination;
  }
  dword_9287C0 -= v14;
  return v8;
}

