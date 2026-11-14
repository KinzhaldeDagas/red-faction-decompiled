// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051F710 rf_world_submit_room_effect_callbacks
// UNREALRED VERIFIED [room-render-20261028]: Skips work when roomnonnull and shared room predicate unknown_libname_11 true unless third byteargument set. Otherwise clears callback count0xA42048 and bytes0x930A39/3A. With room,thirdarg0 and global0x663B08 set, visits room neighbors+108; requires !neighbor byte2 predicate0x5211F0 OR0xA420A8,neighbor+106 nonzero,parent pointer+120==room and neighbor AABB not rejected by0x581C40. Submits neighbor callback0x51EF10 with center=(min+max)/2 and radius=length(center-min), metadata+124/+8/+20, marks0x930A39. Saves count then invokes0x4C1240(room),0x4B9BA0(room,firstarg),0x507790(room),blood-mark render; marks0x930A3A if count changed. Submits global particles and room emitters last. Return branch-dependent helper value, not count.
char __cdecl rf_world_submit_room_effect_callbacks(char a1, int a2, char a3)
{
  char result; // al
  int first_dword; // eax
  float *v5; // eax
  float *v6; // eax
  float out_vector[3]; // [esp+20h] [ebp-34h] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-28h] BYREF
  float lhs[3]; // [esp+38h] [ebp-1Ch] BYREF
  float v10; // [esp+44h] [ebp-10h]
  int v11; // [esp+48h] [ebp-Ch]
  int i; // [esp+4Ch] [ebp-8h]
  int v13; // [esp+50h] [ebp-4h]

  if ( !a2 || (result = unknown_libname_11((void *)a2)) == 0 || a3 )
  {
    *(_DWORD *)&byte_98967F[756169] = 0;
    unk_930A39 = 0;
    unk_930A3A = 0;
    if ( a2 && !a3 && dword_663B08 )
    {
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword((void *)(a2 + 108));
        if ( i >= first_dword )
          break;
        v11 = *(_DWORD *)sub_552200((_DWORD *)(a2 + 108), i);
        if ( (!sub_5211F0((_BYTE *)v11) || unk_A420A8)
          && *(_BYTE *)(v11 + 106)
          && *(_DWORD *)(v11 + 120) == a2
          && !rf_frustum_reject_aabb((float *)(v11 + 8), (float *)(v11 + 20)) )
        {
          v5 = rf_vector_add((const float *)(v11 + 20), sum_result, (const float *)(v11 + 8));
          rf_vector_multiply_scalar(v5, lhs, 0.5);
          v6 = rf_vector_subtract(lhs, out_vector, (const float *)(v11 + 8));
          v10 = rf_vector3_length(v6);
          rf_world_submit_render_callback_entry(
            v11,
            lhs,
            lhs,
            v10,
            (int)rf_world_queue_see_through_room_faces,
            *(_BYTE *)(v11 + 106),
            v11 + 124,
            v11 + 8,
            v11 + 20,
            0,
            1);
          unk_930A39 = 1;
        }
      }
    }
    v13 = *(_DWORD *)&byte_98967F[756169];
    rf_bolt_emitters_submit_callbacks_for_room(a2);
    rf_world_submit_object_callbacks_for_room(a2, a1);
    rf_vclip_effect_submit_callbacks_for_room(a2);
    rf_blood_surface_marks_render_for_region(a2);
    if ( *(_DWORD *)&byte_98967F[756169] != v13 )
      unk_930A3A = 1;
    rf_particle_submit_global_lists_for_room(a2);
    return rf_particle_submit_emitters_for_room(a2);
  }
  return result;
}

