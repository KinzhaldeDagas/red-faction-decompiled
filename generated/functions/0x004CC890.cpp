// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CC890 sub_4CC890
// UNREALRED VERIFIED [combat-particle-liquid-handoff-20261104]: Iterates ordered room faces with bounds overlap, front-plane segment intersection569600, strict t<1 and projected polygon containment. Plane start<0 is rejected, t=0 front-entry is permitted, endpoint t=1 rejected. Do not substitute glass AABB liquid helper (different boundary rules) or broad-scan all liquid rooms; caller4CC4E0 carries current room+portal traversal with depth limit5.
char __cdecl sub_4CC890(float *a1, float *a2, float *a3, float *lhs, int a5)
{
  float *v5; // eax
  float *v6; // eax
  float v8[3]; // [esp+4h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-2Ch] BYREF
  float sum_result[3]; // [esp+1Ch] [ebp-20h] BYREF
  float scaled_result[3]; // [esp+28h] [ebp-14h] BYREF
  float scalar; // [esp+34h] [ebp-8h] BYREF
  float *source; // [esp+38h] [ebp-4h]

  if ( rf_aabb_overlap_strict_ordered(a2, a3, a1 + 2, a1 + 5) )
  {
    for ( source = (float *)rf_receiver_get_first_dword(a1 + 10);
          source;
          source = (float *)rf_face_next_room_link((int)source) )
    {
      if ( rf_aabb_overlap_strict_ordered(source + 4, source + 7, a2, a3) )
      {
        if ( rf_polygon_segment_intersect_front_plane(lhs, lhs + 3, source, &scalar) )
        {
          if ( scalar < 1.0 )
          {
            v5 = rf_vector_multiply_scalar(lhs + 3, scaled_result, scalar);
            v6 = rf_vector_add(lhs, sum_result, v5);
            rf_vector_copy((float *)(a5 + 8), copy_result, v6);
            if ( rf_geomod_face_contains_projected_point(source, a5 + 8) )
            {
              rf_vector_copy((float *)(a5 + 20), v8, source);
              *(float *)(a5 + 4) = scalar;
              *(_DWORD *)(a5 + 36) = source;
              return 1;
            }
          }
        }
      }
    }
  }
  return 0;
}

