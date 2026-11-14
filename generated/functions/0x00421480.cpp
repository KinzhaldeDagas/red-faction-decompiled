// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00421480 rf_weapon_present_reload_clip_ejection
// UNREALRED VERIFIED [reload-clip-physics-20261013] Reload magazine presentation. 0x4215F5 uses Entity+0x7EC, row1 (up) of aim matrix +0x7E0, multiplied by -0.6 for first-person prop displacement, NOT forward. 0x42166F copies FULL entity velocity +0x144 to config+48; 0x421683 copies aim orientation to config+12. Config+60 angular velocity remains zero from 0x419580; normalized temporary at 0x421643 is not copied there. No random orientation/spin call occurs. Lifetime config+72=1000ms, material+76=2, flags+84=12, object flags+88=0x10000, custom CONTACT sound+96 from WeaponInfo+0x4D8. Third constructor float0.3 is MASS via setup+0x14, not scale. No direct launch-sound call. Eight-RF-unit observer distance gate and first-person prop vs world-origin routing remain. Unreal adapts collision/settling through shared Chaos cosmetic debris; full observer reload replay is not established.
void __cdecl rf_weapon_present_reload_clip_ejection(unsigned int *entity, int a2)
{
  float *v2; // eax
  const float *v3; // eax
  char *v4; // eax
  float v5[3]; // [esp+10h] [ebp-ECh] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-E0h] BYREF
  _BYTE v7[12]; // [esp+28h] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+34h] [ebp-C8h] BYREF
  float out_attachment_position[3]; // [esp+40h] [ebp-BCh] BYREF
  int v10; // [esp+4Ch] [ebp-B0h]
  float v11[3]; // [esp+50h] [ebp-ACh] BYREF
  float v12; // [esp+5Ch] [ebp-A0h]
  float destination[3]; // [esp+60h] [ebp-9Ch] BYREF
  float out_corrected_position[3]; // [esp+6Ch] [ebp-90h] BYREF
  float v15[9]; // [esp+78h] [ebp-84h] BYREF
  float v16[15]; // [esp+9Ch] [ebp-60h] BYREF
  float out_orientation[6]; // [esp+D8h] [ebp-24h] BYREF
  float v18[3]; // [esp+F0h] [ebp-Ch] BYREF

  if ( entity )
  {
    if ( a2 )
    {
      if ( !rf_string_equals_case_insensitive(a2 + 1228, (char *)&byte_631A9E) )
      {
        if ( !dword_681E38
          || !*(_DWORD *)(dword_681E38 + 5168)
          || (rf_entity_view_copy_referenced_position(v11, *(_DWORD *)(*(_DWORD *)(dword_681E38 + 5168) + 196)),
              v12 = rf_vector_distance_squared(v11, (const float *)entity + 15),
              v12 <= 64.0) )
        {
          rf_geomod_debris_spawn_config_init((int)out_corrected_position);
          rf_matrix3_construct((char *)out_orientation);
          rf_vector3_default_construct_noop(destination);
          if ( !sub_438AC0((int)entity) || rf_view_wrapper_get_dword8(*(_DWORD *)(entity[1292] + 196)) )
          {
            rf_vector3_default_construct_noop(out_attachment_position);
            rf_entity_copy_weapon_attachment_transforms(
              entity,
              0,
              out_attachment_position,
              out_corrected_position,
              out_orientation);
          }
          else
          {
            v10 = rf_weapon_resolve_reload_clip_prop(entity[1292], a2);
            rf_vmesh_compose_prop_world_transform(
              *(_DWORD *)(entity[1292] + 52),
              v10,
              (float *)(entity[1292] + 4084),
              entity[1292] + 4120,
              (int)out_orientation,
              out_corrected_position);
            v2 = rf_vector_multiply_scalar((const float *)entity + 507, scaled_result, -0.60000002);
            rf_vector_accumulate(out_corrected_position, v2);
          }
          v3 = (const float *)rf_vector3_normalized_copy_unchecked(v18, (int)v7);
          rf_vector_copy(destination, copy_result, v3);
          rf_vector_copy(v16, v5, (const float *)entity + 81);
          rf_matrix3_copy(v15, (const float *)entity + 504);
          LODWORD(v16[14]) = 1000;
          LODWORD(v16[6]) = 1000;
          LODWORD(v16[7]) = 2;
          v16[8] = NAN;
          LODWORD(v16[9]) = 12;
          LODWORD(v16[10]) = 0x10000;
          v16[12] = *(float *)(a2 + 1240);
          v4 = (char *)rf_string_object_c_str_or_empty((const void *)(a2 + 1228));
          rf_physical_debris_piece_create(
            -1,
            v4,
            COERCE_VOID_(0.30000001),
            out_corrected_position,
            0,
            COERCE_VOID_(-1.0));
        }
      }
    }
  }
}

