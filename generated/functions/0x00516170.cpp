// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00516170 rf_solid_rebuild_rooms_detail_refs_and_portals
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall solid,no stack args,void. Full destructive topology rebuild. First scalar-delete nonnull old room pointers from solid array144; release arrays144,168,156; scalar-delete nonnull auxiliary records180 and release180. If counted solid face-list112 countDWORD116 is0,return after this cleanup without clearing individual face.room68. Otherwise walk linked faces84, call flag8 getter but IGNORE its result,clear ALL face.room68 (the getter does not clear flag8). Allocate oneDWORD-per-count work stack using unsigned MUL4 with overflow Size=0xFFFFFFFF, not wrap-to-small; no allocation/stack-bound checks. In global face order seed every unowned face satisfying terrain
// eligibility(flags8/4clear,signedportalWORD52<=0) OR flag8. Construct460-byte room using seed face bounds16/28,attach seed; flag8 seed changes room BYTE0 to1 via517BE0, moving world membership from ordinary156 to detail168. Pop work faces LIFO. For EACH corner vertex inspect all incidence32 entries,excluding self. Collect unique portal faces(signedWORD52>0) only for ordinary BYTE0==0; nonportal candidates are terrain-eligible for ordinary rooms,flag8 for any nonzero detail type. This uses shared VERTEX incidence,not shared-edge/manifold proof. For each collected portal compute516F60(currentFace,portalPlane),attach portal only when vote true AND unowned; save EVERY portal vote in byte array. Attach/push each unowned candidate iff its516F60 votes match ALL saved portal votes; no portals means vacuous acceptance. Already-owned candidates cannot migrate. Portal faces are attached but not
// pushed. Temporary arrays are released/destroyed per work-face. After grouping,ordinary rooms whose first unambiguous outside-in ray returnsclass1 become detail. For every detail room resetBYTE106 then set1 on first face texture48>=0 whose resolved format is4/5/7; ordinary rooms invoke517BE0(...,0). Release EVERY room borrowed reference array108; only ordinary rooms rebuild it by scanning ALL authored rooms144 for detail rooms with inclusive AABB overlap. Use first detail face first corner point (unguarded nonempty lists) and517060(world,NULL,point,point,0); if returned ordinary room matches append detail. Otherwise ANY detail-face bounds overlap ordinary-room bounds AND ANY ordinary-face bounds overlap that detail-face bounds is sufficient to append once; this is broad-phase admission,not exact polygon intersection or full containment. Scan solid faces with cachednext84: for each portal
// gather UNIQUE different nonnull room owners from shared-vertex incident terrain-eligible faces. Keep/publish through557D00 only if portal own room68 exists and opposite-owner countEXACT1; otherwise unlink from solid and destroy portal face (including count0/count>1/no-own cases). Rebuild spatial tree of EVERY remaining authored room144,then free stack. No recomputation of solid bounds,face planes or authored input geometry; no rollback,allocation-failure handling,old owner preservation or normal-based room ordering. Native xor reg,reg;jnz self pairs are never-taken diagnostic remnants,not actual waits.
void __thiscall rf_solid_rebuild_rooms_detail_refs_and_portals(char *this)
{
  int first_dword; // eax
  int v2; // eax
  float **v3; // eax
  int *v4; // eax
  int v5; // eax
  float **v6; // eax
  int v7; // esi
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int *v13; // eax
  int v14; // eax
  int *v15; // [esp+8h] [ebp-128h]
  int *v16; // [esp+Ch] [ebp-124h]
  unsigned __int8 *v17; // [esp+10h] [ebp-120h]
  void *room; // [esp+24h] [ebp-10Ch]
  void *v20; // [esp+34h] [ebp-FCh]
  void *v21; // [esp+3Ch] [ebp-F4h]
  int v22; // [esp+40h] [ebp-F0h]
  int v23; // [esp+44h] [ebp-ECh]
  int *kk; // [esp+48h] [ebp-E8h]
  void *v25[3]; // [esp+4Ch] [ebp-E4h] BYREF
  _DWORD *link; // [esp+58h] [ebp-D8h]
  int ii; // [esp+5Ch] [ebp-D4h]
  int jj; // [esp+60h] [ebp-D0h]
  int v29; // [esp+64h] [ebp-CCh]
  char *v30; // [esp+68h] [ebp-C8h]
  float v31[3]; // [esp+6Ch] [ebp-C4h] BYREF
  float *v32; // [esp+78h] [ebp-B8h]
  char v33; // [esp+7Fh] [ebp-B1h]
  int n; // [esp+80h] [ebp-B0h]
  char v35[12]; // [esp+84h] [ebp-ACh] BYREF
  char *v36; // [esp+90h] [ebp-A0h]
  int m; // [esp+94h] [ebp-9Ch]
  unsigned __int8 *v38; // [esp+98h] [ebp-98h]
  int index; // [esp+9Ch] [ebp-94h]
  char v40; // [esp+A3h] [ebp-8Dh]
  int v41; // [esp+A4h] [ebp-8Ch]
  char v42; // [esp+ABh] [ebp-85h]
  int v43; // [esp+ACh] [ebp-84h]
  int v44; // [esp+B0h] [ebp-80h]
  void *v45[3]; // [esp+B4h] [ebp-7Ch] BYREF
  int *k; // [esp+C0h] [ebp-70h]
  void *header[3]; // [esp+C4h] [ebp-6Ch] BYREF
  int v48; // [esp+D0h] [ebp-60h]
  void *v49[3]; // [esp+D4h] [ebp-5Ch] BYREF
  unsigned __int8 *v50; // [esp+E0h] [ebp-50h]
  int v51; // [esp+E4h] [ebp-4Ch]
  _DWORD *v52; // [esp+E8h] [ebp-48h]
  int v53; // [esp+ECh] [ebp-44h]
  int v54; // [esp+F0h] [ebp-40h]
  int v55; // [esp+F4h] [ebp-3Ch]
  int v56; // [esp+F8h] [ebp-38h]
  int v57; // [esp+FCh] [ebp-34h]
  int *v58; // [esp+100h] [ebp-30h]
  int v59; // [esp+104h] [ebp-2Ch]
  int v60; // [esp+108h] [ebp-28h]
  int v61; // [esp+10Ch] [ebp-24h]
  _DWORD *j; // [esp+110h] [ebp-20h]
  int v63; // [esp+114h] [ebp-1Ch]
  int v64; // [esp+118h] [ebp-18h]
  int i; // [esp+11Ch] [ebp-14h]
  int v66; // [esp+120h] [ebp-10h]
  int v67; // [esp+12Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 144); ++i )
  {
    v21 = *(void **)sub_552200((_DWORD *)this + 36, i);
    if ( v21 )
      rf_room460_scalar_deleting_destructor_517cf0(v21, 1);
  }
  rf_pointer_array_release_storage((void **)this + 36);
  rf_pointer_array_release_storage((void **)this + 42);
  rf_pointer_array_release_storage((void **)this + 39);
  for ( i = 0; i < rf_receiver_get_first_dword(this + 180); ++i )
  {
    v20 = *(void **)sub_552200((_DWORD *)this + 45, i);
    if ( v20 )
      rf_solid_aux_scalar_deleting_destructor_517d20(v20, 1);
  }
  rf_pointer_array_release_storage((void **)this + 45);
  if ( rf_shared_second_dword_getter_518050((_DWORD *)this + 28) )
  {
    for ( j = (_DWORD *)rf_receiver_get_first_dword(this + 112); j; j = (_DWORD *)rf_solid_face_next_link((int)j) )
    {
      rf_face_metadata_has_flag8(j + 10);
      j[17] = 0;
    }
    v53 = rf_shared_second_dword_getter_518050((_DWORD *)this + 28);
    v52 = operator new(4 * v53);
    for ( j = (_DWORD *)rf_receiver_get_first_dword(this + 112); j; j = (_DWORD *)rf_solid_face_next_link((int)j) )
    {
      if ( !j[17]
        && (rf_geomod_terrain_component_face_eligible((__int16 *)j + 20) || rf_face_metadata_has_flag8(j + 10)) )
      {
        room = operator new(0x1CCu);
        v67 = 0;
        if ( room )
          v17 = (unsigned __int8 *)rf_room460_construct_register(room, this, (const float *)j + 4, (const float *)j + 7);
        else
          v17 = nullptr;
        v67 = -1;
        v50 = v17;
        rf_geomod_room_face_attach((float *)v17, (int)j);
        if ( rf_face_metadata_has_flag8(j + 10) )
          sub_517BE0(v50, (int)this, 1u);
        v51 = 0;
        *v52 = j;
        while ( v51 > -1 )
        {
          v48 = v52[v51--];
          rf_dword_array_construct_capacity(v49, 0);
          v67 = 1;
          rf_dword_array_construct_capacity(v45, 0);
          LOBYTE(v67) = 2;
          for ( k = *(int **)(v48 + 64); k; k = v16 )
          {
            v44 = *k;
            for ( i = 0; ; ++i )
            {
              first_dword = rf_receiver_get_first_dword((void *)(v44 + 32));
              if ( i >= first_dword )
                break;
              v43 = *(_DWORD *)sub_552200((_DWORD *)(v44 + 32), i);
              if ( v43 != v48 )
              {
                if ( rf_face_is_portal((__int16 *)(v43 + 40)) )
                {
                  if ( !unknown_libname_11(v50) )
                    rf_pointer_array_append_unique(v45, v43);
                }
                else if ( unknown_libname_11(v50) || !rf_geomod_terrain_component_face_eligible((__int16 *)(v43 + 40)) )
                {
                  if ( unknown_libname_11(v50) && rf_face_metadata_has_flag8((_DWORD *)(v43 + 40)) )
                    rf_pointer_array_append_unique(v49, v43);
                }
                else
                {
                  rf_pointer_array_append_unique(v49, v43);
                }
              }
            }
            if ( k[5] == *(_DWORD *)(v48 + 64) )
              v16 = nullptr;
            else
              v16 = (int *)k[5];
          }
          rf_byte_array_construct_capacity_wrapper(header, 0);
          LOBYTE(v67) = 3;
          for ( i = 0; ; ++i )
          {
            v2 = rf_receiver_get_first_dword(v45);
            if ( i >= v2 )
              break;
            v3 = (float **)sub_552200(v45, i);
            v42 = rf_geomod_face_portal_side_vote(v48, *v3);
            if ( v42 && !*(_DWORD *)(*(_DWORD *)sub_552200(v45, i) + 68) )
            {
              v4 = (int *)sub_552200(v45, i);
              rf_geomod_room_face_attach((float *)v50, *v4);
            }
            rf_byte_array_append(header, v42);
          }
          for ( i = 0; ; ++i )
          {
            v5 = rf_receiver_get_first_dword(v49);
            if ( i >= v5 )
              break;
            v41 = *(_DWORD *)sub_552200(v49, i);
            if ( !*(_DWORD *)(v41 + 68) )
            {
              v40 = 1;
              for ( index = 0; index < rf_receiver_get_first_dword(v45); ++index )
              {
                v6 = (float **)sub_552200(v45, index);
                v7 = rf_geomod_face_portal_side_vote(v41, *v6);
                if ( v7 != *rf_byte_array_element_address_unchecked(header, index) )
                {
                  v40 = 0;
                  break;
                }
              }
              if ( v40 )
              {
                rf_geomod_room_face_attach((float *)v50, v41);
                v52[++v51] = v41;
              }
            }
          }
          rf_pointer_array_release_storage(v49);
          rf_pointer_array_release_storage(v45);
          rf_pointer_array_release_storage(header);
          LOBYTE(v67) = 2;
          rf_pointer_array_destroy_backing_storage(header);
          LOBYTE(v67) = 1;
          rf_pointer_array_destroy_backing_storage(v45);
          v67 = -1;
          rf_pointer_array_destroy_backing_storage(v49);
        }
      }
    }
    v66 = 0;
    v59 = 0;
    v55 = 0;
    for ( i = 0; ; ++i )
    {
      v8 = rf_receiver_get_first_dword(this + 144);
      if ( i >= v8 )
        break;
      v38 = *(unsigned __int8 **)sub_552200((_DWORD *)this + 36, i);
      if ( !unknown_libname_11(v38) && rf_geomod_room_first_unambiguous_ray_is_class1((float *)v38) )
      {
        ++v55;
        sub_517BE0(v38, (int)this, 1u);
      }
      if ( unknown_libname_11(v38) )
      {
        v38[106] = 0;
        for ( m = rf_receiver_get_first_dword(v38 + 40); m; m = rf_face_next_room_link(m) )
        {
          if ( *(int *)(m + 48) >= 0 && rf_bitmap_resolved_format_is_4_5_7(*(_DWORD *)(m + 48)) )
          {
            v38[106] = 1;
            break;
          }
        }
        if ( v38[106] )
          ++v59;
        else
          ++v66;
      }
      else
      {
        sub_517BE0(v38, (int)this, 0);
      }
    }
    v56 = rf_performance_clock_elapsed_scaled(1000);
    for ( i = 0; ; ++i )
    {
      v9 = rf_receiver_get_first_dword(this + 144);
      if ( i >= v9 )
        break;
      v36 = *(char **)sub_552200((_DWORD *)this + 36, i);
      rf_pointer_array_release_storage((void **)v36 + 27);
      if ( !unknown_libname_11(v36) )
      {
        rf_vector3_default_construct_noop(v35);
        for ( n = 0; ; ++n )
        {
          v10 = rf_receiver_get_first_dword(this + 144);
          if ( n >= v10 )
            break;
          v33 = 0;
          v32 = *(float **)sub_552200((_DWORD *)this + 36, n);
          if ( unknown_libname_11(v32)
            && rf_aabb_overlap_inclusive(v32 + 2, v32 + 5, (float *)v36 + 2, (float *)v36 + 5) )
          {
            v29 = rf_receiver_get_first_dword(v32 + 10);
            rf_vector3_copy_return_destination(v31, **(float ***)(v29 + 64));
            v30 = (char *)rf_world_resolve_cached_room(this, nullptr, v31, v31, 0);
            if ( v30 == v36 )
            {
              rf_pointer_array_append_dword((_DWORD *)v36 + 27, (int)v32);
            }
            else
            {
              for ( ii = rf_receiver_get_first_dword(v32 + 10); ii; ii = rf_face_next_room_link(ii) )
              {
                if ( rf_aabb_overlap_inclusive(
                       (float *)(ii + 16),
                       (float *)(ii + 28),
                       (float *)v36 + 2,
                       (float *)v36 + 5) )
                {
                  for ( jj = rf_receiver_get_first_dword(v36 + 40); jj; jj = rf_face_next_room_link(jj) )
                  {
                    if ( rf_aabb_overlap_inclusive(
                           (float *)(ii + 16),
                           (float *)(ii + 28),
                           (float *)(jj + 16),
                           (float *)(jj + 28)) )
                    {
                      rf_pointer_array_append_dword((_DWORD *)v36 + 27, (int)v32);
                      v33 = 1;
                      break;
                    }
                  }
                  if ( v33 )
                    break;
                }
              }
            }
          }
        }
      }
    }
    v60 = rf_performance_clock_elapsed_scaled(1000);
    v63 = 0;
    v54 = 0;
    v57 = 0;
    v61 = 0;
    v64 = 0;
    for ( j = (_DWORD *)rf_receiver_get_first_dword(this + 112); j; j = link )
    {
      link = (_DWORD *)rf_solid_face_next_link((int)j);
      if ( rf_face_is_portal((__int16 *)j + 20) )
      {
        rf_dword_array_construct_capacity(v25, 0);
        v67 = 4;
        for ( kk = (int *)j[16]; kk; kk = v15 )
        {
          v23 = *kk;
          for ( i = 0; ; ++i )
          {
            v11 = rf_receiver_get_first_dword((void *)(v23 + 32));
            if ( i >= v11 )
              break;
            v12 = sub_552200((_DWORD *)(v23 + 32), i);
            v22 = *(_DWORD *)v12;
            if ( *(_DWORD *)(*(_DWORD *)v12 + 68) != j[17]
              && *(_DWORD *)(v22 + 68)
              && rf_geomod_terrain_component_face_eligible((__int16 *)(v22 + 40)) )
            {
              rf_pointer_array_append_unique(v25, *(_DWORD *)(v22 + 68));
            }
          }
          if ( kk[5] == j[16] )
            v15 = nullptr;
          else
            v15 = (int *)kk[5];
        }
        if ( j[17] )
        {
          if ( rf_receiver_get_first_dword(v25) )
          {
            if ( rf_receiver_get_first_dword(v25) == 1 )
            {
              v13 = (int *)sub_552200(v25, 0);
              rf_world_assign_face_runtime_room_portal(this, (int)j, j[17], *v13);
              ++v63;
            }
            else
            {
              ++v54;
              rf_solid_face_list_remove((int *)this + 28, (int)j);
              rf_geomod_face_destroy(j);
              j = nullptr;
            }
          }
          else
          {
            rf_solid_face_list_remove((int *)this + 28, (int)j);
            rf_geomod_face_destroy(j);
            j = nullptr;
            ++v57;
          }
        }
        else
        {
          rf_solid_face_list_remove((int *)this + 28, (int)j);
          rf_geomod_face_destroy(j);
          j = nullptr;
          ++v61;
        }
        v67 = -1;
        rf_pointer_array_destroy_backing_storage(v25);
      }
    }
    for ( i = 0; ; ++i )
    {
      v14 = rf_receiver_get_first_dword(this + 144);
      if ( i >= v14 )
        break;
      v58 = *(int **)sub_552200((_DWORD *)this + 36, i);
      rf_room_face_spatial_tree_rebuild(v58);
    }
    operator delete(v52);
  }
}

