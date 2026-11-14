// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005268F0 rf_light_assign_receiver_coverage
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl light,receiverSolid,lowBYTE mode. Type1 returns immediately without coverage; type2 point predicate526100, type3 spot5261B0, type4 tube526250. Other types leave predicateNULL then continue, so can indirect-callNULL; no validation. Spot rebuilds plane data IN light: choose original origin12/direction36 or alternate92/116 by DWORD18CD388; end=origin+direction*range60. Build RF basis55C050 (does not generally normalize supplied forward), scale row1 androw0 by raw light140; cornersC0=end+row1*r+row0*r,C1=end+row1*r-row0*r,C2=end-row1*r-row0*r,C3=end-row1*r+row0*r. Side planes180/196/212/228 use(C1,C0,origin),(C2,C1,origin),(origin,C3,C2),(C0,C3,origin). Near148 from -direction/origin,far164
// from direction/end. Compute min support selectors244..264; max selectors are discarded into local scratch. No circular cone refinement. If signed receiver array156 count>0, test each room bounds8/20; accepted room pushes root60 then accepted child-room108 roots60. Room children only examined when parent-room predicate passed. LIFO node stack begins EBP-0x1038, no capacity/rootNULL/duplicate checks. Pop,test node bounds0/12;on pass push child32 then36 (36 first), process node face list24. Otherwise flat mode first tests solid bounds72/84, then face list112. In EITHER path skip faces whose signed portalWORD52>0. If globalBYTE rf_fixed_pool_heap_spill_enabled nonzero, require signed lightmapWORD54>=0, fetch descriptor from solid array192, test requested dirtybit:mode0 skips if bit1 alreadyset, ANY nonzero mode skips ifbit2 alreadyset. Only then test face bounds16/28; success writes
// flagsBYTE8 EXACT1 then OR2 if mode nonzero ->EXACT3, clearing other bits. Shared descriptors may skip later faces after first hit. With globalBYTEzero, after parent/node bound admission OR face metadata40 with0x40000 for EVERY nonportal face, with NO per-face bounds test or lightmap requirement. No per-light identity encoded, no active-world-list or32-bit face light-mask update, no clearing of misses, geometry/tree mutation or bounds rebuild. Return int is incidental traversal/helper result.
int __cdecl rf_light_assign_receiver_coverage(int a1, _DWORD *a2, char a3)
{
  int result; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float *v17; // eax
  float *v18; // eax
  int first_dword; // eax
  float *scalar; // [esp+0h] [ebp-11F4h]
  char v21[12]; // [esp+8h] [ebp-11ECh] BYREF
  float v22[3]; // [esp+14h] [ebp-11E0h] BYREF
  float v23[3]; // [esp+20h] [ebp-11D4h] BYREF
  float v24[3]; // [esp+2Ch] [ebp-11C8h] BYREF
  float v25[3]; // [esp+38h] [ebp-11BCh] BYREF
  float v26[3]; // [esp+44h] [ebp-11B0h] BYREF
  float v27[3]; // [esp+50h] [ebp-11A4h] BYREF
  float v28[3]; // [esp+5Ch] [ebp-1198h] BYREF
  float out_vector[3]; // [esp+68h] [ebp-118Ch] BYREF
  float v30[3]; // [esp+74h] [ebp-1180h] BYREF
  float v31[3]; // [esp+80h] [ebp-1174h] BYREF
  float v32[3]; // [esp+8Ch] [ebp-1168h] BYREF
  float v33[3]; // [esp+98h] [ebp-115Ch] BYREF
  float v34[3]; // [esp+A4h] [ebp-1150h] BYREF
  float v35[3]; // [esp+B0h] [ebp-1144h] BYREF
  float v36[3]; // [esp+BCh] [ebp-1138h] BYREF
  float v37[3]; // [esp+C8h] [ebp-112Ch] BYREF
  float v38[3]; // [esp+D4h] [ebp-1120h] BYREF
  float v39[3]; // [esp+E0h] [ebp-1114h] BYREF
  float v40[3]; // [esp+ECh] [ebp-1108h] BYREF
  float copy_result[3]; // [esp+F8h] [ebp-10FCh] BYREF
  float sum_result[3]; // [esp+104h] [ebp-10F0h] BYREF
  float scaled_result[3]; // [esp+110h] [ebp-10E4h] BYREF
  int v44; // [esp+11Ch] [ebp-10D8h]
  int j; // [esp+120h] [ebp-10D4h]
  int v46; // [esp+124h] [ebp-10D0h]
  int n; // [esp+128h] [ebp-10CCh]
  float v48; // [esp+12Ch] [ebp-10C8h]
  int v49; // [esp+130h] [ebp-10C4h]
  int m; // [esp+134h] [ebp-10C0h]
  int v51; // [esp+138h] [ebp-10BCh]
  int i; // [esp+13Ch] [ebp-10B8h]
  float v53[3]; // [esp+140h] [ebp-10B4h] BYREF
  float vector[6]; // [esp+14Ch] [ebp-10A8h] BYREF
  float *v55; // [esp+164h] [ebp-1090h]
  void *v56; // [esp+168h] [ebp-108Ch]
  float rhs[9]; // [esp+16Ch] [ebp-1088h] BYREF
  int v58; // [esp+190h] [ebp-1064h]
  float v59[3]; // [esp+194h] [ebp-1060h] BYREF
  float v60[3]; // [esp+1A0h] [ebp-1054h] BYREF
  float *v61; // [esp+1ACh] [ebp-1048h]
  float destination[1028]; // [esp+1B0h] [ebp-1044h] BYREF
  float v63[3]; // [esp+11C0h] [ebp-34h] BYREF
  int k; // [esp+11CCh] [ebp-28h]
  float v65[3]; // [esp+11D0h] [ebp-24h] BYREF
  char v66[12]; // [esp+11DCh] [ebp-18h] BYREF
  float lhs[3]; // [esp+11E8h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v63);
  rf_vector3_default_construct_noop(v59);
  rf_vector3_default_construct_noop(v65);
  rf_vector3_default_construct_noop(v60);
  rf_matrix3_construct((char *)v53);
  rf_vector3_default_construct_noop(destination);
  rf_vector3_default_construct_noop(rhs);
  rf_vector3_default_construct_noop(v66);
  rf_vector3_default_construct_noop(lhs);
  v56 = nullptr;
  result = *(_DWORD *)(a1 + 8) - 1;
  switch ( *(_DWORD *)(a1 + 8) )
  {
    case 1:
      return result;
    case 2:
      v56 = rf_point_light_intersects_aabb;
      goto LABEL_11;
    case 3:
      v56 = rf_spot_light_intersects_aabb;
      if ( unk_18CD388 )
      {
        v61 = (float *)(a1 + 92);
        v55 = (float *)(a1 + 116);
        v6 = rf_vector_multiply_scalar((const float *)(a1 + 116), v40, *(float *)(a1 + 60));
        v7 = rf_vector_add((const float *)(a1 + 92), v39, v6);
        rf_vector_copy(lhs, v38, v7);
      }
      else
      {
        v61 = (float *)(a1 + 12);
        v55 = (float *)(a1 + 36);
        v4 = rf_vector_multiply_scalar((const float *)(a1 + 36), scaled_result, *(float *)(a1 + 60));
        v5 = rf_vector_add((const float *)(a1 + 12), sum_result, v4);
        rf_vector_copy(lhs, copy_result, v5);
      }
      rf_orientation_matrix_from_direction(v53, (int)v55);
      v8 = rf_vector_multiply_scalar(vector, v37, *(float *)(a1 + 140));
      rf_vector_copy(destination, v36, v8);
      v9 = rf_vector_multiply_scalar(v53, v35, *(float *)(a1 + 140));
      rf_vector_copy(rhs, v34, v9);
      v10 = rf_vector_add(lhs, v33, destination);
      v11 = rf_vector_add(v10, v32, rhs);
      rf_vector_copy(v63, v31, v11);
      v12 = rf_vector_add(lhs, v30, destination);
      v13 = rf_vector_subtract(v12, out_vector, rhs);
      rf_vector_copy(v59, v28, v13);
      v14 = rf_vector_subtract(lhs, v27, destination);
      v15 = rf_vector_subtract(v14, v26, rhs);
      rf_vector_copy(v65, v25, v15);
      v16 = rf_vector_subtract(lhs, v24, destination);
      v17 = rf_vector_add(v16, v23, rhs);
      rf_vector_copy(v60, v22, v17);
      rf_plane_set_from_three_world_points((float *)(a1 + 180), v59, (int)v63, (int)v61);
      rf_plane_set_from_three_world_points((float *)(a1 + 196), v65, (int)v59, (int)v61);
      rf_plane_set_from_three_world_points((float *)(a1 + 212), v61, (int)v60, (int)v65);
      rf_plane_set_from_three_world_points((float *)(a1 + 228), v63, (int)v60, (int)v61);
      scalar = v61;
      v18 = rf_vector_negate(v55, (float *)v21);
      rf_plane4_construct_normal_point((float *)(a1 + 148), v18, scalar);
      rf_plane4_construct_normal_point((float *)(a1 + 164), v55, lhs);
      for ( i = 0; i < 6; ++i )
        rf_plane_select_aabb_support_corners((float *)(a1 + 16 * i + 148), (_DWORD *)(a1 + 4 * i + 244), &rhs[i + 3]);
      goto LABEL_11;
    case 4:
      v56 = rf_tube_light_intersects_aabb;
      goto LABEL_11;
    default:
LABEL_11:
      v58 = 0;
      if ( rf_receiver_get_first_dword(a2 + 39) <= 0 )
      {
        result = ((int (__cdecl *)(int, _DWORD *, _DWORD *))v56)(a1, a2 + 18, a2 + 21);
        if ( (_BYTE)result )
        {
          result = rf_receiver_get_first_dword(a2 + 28);
          for ( j = result; j; j = result )
          {
            if ( !rf_face_is_portal((__int16 *)(j + 40)) )
            {
              if ( rf_fixed_pool_heap_spill_enabled[0] )
              {
                if ( *(__int16 *)(j + 54) > -1 )
                {
                  if ( (v44 = *(_DWORD *)sub_552200(a2 + 48, *(__int16 *)(j + 54)), !a3)
                    && (*(_BYTE *)(v44 + 8) & 1) == 0
                    || a3 && (*(_BYTE *)(v44 + 8) & 2) == 0 )
                  {
                    if ( ((unsigned __int8 (__cdecl *)(int, int, int))v56)(a1, j + 16, j + 28) )
                    {
                      *(_BYTE *)(v44 + 8) = 1;
                      if ( a3 )
                        *(_BYTE *)(v44 + 8) |= 2u;
                    }
                  }
                }
              }
              else
              {
                *(_DWORD *)(j + 40) |= 0x40000u;
              }
            }
            result = rf_solid_face_next_link(j);
          }
        }
      }
      else
      {
        for ( k = 0; ; ++k )
        {
          result = rf_receiver_get_first_dword(a2 + 39);
          if ( k >= result )
            break;
          v51 = *(_DWORD *)sub_552200(a2 + 39, k);
          if ( ((unsigned __int8 (__cdecl *)(int, int, int))v56)(a1, v51 + 8, v51 + 20) )
          {
            destination[v58++ + 3] = *(float *)(v51 + 60);
            for ( m = 0; ; ++m )
            {
              first_dword = rf_receiver_get_first_dword((void *)(v51 + 108));
              if ( m >= first_dword )
                break;
              v49 = *(_DWORD *)sub_552200((_DWORD *)(v51 + 108), m);
              if ( ((unsigned __int8 (__cdecl *)(int, int, int))v56)(a1, v49 + 8, v49 + 20) )
                destination[v58++ + 3] = *(float *)(v49 + 60);
            }
          }
        }
        while ( v58 > 0 )
        {
          v48 = destination[--v58 + 3];
          result = ((int (__cdecl *)(int, _DWORD, int))v56)(a1, LODWORD(v48), LODWORD(v48) + 12);
          if ( (_BYTE)result )
          {
            if ( *(_DWORD *)(LODWORD(v48) + 32) )
              destination[v58++ + 3] = *(float *)(LODWORD(v48) + 32);
            if ( *(_DWORD *)(LODWORD(v48) + 36) )
              destination[v58++ + 3] = *(float *)(LODWORD(v48) + 36);
            result = rf_receiver_get_first_dword((void *)(LODWORD(v48) + 24));
            for ( n = result; n; n = result )
            {
              if ( !rf_face_is_portal((__int16 *)(n + 40)) )
              {
                if ( rf_fixed_pool_heap_spill_enabled[0] )
                {
                  if ( *(__int16 *)(n + 54) > -1 )
                  {
                    if ( (v46 = *(_DWORD *)sub_552200(a2 + 48, *(__int16 *)(n + 54)), !a3)
                      && (*(_BYTE *)(v46 + 8) & 1) == 0
                      || a3 && (*(_BYTE *)(v46 + 8) & 2) == 0 )
                    {
                      if ( ((unsigned __int8 (__cdecl *)(int, int, int))v56)(a1, n + 16, n + 28) )
                      {
                        *(_BYTE *)(v46 + 8) = 1;
                        if ( a3 )
                          *(_BYTE *)(v46 + 8) |= 2u;
                      }
                    }
                  }
                }
                else
                {
                  *(_DWORD *)(n + 40) |= 0x40000u;
                }
              }
              result = rf_face_next_spatial_node_link(n);
            }
          }
        }
      }
      return result;
  }
}

