// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00480230 rf_decal_find_room_at_center_or_box_corners
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl(center3f,matrix3 rows,dimensions3f), returns first nonnull room pointer orNULL. Copies center to local scratch and queries
// world_resolve_cached_room(world,NULL,zeroVector,point,0). With NULL prior-room delegate performs endpoint room lookup, so start zeroVector does not imply movement from origin or
// ray intersection. Center hit returns immediately.
// If center misses, first corner is center -row0*(dimX/2) +row1*(dimY/2) -row2*(dimZ/2), with half-products stored binary32 and vector operations materialized individually. Queries
// that corner, then cumulatively adds +row0*X,-row1*Y,-row0*X,+row2*Z,+row1*Y,+row0*X,-row1*Y, querying after EVERY step. Thus center then eight corners in sign
// order(-,+,-),(+,+,-),(+,-,-),(-,-,-),(-,-,+),(-,+,+),(+,+,+),(+,-,+). Each step starts from previous rounded corner, not a freshly reconstructed center expression.
// Returns first room in that order; does not require all points in same room or perform full box/world-overlap test. Does not change input center/matrix/dimensions, normalize basis,
// clamp dimensions, checkNULL inputs/world or project a decal itself. Room-query delegates may update their own scratch.
void *__cdecl rf_decal_find_room_at_center_or_box_corners(float *a1, float *a2, float *a3)
{
  float *v3; // eax
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
  float *v34; // eax
  float *v35; // eax
  float *v36; // [esp+Ch] [ebp-220h]
  float *v37; // [esp+14h] [ebp-218h]
  float v38; // [esp+18h] [ebp-214h]
  float v39; // [esp+1Ch] [ebp-210h]
  float v40; // [esp+20h] [ebp-20Ch]
  float v41[3]; // [esp+24h] [ebp-208h] BYREF
  float v42[3]; // [esp+30h] [ebp-1FCh] BYREF
  float v43[3]; // [esp+3Ch] [ebp-1F0h] BYREF
  int v44[3]; // [esp+48h] [ebp-1E4h] BYREF
  float v45[3]; // [esp+54h] [ebp-1D8h] BYREF
  float v46[3]; // [esp+60h] [ebp-1CCh] BYREF
  float v47[3]; // [esp+6Ch] [ebp-1C0h] BYREF
  float v48[3]; // [esp+78h] [ebp-1B4h] BYREF
  int v49[3]; // [esp+84h] [ebp-1A8h] BYREF
  float v50[3]; // [esp+90h] [ebp-19Ch] BYREF
  float v51[3]; // [esp+9Ch] [ebp-190h] BYREF
  float v52[3]; // [esp+A8h] [ebp-184h] BYREF
  int v53[3]; // [esp+B4h] [ebp-178h] BYREF
  float v54[3]; // [esp+C0h] [ebp-16Ch] BYREF
  float v55[3]; // [esp+CCh] [ebp-160h] BYREF
  float v56[3]; // [esp+D8h] [ebp-154h] BYREF
  int v57[3]; // [esp+E4h] [ebp-148h] BYREF
  float v58[3]; // [esp+F0h] [ebp-13Ch] BYREF
  float v59[3]; // [esp+FCh] [ebp-130h] BYREF
  float v60[3]; // [esp+108h] [ebp-124h] BYREF
  int v61[3]; // [esp+114h] [ebp-118h] BYREF
  float v62[3]; // [esp+120h] [ebp-10Ch] BYREF
  float v63[3]; // [esp+12Ch] [ebp-100h] BYREF
  float v64[3]; // [esp+138h] [ebp-F4h] BYREF
  float v65[3]; // [esp+144h] [ebp-E8h] BYREF
  int v66[3]; // [esp+150h] [ebp-DCh] BYREF
  float v67[3]; // [esp+15Ch] [ebp-D0h] BYREF
  float v68[3]; // [esp+168h] [ebp-C4h] BYREF
  float v69[3]; // [esp+174h] [ebp-B8h] BYREF
  float v70[3]; // [esp+180h] [ebp-ACh] BYREF
  int v71[3]; // [esp+18Ch] [ebp-A0h] BYREF
  float v72[3]; // [esp+198h] [ebp-94h] BYREF
  float copy_result[3]; // [esp+1A4h] [ebp-88h] BYREF
  float v74[3]; // [esp+1B0h] [ebp-7Ch] BYREF
  int v75[3]; // [esp+1BCh] [ebp-70h] BYREF
  float v76[3]; // [esp+1C8h] [ebp-64h] BYREF
  int v77[3]; // [esp+1D4h] [ebp-58h] BYREF
  float v78[3]; // [esp+1E0h] [ebp-4Ch] BYREF
  float sum_result[3]; // [esp+1ECh] [ebp-40h] BYREF
  int v80[3]; // [esp+1F8h] [ebp-34h] BYREF
  float v81[3]; // [esp+204h] [ebp-28h] BYREF
  float v82[3]; // [esp+210h] [ebp-1Ch] BYREF
  float destination[3]; // [esp+21Ch] [ebp-10h] BYREF
  void *v84; // [esp+228h] [ebp-4h]

  v84 = nullptr;
  rf_vector3_copy_return_destination(destination, a1);
  v3 = rf_vector3_set_components_return_destination(v82, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v3, destination, 0);
  if ( v84 )
    return v84;
  v40 = a3[1] * 0.5;
  v37 = rf_vector_scale((float *)v75, v40, a2 + 3);
  v5 = rf_vector_negate(a2, v78);
  v39 = *a3 * 0.5;
  v36 = rf_vector_scale((float *)v77, v39, v5);
  v6 = rf_vector_negate(a2 + 6, v81);
  v38 = a3[2] * 0.5;
  v7 = rf_vector_scale((float *)v80, v38, v6);
  v8 = rf_vector_add(destination, sum_result, v7);
  v9 = rf_vector_add(v8, v76, v36);
  v10 = rf_vector_add(v9, v74, v37);
  rf_vector_copy(destination, copy_result, v10);
  v11 = rf_vector3_set_components_return_destination(v72, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v11, destination, 0);
  if ( v84 )
    return v84;
  v12 = rf_vector_scale((float *)v71, *a3, a2);
  v13 = rf_vector_add(destination, v70, v12);
  rf_vector_copy(destination, v69, v13);
  v14 = rf_vector3_set_components_return_destination(v68, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v14, destination, 0);
  if ( v84 )
    return v84;
  v15 = rf_vector_negate(a2 + 3, v67);
  v16 = rf_vector_scale((float *)v66, a3[1], v15);
  v17 = rf_vector_add(destination, v65, v16);
  rf_vector_copy(destination, v64, v17);
  v18 = rf_vector3_set_components_return_destination(v63, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v18, destination, 0);
  if ( v84 )
    return v84;
  v19 = rf_vector_negate(a2, v62);
  v20 = rf_vector_scale((float *)v61, *a3, v19);
  v21 = rf_vector_add(destination, v60, v20);
  rf_vector_copy(destination, v59, v21);
  v22 = rf_vector3_set_components_return_destination(v58, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v22, destination, 0);
  if ( v84 )
    return v84;
  v23 = rf_vector_scale((float *)v57, a3[2], a2 + 6);
  v24 = rf_vector_add(destination, v56, v23);
  rf_vector_copy(destination, v55, v24);
  v25 = rf_vector3_set_components_return_destination(v54, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v25, destination, 0);
  if ( v84 )
    return v84;
  v26 = rf_vector_scale((float *)v53, a3[1], a2 + 3);
  v27 = rf_vector_add(destination, v52, v26);
  rf_vector_copy(destination, v51, v27);
  v28 = rf_vector3_set_components_return_destination(v50, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v28, destination, 0);
  if ( v84 )
    return v84;
  v29 = rf_vector_scale((float *)v49, *a3, a2);
  v30 = rf_vector_add(destination, v48, v29);
  rf_vector_copy(destination, v47, v30);
  v31 = rf_vector3_set_components_return_destination(v46, 0.0, 0.0, 0.0);
  v84 = rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v31, destination, 0);
  if ( v84 )
    return v84;
  v32 = rf_vector_negate(a2 + 3, v45);
  v33 = rf_vector_scale((float *)v44, a3[1], v32);
  v34 = rf_vector_add(destination, v43, v33);
  rf_vector_copy(destination, v42, v34);
  v35 = rf_vector3_set_components_return_destination(v41, 0.0, 0.0, 0.0);
  return rf_world_resolve_cached_room((void *)rf_world_solid, nullptr, v35, destination, 0);
}

