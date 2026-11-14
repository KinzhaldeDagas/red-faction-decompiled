// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CFEB0 rf_world_tree_segment_nearest_nonportal_hit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, emitter extent ownership, underwater motion/pause state, projectile geometry continuation and native output writes): 
// Cdecl(root,ray6(start0,direction12),INOUT endpoint3f,INOUT solidResult(count0,fraction4,point8,normal20,face36)); returns AL whether any face accepted. Initializes global LIFO
// stack0x87AA90[1024] with root, tracks current node in global0x87AA88, no NULL-root, capacity/depth/cycle or reentrancy guard. Node AABB+0/+12 tests current finite segment
// start/endpoint; on admission walks face container+24. Skips signed portal-marker>0 through rf_face_is_portal(face+40) and liquid flags bit4 through rf_face_is_liquid. Negative or
// zero portal markers are not rejected merely as portal here.
// Each remaining face needs segment-AABB against bounds+16/+28, front-side plane helper fraction, then ORDERED currentResultFraction>candidate (TEST AH,0x41/JNZ rejects
// equal,less,unordered). Writes candidate point=start+ray.direction*fraction to result+8 BEFORE projected polygon containment. A rejected polygon can therefore clobber point even
// when return0 or an earlier accepted hit remains in fraction/normal/face. Accepted polygon copies face normal0 to result+20, fraction+4, face pointer+36, sets hit flag and clips
// caller endpoint to candidate; continues all faces and nodes. No initialization of result fraction/count, no count increment, no material filter or normal normalization.
// For admitted node, pushes child+32 then child+36; LIFO visits +36 first. A pruned node does not enqueue children. Current clipped endpoint and bound prune later candidates; equal
// fractions retain first accepted face, but point can still be overwritten by a smaller rejected candidate. Original caller0x4CFA50 shares this result bound across mover face scans
// and all world roots.
char __cdecl rf_world_tree_segment_nearest_nonportal_hit(int a1, float *lhs, float *destination, int a4)
{
  float *v4; // eax
  float *v5; // eax
  float v7[3]; // [esp+4h] [ebp-58h] BYREF
  float v8[3]; // [esp+10h] [ebp-4Ch] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-40h] BYREF
  float sum_result[3]; // [esp+28h] [ebp-34h] BYREF
  float scaled_result[3]; // [esp+34h] [ebp-28h] BYREF
  float *source; // [esp+40h] [ebp-1Ch]
  float scalar; // [esp+44h] [ebp-18h] BYREF
  int v14; // [esp+48h] [ebp-14h]
  char v15; // [esp+4Fh] [ebp-Dh]
  float v16[3]; // [esp+50h] [ebp-Ch] BYREF

  v15 = 0;
  rf_vector3_default_construct_noop(v16);
  unk_87AA90[0] = a1;
  v14 = 1;
  while ( v14 > 0 )
  {
    unk_87AA88 = unk_87AA90[--v14];
    if ( rf_segment_intersects_aabb(unk_87AA88, (float *)(unk_87AA88 + 12), lhs, destination, v16) )
    {
      for ( source = (float *)rf_receiver_get_first_dword((void *)(unk_87AA88 + 24));
            source;
            source = (float *)rf_face_next_spatial_node_link((int)source) )
      {
        if ( !rf_face_is_portal((__int16 *)source + 20)
          && !rf_face_is_liquid((_DWORD *)source + 10)
          && rf_segment_intersects_aabb(source + 4, source + 7, lhs, destination, v16)
          && rf_segment_plane_front_side_hit_fraction(lhs, lhs + 3, source, &scalar)
          && *(float *)(a4 + 4) > (double)scalar )
        {
          v4 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
          v5 = rf_vector_add(lhs, sum_result, v4);
          rf_vector_copy((float *)(a4 + 8), copy_result, v5);
          if ( rf_geomod_face_contains_projected_point(source, a4 + 8) )
          {
            rf_vector_copy((float *)(a4 + 20), v8, source);
            *(float *)(a4 + 4) = scalar;
            *(_DWORD *)(a4 + 36) = source;
            v15 = 1;
            rf_vector_copy(destination, v7, (const float *)(a4 + 8));
          }
        }
      }
      if ( *(_DWORD *)(unk_87AA88 + 32) )
        unk_87AA90[v14++] = *(_DWORD *)(unk_87AA88 + 32);
      if ( *(_DWORD *)(unk_87AA88 + 36) )
        unk_87AA90[v14++] = *(_DWORD *)(unk_87AA88 + 36);
    }
  }
  return v15;
}

