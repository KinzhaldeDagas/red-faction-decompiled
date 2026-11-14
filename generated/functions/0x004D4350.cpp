// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D4350 rf_world_segment_query_into_solid_hit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, shape-sphere/model/solid sweeps, x87 unordered gates, descriptor constructors and native output mutation): Cdecl start,end,low-byte public mask,caller solid-result pointer. Constructs solid query (only face-hint0 cleared), sets start52,displacement64=end-start,radius76=0,flags80=mask_to_query_flags(mask)|4. Writes caller result fraction4=1, calls global world-solid sweep initializeByte0; backend resets count0,edge32,face36 and preserves supplied fraction bound; point8/normal20 are not initialized by this wrapper and candidate/hit writes belong to backend. Returns normalized32-bit BOOL from SIGNED result count>0, not delegate EAX. No moving/model lists, entire-result zeroing or own face-cache management/NULL/finite checks. Query position4/orientation16 left uninitialized but bypass flag4 avoids reading them.
BOOL __cdecl rf_world_segment_query_into_solid_hit(float *rhs, float *lhs, char a3, int a4)
{
  float *v4; // eax
  float v6[3]; // [esp+0h] [ebp-94h] BYREF
  float out_vector[3]; // [esp+Ch] [ebp-88h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-7Ch] BYREF
  char v9[52]; // [esp+24h] [ebp-70h] BYREF
  float destination[3]; // [esp+58h] [ebp-3Ch] BYREF
  float v11[4]; // [esp+64h] [ebp-30h] BYREF
  int flags; // [esp+74h] [ebp-20h]

  rf_solid_collision_query_construct_clear_face_hint(v9);
  rf_vector_copy(destination, copy_result, rhs);
  v4 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v11, v6, v4);
  v11[3] = 0.0;
  flags = rf_geometry_segment_mask_to_query_flags(a3);
  *(float *)(a4 + 4) = 1.0;
  flags |= 4u;
  rf_world_collision_sweep((char *)rf_world_solid, (int)v9, a4, 0);
  return *(_DWORD *)a4 > 0;
}

