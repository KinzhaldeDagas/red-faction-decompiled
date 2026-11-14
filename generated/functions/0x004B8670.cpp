// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B8670 rf_geomod_postcut_world_object_update
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, push-region/GeoMod/use-selector/physics batch chains, original float constants and field widths and native
// signed/x87/stack/callback ABI): Five cdecl args(center pointer,radius float,AABB-pair array,signed count,LOWBYTE removal mode). Nonzero removal mode removes blood marks in
// each24-byte min/max box, then in sphere(center,float32(2*radius)); this mark pass occurs even for nonpositive radius and nonpositive count. Common live-list walk follows next+16
// after processing to sentinel7D0C80. Only objects with common bit0x400000, NO resolved mover for handle+48, and common liquid bit0x80000 clear proceed. For EACH strict-overlapping
// AABB versus object bounds+400/+412: non-clutter with any physics flags+424 mask0x71 requests flag-only reactivation40D5B0, otherwise removal requires nonzero mode and common bit4
// clear. No break after a hit; callbacks may repeat. Independently, ordered radius>0 enters sphere test using physics position+228; squared distance rounded float32 must be ordered
// strictly below (float32(object radius+384+input radius))^2. Sphere deletion category is (type4 and FLOAT+120 ordered<3) OR type1 OR type7. Item resolution by full handle+44
// suppresses deletion for item flags+700 bit1 or any nonzero splitscreen/runtime byte. Common bit4 or inactive bit0x4000 suppresses sphere deletion for all deletion-category types.
// Remaining admitted object is marked deferred-delete. Non-deletion-category objects with physics mask0x71 request reactivation. Sphere processing is independent of removal mode; an
// AABB mark does not skip the sphere test. No direct object destruction, position/bounds update, zeroing velocity or physics-enable call. No own upper count cap or array validation.
void __cdecl rf_geomod_postcut_world_object_update(float *rhs, float a2, int a3, int a4, char a5)
{
  float *v5; // eax
  float v6; // [esp+4h] [ebp-44h]
  float copy_result[3]; // [esp+8h] [ebp-40h] BYREF
  float out_vector[3]; // [esp+14h] [ebp-34h] BYREF
  int v9; // [esp+20h] [ebp-28h]
  char v10; // [esp+27h] [ebp-21h]
  float v11; // [esp+28h] [ebp-20h]
  float v12; // [esp+2Ch] [ebp-1Ch]
  int v13; // [esp+30h] [ebp-18h]
  float destination[3]; // [esp+34h] [ebp-14h] BYREF
  int j; // [esp+40h] [ebp-8h]
  int i; // [esp+44h] [ebp-4h]

  rf_vector3_default_construct_noop(destination);
  if ( a5 )
  {
    for ( i = 0; i < a4; ++i )
      rf_blood_surface_marks_remove_in_aabb((int)rhs, (float *)(a3 + 24 * i), (float *)(a3 + 24 * i + 12));
    v6 = a2 + a2;
    rf_blood_surface_marks_remove_in_sphere(rhs, v6);
  }
  for ( j = unk_7D0C90; (_UNKNOWN *)j != &unk_7D0C80; j = *(_DWORD *)(j + 16) )
  {
    if ( rf_object_blocks_when_dead(j) )
    {
      v13 = rf_mover_resolve_handle(*(_DWORD *)(j + 48));
      if ( !v13 && (*(_DWORD *)(j + 124) & 0x80000) == 0 )
      {
        for ( i = 0; i < a4; ++i )
        {
          if ( rf_aabb_overlap_strict_ordered(
                 (float *)(j + 400),
                 (float *)(j + 412),
                 (float *)(a3 + 24 * i),
                 (float *)(a3 + 24 * i + 12)) )
          {
            if ( *(_DWORD *)(j + 36) == 4 || (*(_DWORD *)(j + 424) & 0x71) == 0 )
            {
              if ( a5 )
              {
                if ( (*(_DWORD *)(j + 124) & 4) == 0 )
                  rf_object_mark_for_deferred_delete(j);
              }
            }
            else
            {
              rf_object_request_physics_reactivation_flags(j);
            }
          }
        }
        if ( a2 > 0.0 )
        {
          v5 = rf_vector_subtract((const float *)(j + 228), out_vector, rhs);
          rf_vector_copy(destination, copy_result, v5);
          v12 = rf_vector_length_squared(destination);
          v11 = *(float *)(j + 384) + a2;
          if ( v12 < v11 * v11 )
          {
            if ( *(_DWORD *)(j + 36) == 4 && *(float *)(j + 120) < 3.0
              || *(_DWORD *)(j + 36) == 1
              || *(_DWORD *)(j + 36) == 7 )
            {
              v10 = 1;
              v9 = rf_item_resolve_handle(*(_DWORD *)(j + 44));
              if ( v9 && (*(_DWORD *)(v9 + 700) & 1) != 0 )
                v10 = 0;
              if ( v9 && (rf_splitscreen_runtime_active || rf_multiplayer_runtime_mode) )
                v10 = 0;
              if ( (*(_DWORD *)(j + 124) & 4) != 0 || (*(_DWORD *)(j + 124) & 0x4000) != 0 )
                v10 = 0;
              if ( v10 )
                rf_object_mark_for_deferred_delete(j);
            }
            else if ( (*(_DWORD *)(j + 424) & 0x71) != 0 )
            {
              rf_object_request_physics_reactivation_flags(j);
            }
          }
        }
      }
    }
  }
}

