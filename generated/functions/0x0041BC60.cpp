// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041BC60 rf_glare_render_surface_reflection_quad
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, glare visibility/reflection and cached-query initialization, native flags/x87 gates and static ownership): Cdecl glare. Disabled byte+652, zero reflection handle(definition+48), owner room with byte353==0, or rejected later gate clears runtime flags+692 mask0x10000000 and exits. Return is path-dependent glare-pointer or flags bits, not bool. Copies renderer current view position and FULL36-byte matrix, defining forward at EBP-80h despite split locals. Distance to glare must be <=20 OR unordered. From camera+0.5*distance*normalize(glare-camera), sweeps displacement(0,-100,0) in world solid with identity pose,radius0,flags0,initializeByte1. Requires signed positive hit count and face flags mask2 OR4. Projects glare and camera onto hit plane without normal-length division; reflection candidate lies on their projected
// segment at distance hCamera*projectedDistance/(hCamera+hGlare) from camera projection. No zero denominator guard. If cached vector+704 differs from(-1000,-1000,-1000) and flags0x10000000 was set, instead moves cached point TOWARD RAW DOWNWARD HIT POINT by normalized step0.15000000596046448, reducing step to remaining distance only when ordered smaller. No dt scaling. Otherwise uses newly constructed reflection candidate. Writes cache+704 BEFORE subsequent visibility/alpha gates, even if rendering later fails. Normalizes direction camera->candidate; forward dot>=0 OR unordered admits, then cameraY-.75>=candidateY+.1 OR unordered, then0x41B2A0 must report clear. Let t=(20-distance)/20: alpha=clamp(t*255*(dot*.4000000059604645+.6000000238418579),0,255), size=clamp(t*1.25+.75,.75,2). Alpha>=5 OR unordered admits. Builds normal-oriented square using half-size right/up:
// corners(+R+U),(+R-U),(-R-U),(-R+U), UV(0,0),(0,1),(1,1),(1,0). UV iterator stride8 uses NO-WRITE vec3 constructors, so it does not overwrite adjacent records. Unless normal equals exactly(0,1,0), projects each corner onto hit plane and offsets by normal*.1; exact-up uses(0,.1,0). Submits four world vertices with reflection texture,state(2,2,3,2,1,3),WHITE RGB,low byte trunc(alpha). SUCCESS performs flags+692 &=0x10000000, NOT OR: clears every OTHER bit and cannot set reflection bit if previously absent. Failures instead &=0xEFFFFFFF. No finite/current-view/hit-face/null/denominator guard, state rollback, previous flags restoration or explicit fog changes.
float *__cdecl rf_glare_render_surface_reflection_quad(float *glare)
{
  float *result; // eax
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  double v9; // st7
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  float *v19; // eax
  float *v20; // eax
  float *v21; // eax
  float *v22; // eax
  float *v23; // eax
  float *v24; // eax
  float *v25; // eax
  float *v26; // eax
  float *v27; // eax
  float *v28; // eax
  float *v29; // eax
  float *v30; // eax
  float *v31; // eax
  float *v32; // eax
  float *v33; // eax
  const float *v34; // eax
  const float *v35; // eax
  const float *v36; // eax
  const float *v37; // eax
  float *v38; // eax
  float *v39; // eax
  int scalar; // [esp+8h] [ebp-4F0h]
  int scalara; // [esp+8h] [ebp-4F0h]
  int scalarb; // [esp+8h] [ebp-4F0h]
  int scalarc; // [esp+8h] [ebp-4F0h]
  int v44; // [esp+10h] [ebp-4E8h]
  float *v45; // [esp+10h] [ebp-4E8h]
  int v46; // [esp+10h] [ebp-4E8h]
  float *v47; // [esp+10h] [ebp-4E8h]
  int v48; // [esp+10h] [ebp-4E8h]
  float *v49; // [esp+10h] [ebp-4E8h]
  int v50; // [esp+10h] [ebp-4E8h]
  float *v51; // [esp+10h] [ebp-4E8h]
  float v52[3]; // [esp+14h] [ebp-4E4h] BYREF
  float v53[3]; // [esp+20h] [ebp-4D8h] BYREF
  float v54[3]; // [esp+2Ch] [ebp-4CCh] BYREF
  float v55[3]; // [esp+38h] [ebp-4C0h] BYREF
  float v56[3]; // [esp+44h] [ebp-4B4h] BYREF
  _BYTE v57[12]; // [esp+50h] [ebp-4A8h] BYREF
  float v58[3]; // [esp+5Ch] [ebp-49Ch] BYREF
  _BYTE v59[12]; // [esp+68h] [ebp-490h] BYREF
  float v60[3]; // [esp+74h] [ebp-484h] BYREF
  _BYTE v61[12]; // [esp+80h] [ebp-478h] BYREF
  float v62[3]; // [esp+8Ch] [ebp-46Ch] BYREF
  _BYTE v63[12]; // [esp+98h] [ebp-460h] BYREF
  float v64[3]; // [esp+A4h] [ebp-454h] BYREF
  float v65[3]; // [esp+B0h] [ebp-448h] BYREF
  float v66[3]; // [esp+BCh] [ebp-43Ch] BYREF
  float v67[3]; // [esp+C8h] [ebp-430h] BYREF
  float v68[3]; // [esp+D4h] [ebp-424h] BYREF
  float v69[3]; // [esp+E0h] [ebp-418h] BYREF
  float v70[3]; // [esp+ECh] [ebp-40Ch] BYREF
  float v71[3]; // [esp+F8h] [ebp-400h] BYREF
  float v72[3]; // [esp+104h] [ebp-3F4h] BYREF
  float v73[3]; // [esp+110h] [ebp-3E8h] BYREF
  float v74[3]; // [esp+11Ch] [ebp-3DCh] BYREF
  float v75[3]; // [esp+128h] [ebp-3D0h] BYREF
  float v76[3]; // [esp+134h] [ebp-3C4h] BYREF
  float v77[3]; // [esp+140h] [ebp-3B8h] BYREF
  float v78[3]; // [esp+14Ch] [ebp-3ACh] BYREF
  float v79[3]; // [esp+158h] [ebp-3A0h] BYREF
  float v80[3]; // [esp+164h] [ebp-394h] BYREF
  float v81[3]; // [esp+170h] [ebp-388h] BYREF
  float v82[3]; // [esp+17Ch] [ebp-37Ch] BYREF
  float v83[3]; // [esp+188h] [ebp-370h] BYREF
  float v84[3]; // [esp+194h] [ebp-364h] BYREF
  float v85[3]; // [esp+1A0h] [ebp-358h] BYREF
  float v86[3]; // [esp+1ACh] [ebp-34Ch] BYREF
  float v87[3]; // [esp+1B8h] [ebp-340h] BYREF
  float v88[3]; // [esp+1C4h] [ebp-334h] BYREF
  float v89[3]; // [esp+1D0h] [ebp-328h] BYREF
  float v90[3]; // [esp+1DCh] [ebp-31Ch] BYREF
  float v91[3]; // [esp+1E8h] [ebp-310h] BYREF
  float v92[3]; // [esp+1F4h] [ebp-304h] BYREF
  float v93[3]; // [esp+200h] [ebp-2F8h] BYREF
  float v94[3]; // [esp+20Ch] [ebp-2ECh] BYREF
  float v95[3]; // [esp+218h] [ebp-2E0h] BYREF
  float v96[3]; // [esp+224h] [ebp-2D4h] BYREF
  float v97[3]; // [esp+230h] [ebp-2C8h] BYREF
  float v98[3]; // [esp+23Ch] [ebp-2BCh] BYREF
  float v99[3]; // [esp+248h] [ebp-2B0h] BYREF
  float v100[3]; // [esp+254h] [ebp-2A4h] BYREF
  float v101[3]; // [esp+260h] [ebp-298h] BYREF
  float sum_result[3]; // [esp+26Ch] [ebp-28Ch] BYREF
  float v103[3]; // [esp+278h] [ebp-280h] BYREF
  float v104[3]; // [esp+284h] [ebp-274h] BYREF
  float v105[3]; // [esp+290h] [ebp-268h] BYREF
  float v106[3]; // [esp+29Ch] [ebp-25Ch] BYREF
  float v107[3]; // [esp+2A8h] [ebp-250h] BYREF
  float v108[3]; // [esp+2B4h] [ebp-244h] BYREF
  float copy_result[3]; // [esp+2C0h] [ebp-238h] BYREF
  float v110[3]; // [esp+2CCh] [ebp-22Ch] BYREF
  float scaled_result[3]; // [esp+2D8h] [ebp-220h] BYREF
  float v112[4]; // [esp+2E4h] [ebp-214h] BYREF
  float v113[3]; // [esp+2F4h] [ebp-204h] BYREF
  float v114[3]; // [esp+300h] [ebp-1F8h] BYREF
  float v115; // [esp+30Ch] [ebp-1ECh]
  int first_dword; // [esp+310h] [ebp-1E8h]
  float v117; // [esp+314h] [ebp-1E4h]
  int v118; // [esp+318h] [ebp-1E0h] BYREF
  float source[3]; // [esp+31Ch] [ebp-1DCh] BYREF
  _DWORD v120[2]; // [esp+328h] [ebp-1D0h] BYREF
  float v121[3]; // [esp+330h] [ebp-1C8h] BYREF
  float v122[4]; // [esp+33Ch] [ebp-1BCh] BYREF
  int v123; // [esp+34Ch] [ebp-1ACh]
  float v124; // [esp+350h] [ebp-1A8h]
  int v125; // [esp+354h] [ebp-1A4h]
  float vector[3]; // [esp+358h] [ebp-1A0h] BYREF
  float v127[4]; // [esp+364h] [ebp-194h] BYREF
  float v128; // [esp+374h] [ebp-184h]
  float rhs[3]; // [esp+378h] [ebp-180h] BYREF
  float v130[8]; // [esp+384h] [ebp-174h] BYREF
  float v131[3]; // [esp+3A4h] [ebp-154h] BYREF
  float v132; // [esp+3B0h] [ebp-148h]
  float v133[4]; // [esp+3B4h] [ebp-144h] BYREF
  float v134[3]; // [esp+3C4h] [ebp-134h] BYREF
  float v135[6]; // [esp+3D0h] [ebp-128h] BYREF
  char v136[4]; // [esp+3E8h] [ebp-110h] BYREF
  float v137[3]; // [esp+3ECh] [ebp-10Ch] BYREF
  float v138[9]; // [esp+3F8h] [ebp-100h] BYREF
  float destination[3]; // [esp+41Ch] [ebp-DCh] BYREF
  float v140[12]; // [esp+428h] [ebp-D0h] BYREF
  float v141; // [esp+458h] [ebp-A0h]
  float v142; // [esp+45Ch] [ebp-9Ch]
  float v143[6]; // [esp+460h] [ebp-98h] BYREF
  float v144[4]; // [esp+478h] [ebp-80h] BYREF
  char v145[4]; // [esp+488h] [ebp-70h] BYREF
  float lhs[3]; // [esp+48Ch] [ebp-6Ch] BYREF
  int v147; // [esp+498h] [ebp-60h] BYREF
  float out_vector[3]; // [esp+49Ch] [ebp-5Ch] BYREF
  float v149; // [esp+4A8h] [ebp-50h]
  void *v150; // [esp+4ACh] [ebp-4Ch]
  float view_point[3]; // [esp+4B0h] [ebp-48h] BYREF
  int v152[2]; // [esp+4BCh] [ebp-3Ch] BYREF
  float v153; // [esp+4C4h] [ebp-34h]
  float v154[3]; // [esp+4C8h] [ebp-30h] BYREF
  float v155[3]; // [esp+4D4h] [ebp-24h] BYREF
  float v156[3]; // [esp+4E0h] [ebp-18h] BYREF
  float v157[3]; // [esp+4ECh] [ebp-Ch] BYREF

  if ( *((_BYTE *)glare + 652) )
  {
    v125 = *((_DWORD *)glare + 171);
    if ( *(_DWORD *)(v125 + 48) )
    {
      v150 = (void *)rf_object_resolve_handle(*((_DWORD *)glare + 12));
      if ( v150 && (first_dword = rf_receiver_get_first_dword(v150)) != 0 && !*(_BYTE *)(first_dword + 353) )
      {
        *((_DWORD *)glare + 173) &= ~0x10000000u;
        return glare;
      }
      else
      {
        rf_vector3_default_construct_noop(rhs);
        rf_matrix3_construct((char *)v143);
        rf_renderer_copy_current_view_transform(rhs, v143);
        rf_vector_subtract(glare + 15, out_vector, rhs);
        rf_vector_normalize(out_vector);
        v132 = rf_vector_distance(rhs, glare + 15);
        rf_vector3_default_construct_noop(vector);
        rf_matrix3_construct((char *)v134);
        rf_vector3_default_construct_noop(view_point);
        rf_vector3_default_construct_noop(v131);
        rf_render_state_pack(&v147, 2, 2, 3, 2, 1, 3);
        v144[3] = rf_vector_dot(v144, out_vector);
        if ( v132 <= 20.0 )
        {
          v2 = rf_vector_multiply_scalar(out_vector, scaled_result, v132);
          v3 = rf_vector_multiply_scalar(v2, v110, 0.5);
          rf_vector_add(rhs, source, v3);
          rf_solid_collision_query_construct_clear_face_hint(v136);
          rf_solid_collision_result_construct_noop((int)v120);
          v140[4] = 0.0;
          rf_identity_orientation_matrix(v138);
          rf_vector3_zero_return_destination(v137);
          v140[3] = 0.0;
          rf_vector_copy(destination, copy_result, source);
          v4 = rf_vector3_set_components_return_destination(v108, 0.0, -100.0, 0.0);
          rf_vector_copy(v140, v107, v4);
          rf_world_collision_sweep((char *)rf_world_solid, (int)v136, (int)v120, 1);
          if ( v120[0] > 0 )
          {
            if ( rf_face_flags_has_mask2((_DWORD *)(v123 + 40)) || rf_face_is_liquid((_DWORD *)(v123 + 40)) )
            {
              rf_plane_construct_from_normal_point(v133, v122, (int)v121);
              rf_plane_project_point_assuming_unit_normal(v133, (int)lhs, glare + 15);
              *(float *)&v152[1] = rf_vector_distance(glare + 15, lhs);
              rf_plane_project_point_assuming_unit_normal(v133, (int)v127, rhs);
              v127[3] = rf_vector_distance(rhs, v127);
              v141 = rf_vector_distance(lhs, v127);
              v149 = rf_vector_distance(rhs, v127);
              v124 = rf_vector_distance(glare + 15, lhs);
              v128 = v149 + v124;
              v117 = v149 * v141 / v128;
              v5 = rf_vector_subtract(lhs, v106, v127);
              rf_vector_copy(vector, v105, v5);
              rf_vector_normalize(vector);
              v6 = rf_vector3_set_components_return_destination(v104, -1000.0, -1000.0, -1000.0);
              if ( !rf_vector3_components_equal(glare + 176, v6) && ((_DWORD)glare[173] & 0x10000000) != 0 )
              {
                rf_vector_subtract(v121, v114, glare + 176);
                v115 = rf_vector3_length(v114);
                rf_vector_normalize(v114);
                rf_vector_scale(v113, 0.15000001, v114);
                v9 = rf_vector3_length(v113);
                if ( v115 < v9 )
                {
                  v10 = rf_vector_multiply_scalar(v114, v99, v115);
                  rf_vector_copy(v113, v98, v10);
                }
                v11 = rf_vector_add(glare + 176, v97, v113);
                rf_vector_copy(view_point, v96, v11);
                rf_vector_copy(glare + 176, v95, view_point);
              }
              else
              {
                v7 = rf_vector_multiply_scalar(vector, v103, v117);
                v8 = rf_vector_add(v127, sum_result, v7);
                rf_vector_copy(view_point, v101, v8);
                rf_vector_copy(glare + 176, v100, view_point);
              }
              v12 = rf_vector_subtract(view_point, v94, rhs);
              rf_vector_copy(out_vector, v93, v12);
              rf_vector_normalize(out_vector);
              v153 = rf_vector_dot(v144, out_vector);
              if ( v153 >= 0.0 )
              {
                if ( rhs[1] - 0.75 >= view_point[1] + 0.1000000014901161 )
                {
                  if ( rf_glare_line_of_sight_with_caches(glare, view_point) )
                  {
                    v142 = (20.0 - v132) / 20.0;
                    *(float *)v152 = v142 * 255.0;
                    *(float *)&v118 = v142 * 1.25 + 0.75;
                    *(float *)v152 = (v153 * 0.4000000059604645 + 0.6000000238418579) * *(float *)v152;
                    rf_float_clamp_in_place((float *)v152, 0.0, 255.0);
                    rf_float_clamp_in_place((float *)&v118, 0.75, 2.0);
                    if ( *(float *)v152 >= 5.0 )
                    {
                      rf_orientation_matrix_from_normalized_direction(v134, v122);
                      rf_vector_construct_no_unwind((char *)v154, 0xCu, 4, rf_vector3_default_construct_noop);
                      rf_vector_construct_no_unwind((char *)v130, 8u, 4, rf_vector3_default_construct_noop);
                      v44 = v118;
                      v13 = rf_vector_multiply_scalar(v134, v89, 0.5);
                      v45 = rf_vector_multiply_scalar(v13, v88, *(float *)&v44);
                      scalar = v118;
                      v14 = rf_vector_multiply_scalar(v135, v92, 0.5);
                      v15 = rf_vector_multiply_scalar(v14, v91, *(float *)&scalar);
                      v16 = rf_vector_add(view_point, v90, v15);
                      v17 = rf_vector_add(v16, v87, v45);
                      rf_vector_copy(v154, v86, v17);
                      v130[0] = 0.0;
                      v130[1] = 0.0;
                      v46 = v118;
                      v18 = rf_vector_multiply_scalar(v134, v82, 0.5);
                      v47 = rf_vector_multiply_scalar(v18, v81, *(float *)&v46);
                      scalara = v118;
                      v19 = rf_vector_multiply_scalar(v135, v85, 0.5);
                      v20 = rf_vector_multiply_scalar(v19, v84, *(float *)&scalara);
                      v21 = rf_vector_subtract(view_point, v83, v20);
                      v22 = rf_vector_add(v21, v80, v47);
                      rf_vector_copy(v155, v79, v22);
                      v130[2] = 0.0;
                      v130[3] = 1.0;
                      v48 = v118;
                      v23 = rf_vector_multiply_scalar(v134, v75, 0.5);
                      v49 = rf_vector_multiply_scalar(v23, v74, *(float *)&v48);
                      scalarb = v118;
                      v24 = rf_vector_multiply_scalar(v135, v78, 0.5);
                      v25 = rf_vector_multiply_scalar(v24, v77, *(float *)&scalarb);
                      v26 = rf_vector_subtract(view_point, v76, v25);
                      v27 = rf_vector_subtract(v26, v73, v49);
                      rf_vector_copy(v156, v72, v27);
                      v130[4] = 1.0;
                      v130[5] = 1.0;
                      v50 = v118;
                      v28 = rf_vector_multiply_scalar(v134, v68, 0.5);
                      v51 = rf_vector_multiply_scalar(v28, v67, *(float *)&v50);
                      scalarc = v118;
                      v29 = rf_vector_multiply_scalar(v135, v71, 0.5);
                      v30 = rf_vector_multiply_scalar(v29, v70, *(float *)&scalarc);
                      v31 = rf_vector_add(view_point, v69, v30);
                      v32 = rf_vector_subtract(v31, v66, v51);
                      rf_vector_copy(v157, v65, v32);
                      v130[6] = 1.0;
                      v130[7] = 0.0;
                      v33 = rf_vector3_set_components_return_destination(v64, 0.0, 1.0, 0.0);
                      if ( rf_vector3_components_not_equal(v122, v33) )
                      {
                        rf_plane_construct_from_normal_point(v112, v122, (int)v121);
                        v34 = (const float *)rf_plane_project_point_assuming_unit_normal(v112, (int)v63, v154);
                        rf_vector_copy(v154, v62, v34);
                        v35 = (const float *)rf_plane_project_point_assuming_unit_normal(v112, (int)v61, v155);
                        rf_vector_copy(v155, v60, v35);
                        v36 = (const float *)rf_plane_project_point_assuming_unit_normal(v112, (int)v59, v156);
                        rf_vector_copy(v156, v58, v36);
                        v37 = (const float *)rf_plane_project_point_assuming_unit_normal(v112, (int)v57, v157);
                        rf_vector_copy(v157, v56, v37);
                        v38 = rf_vector_multiply_scalar(v122, v55, 0.1);
                        rf_vector_copy(v131, v54, v38);
                      }
                      else
                      {
                        v39 = rf_vector3_set_components_return_destination(v53, 0.0, 0.1, 0.0);
                        rf_vector_copy(v131, v52, v39);
                      }
                      rf_vector_accumulate(v154, v131);
                      rf_vector_accumulate(v155, v131);
                      rf_vector_accumulate(v156, v131);
                      rf_vector_accumulate(v157, v131);
                      v145[0] = -1;
                      v145[1] = -1;
                      v145[2] = -1;
                      v145[3] = (int)*(float *)v152;
                      rf_renderer_submit_textured_world_polygon_color4_dispatch(
                        *(_DWORD *)(v125 + 48),
                        4,
                        (int)v154,
                        (int)v130,
                        v147,
                        v145);
                      *((_DWORD *)glare + 173) &= 0x10000000u;
                      return glare;
                    }
                    else
                    {
                      *((_DWORD *)glare + 173) &= ~0x10000000u;
                      return glare;
                    }
                  }
                  else
                  {
                    result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
                    *((_DWORD *)glare + 173) = result;
                  }
                }
                else
                {
                  result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
                  *((_DWORD *)glare + 173) = result;
                }
              }
              else
              {
                result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
                *((_DWORD *)glare + 173) = result;
              }
            }
            else
            {
              result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
              *((_DWORD *)glare + 173) = result;
            }
          }
          else
          {
            *((_DWORD *)glare + 173) &= ~0x10000000u;
            return glare;
          }
        }
        else
        {
          *((_DWORD *)glare + 173) &= ~0x10000000u;
          return glare;
        }
      }
    }
    else
    {
      result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
      *((_DWORD *)glare + 173) = result;
    }
  }
  else
  {
    result = (float *)((_DWORD)glare[173] & 0xEFFFFFFF);
    *((_DWORD *)glare + 173) = result;
  }
  return result;
}

