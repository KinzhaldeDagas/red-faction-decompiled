// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C58B0 rf_glass_face_shatter_dispatch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl face,impactPosition,optionalDirection. Computes F32 AABB center=(face.min16+max28)*.5, resolves room with NULLcachedRoom,start=end=center,flags0. Missing room exits with no
// tessellation/reactivation. Does NOT validate/register four corners itself. Assumes corner ring face64:
// P0=head.vertex0,P1=head.next20.vertex,P3=head.prev24.vertex,P2=head.next.next.vertex. Normalizes e=P1-P0,f=P2-P1,g=P3-P0 (zero/NaN length unitX fallback). Takes F32abs(dot(g,e));
// rectangular path only if STRICT ORDERED value<DOUBLE0.00009999999747378752 AND second F32abs(dot(f,-e))<same. Equality OR unordered at either comparison routes GENERAL quad
// tessellator; do not invert ordered>= pseudocode for NaN. Forwards face/impact/direction/room unchanged.
// After tessellator, expands ORIGINAL face AABB by F32.1 each axis. Walks list head911F74/sentinel911CE8 via physical next652, strict ordered AABB overlap against node400/412
// ->request_physics_reactivation_flags. Computes expanded extents max-min; only STRICT ORDERED extentX>extentY AND extentZ>extentY permits three ADDITIONAL walks:
// head68211C/sentinel681E90,corpse list/sentinel681AF8,physical debris list/sentinel; same overlap/reactivate. Equality/NaN fails extra-list gate. No output/cache rebuild, own face
// deletion, room-crossing update, finite/corner pointer guard or retained snapshot of nodes across callbacks; next loaded after callbacks. Registry/sound handled by caller.
void __cdecl rf_glass_face_shatter_dispatch(int a1, int a2, int a3)
{
  float *v3; // eax
  float *v4; // eax
  float v5; // [esp+4h] [ebp-B8h]
  float v6; // [esp+8h] [ebp-B4h]
  float v7[3]; // [esp+Ch] [ebp-B0h] BYREF
  float sum_result[3]; // [esp+18h] [ebp-A4h] BYREF
  int j; // [esp+24h] [ebp-98h]
  int m; // [esp+28h] [ebp-94h]
  int k; // [esp+2Ch] [ebp-90h]
  float lhs[3]; // [esp+30h] [ebp-8Ch] BYREF
  float v13; // [esp+3Ch] [ebp-80h] BYREF
  float v14; // [esp+40h] [ebp-7Ch]
  float v15; // [esp+44h] [ebp-78h]
  float v16[3]; // [esp+48h] [ebp-74h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-68h] BYREF
  float v18[3]; // [esp+60h] [ebp-5Ch] BYREF
  float v19[3]; // [esp+6Ch] [ebp-50h] BYREF
  float scaled_result[3]; // [esp+78h] [ebp-44h] BYREF
  float v21[3]; // [esp+84h] [ebp-38h] BYREF
  float v22[3]; // [esp+90h] [ebp-2Ch] BYREF
  float v23[3]; // [esp+9Ch] [ebp-20h] BYREF
  int i; // [esp+A8h] [ebp-14h]
  float rhs[3]; // [esp+ACh] [ebp-10h] BYREF
  void *v26; // [esp+B8h] [ebp-4h]

  v3 = rf_vector_add((const float *)(a1 + 28), sum_result, (const float *)(a1 + 16));
  rf_vector_multiply_scalar(v3, scaled_result, 0.5);
  v26 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, scaled_result, scaled_result, 0);
  if ( v26 )
  {
    rf_vector3_copy_return_destination(rhs, **(float ***)(a1 + 64));
    rf_vector3_copy_return_destination(lhs, **(float ***)(*(_DWORD *)(a1 + 64) + 20));
    rf_vector3_copy_return_destination(v23, **(float ***)(*(_DWORD *)(a1 + 64) + 24));
    rf_vector3_copy_return_destination(v21, **(float ***)(*(_DWORD *)(*(_DWORD *)(a1 + 64) + 20) + 20));
    rf_vector_subtract(lhs, out_vector, rhs);
    rf_vector_subtract(v21, v16, lhs);
    rf_vector_subtract(v23, v18, rhs);
    rf_vector_normalize(out_vector);
    rf_vector_normalize(v16);
    rf_vector_normalize(v18);
    v6 = fabs(rf_vector_dot(v18, out_vector));
    if ( v6 >= 0.00009999999747378752
      || (v4 = rf_vector_negate(out_vector, v7), v5 = fabs(rf_vector_dot(v16, v4)), v5 >= 0.00009999999747378752) )
    {
      rf_glass_general_quad_face_tessellate(a1, a2, a3, (int)v26);
    }
    else
    {
      rf_glass_rectangular_face_tessellate(a1, a2, a3, (int)v26);
    }
    rf_vector3_subtract_scalar_from_components((float *)(a1 + 16), v19, 0.1);
    rf_vector3_add_scalar_to_components((float *)(a1 + 28), v22, 0.1);
    for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
    {
      if ( rf_aabb_overlap_strict_ordered(v19, v22, (float *)(i + 400), (float *)(i + 412)) )
        rf_object_request_physics_reactivation_flags(i);
    }
    rf_vector_subtract(v22, &v13, v19);
    if ( v13 > (double)v14 && v15 > (double)v14 )
    {
      for ( j = dword_68211C; (_UNKNOWN *)j != &unk_681E90; j = *(_DWORD *)(j + 652) )
      {
        if ( rf_aabb_overlap_strict_ordered(v19, v22, (float *)(j + 400), (float *)(j + 412)) )
          rf_object_request_physics_reactivation_flags(j);
      }
      for ( k = rf_corpse_list_head; (_UNKNOWN *)k != &unk_681AF8; k = *(_DWORD *)(k + 652) )
      {
        if ( rf_aabb_overlap_strict_ordered(v19, v22, (float *)(k + 400), (float *)(k + 412)) )
          rf_object_request_physics_reactivation_flags(k);
      }
      for ( m = rf_physical_debris_list_head; (_UNKNOWN *)m != &rf_physical_debris_list_sentinel; m = *(_DWORD *)(m + 652) )
      {
        if ( rf_aabb_overlap_strict_ordered(v19, v22, (float *)(m + 400), (float *)(m + 412)) )
          rf_object_request_physics_reactivation_flags(m);
      }
    }
  }
}

