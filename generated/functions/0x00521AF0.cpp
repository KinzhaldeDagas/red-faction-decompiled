// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00521AF0 rf_world_decal_create_volume_and_project
// UNREALRED VERIFIED [decal-projection-20261028]: Arguments: solid/context,primary owner,secondary owner,position vec3,matrix3,dimensions vec3,bitmap,alpha byte,flags,extra dword,scalar. At active count EXACTLY128 removes first record lacking flags1/0x400; subtracts fading count if removed had0x40000000. At active-minus-fading>=96 marks first nonflag1/nonfading record to fade. For primary/secondary owner inline lists+156 (or context+240 when no primary), at count>=48 evicts first nonflag1/non0x400 record and at count>=40 marks first nonflag1/nonfading record. Eviction stops after one candidate; limits are not validated invariants. Incoming flag0x100 enforces category count<16 by repeated eviction of same-category non0x400 records, starts one fade when count>=14, then increments counter. Incoming flag0x200 similarly uses limits32/30. Failure to find category victim returnsnull. Category
// increments occur BEFORE pool acquire; no rollback if acquisition or later category admission fails. Acquires236-byte record or returnsnull; inserts into owner inline arrays but ignores append failure. Copies transform/dimensions, bitmap+60,owners+64/+68,context+72,alpha+76,flags+80,extra+84,scalar+88; clears optional alternate context+232 and polygon head/count+212/+216. Computes broad AABB via0x522950; unless flag2, gathers candidates and may replace orientation via0x522A00. Constructs six plane equations+92..+187 from +/-half dimensions along final matrix axes. Flag0x08000000 calls liquid-face dispatcher0x523000; otherwise general dispatcher0x523C40. Flag8 then computes per-polygon layering against up to17 same-face polygons, sets order=max(existing orders)+1 and removes lowest-order nonflag1 decal if nonflag1 overlap count>=16. Returns allocated record even when no polygons projected.
// No general dimension/bitmap validity checks; source flags and raw offsets preserved without assigning unsupported editor labels.
float *__cdecl rf_world_decal_create_volume_and_project(
        int a1,
        int a2,
        int a3,
        float *lhs,
        float *a5,
        float *source,
        int a7,
        char a8,
        int a9,
        int a10,
        float a11)
{
  _DWORD **v11; // eax
  int v12; // eax
  _DWORD **v13; // eax
  int v14; // eax
  _DWORD **v15; // eax
  int v16; // eax
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
  float *scalar; // [esp+0h] [ebp-204h]
  float *scalara; // [esp+0h] [ebp-204h]
  float *scalarb; // [esp+0h] [ebp-204h]
  _DWORD *v39; // [esp+4h] [ebp-200h]
  float v40; // [esp+8h] [ebp-1FCh]
  float v41; // [esp+Ch] [ebp-1F8h]
  float v42; // [esp+10h] [ebp-1F4h]
  float v43; // [esp+14h] [ebp-1F0h]
  float v44; // [esp+18h] [ebp-1ECh]
  float v45; // [esp+1Ch] [ebp-1E8h]
  int v46; // [esp+20h] [ebp-1E4h]
  _DWORD *v47; // [esp+24h] [ebp-1E0h]
  int v48; // [esp+28h] [ebp-1DCh]
  _DWORD *v49; // [esp+2Ch] [ebp-1D8h]
  int v50; // [esp+3Ch] [ebp-1C8h]
  _DWORD *v51; // [esp+40h] [ebp-1C4h]
  char v52[12]; // [esp+44h] [ebp-1C0h] BYREF
  float v53[3]; // [esp+50h] [ebp-1B4h] BYREF
  float v54[3]; // [esp+5Ch] [ebp-1A8h] BYREF
  _BYTE v55[16]; // [esp+68h] [ebp-19Ch] BYREF
  float v56[3]; // [esp+78h] [ebp-18Ch] BYREF
  float v57[3]; // [esp+84h] [ebp-180h] BYREF
  _BYTE v58[16]; // [esp+90h] [ebp-174h] BYREF
  char v59[12]; // [esp+A0h] [ebp-164h] BYREF
  float v60[3]; // [esp+ACh] [ebp-158h] BYREF
  float v61[3]; // [esp+B8h] [ebp-14Ch] BYREF
  _BYTE v62[16]; // [esp+C4h] [ebp-140h] BYREF
  float v63[3]; // [esp+D4h] [ebp-130h] BYREF
  float v64[3]; // [esp+E0h] [ebp-124h] BYREF
  _BYTE v65[16]; // [esp+ECh] [ebp-118h] BYREF
  char v66[12]; // [esp+FCh] [ebp-108h] BYREF
  float out_vector[3]; // [esp+108h] [ebp-FCh] BYREF
  float v68[3]; // [esp+114h] [ebp-F0h] BYREF
  _BYTE v69[16]; // [esp+120h] [ebp-E4h] BYREF
  float sum_result[3]; // [esp+130h] [ebp-D4h] BYREF
  float scaled_result[3]; // [esp+13Ch] [ebp-C8h] BYREF
  _BYTE v72[16]; // [esp+148h] [ebp-BCh] BYREF
  float v73[3]; // [esp+158h] [ebp-ACh] BYREF
  float copy_result[3]; // [esp+164h] [ebp-A0h] BYREF
  int jj; // [esp+170h] [ebp-94h]
  int v76; // [esp+174h] [ebp-90h]
  int v77; // [esp+178h] [ebp-8Ch]
  int v78; // [esp+17Ch] [ebp-88h]
  int v79; // [esp+180h] [ebp-84h] BYREF
  int v80; // [esp+184h] [ebp-80h]
  _DWORD *ii; // [esp+188h] [ebp-7Ch]
  _DWORD v82[18]; // [esp+18Ch] [ebp-78h] BYREF
  int n; // [esp+1D4h] [ebp-30h]
  _DWORD *v84; // [esp+1D8h] [ebp-2Ch]
  _DWORD *v85; // [esp+1DCh] [ebp-28h]
  char v86; // [esp+1E3h] [ebp-21h]
  int m; // [esp+1E4h] [ebp-20h]
  _DWORD *v88; // [esp+1E8h] [ebp-1Ch]
  _DWORD *v89; // [esp+1ECh] [ebp-18h]
  char v90; // [esp+1F3h] [ebp-11h]
  int j; // [esp+1F4h] [ebp-10h]
  _DWORD *i; // [esp+1F8h] [ebp-Ch]
  float *destination; // [esp+1FCh] [ebp-8h]
  int k; // [esp+200h] [ebp-4h]

  if ( unk_A70624 == 128 )
  {
    for ( i = (_DWORD *)unk_A7051C; i; i = v51 )
    {
      if ( (i[20] & 1) == 0 && (i[20] & 0x400) == 0 )
      {
        if ( (i[20] & 0x40000000) != 0 )
          --unk_A70628;
        rf_world_decal_remove_spatial_links_and_recycle(i);
        break;
      }
      if ( i[56] == unk_A7051C )
        v51 = nullptr;
      else
        v51 = (_DWORD *)i[56];
    }
  }
  if ( unk_A70624 - unk_A70628 >= 96 )
  {
    for ( j = unk_A7051C; j; j = v50 )
    {
      if ( (*(_DWORD *)(j + 80) & 1) == 0 && (*(_DWORD *)(j + 80) & 0x40000000) == 0 )
      {
        *(_DWORD *)(j + 80) |= 0x40000000u;
        break;
      }
      if ( *(_DWORD *)(j + 224) == unk_A7051C )
        v50 = 0;
      else
        v50 = *(_DWORD *)(j + 224);
    }
  }
  if ( a2 )
  {
    if ( rf_receiver_get_first_dword((void *)(a2 + 156)) >= 48 )
    {
      for ( k = 0; k < rf_receiver_get_first_dword((void *)(a2 + 156)); ++k )
      {
        if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k) + 80) & 1) == 0
          && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k) + 80)
            & 0x400) == 0 )
        {
          v13 = (_DWORD **)rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k);
          rf_world_decal_remove_spatial_links_and_recycle(*v13);
          break;
        }
      }
    }
    if ( rf_receiver_get_first_dword((void *)(a2 + 156)) >= 40 )
    {
      for ( k = 0; k < rf_receiver_get_first_dword((void *)(a2 + 156)); ++k )
      {
        if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k) + 80) & 1) == 0
          && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k) + 80)
            & 0x40000000) == 0 )
        {
          v14 = rf_inline_dword_array4_element_address_unchecked((void *)(a2 + 156), k);
          *(_DWORD *)(*(_DWORD *)v14 + 80) |= 0x40000000u;
          break;
        }
      }
    }
    if ( a3 )
    {
      if ( rf_receiver_get_first_dword((void *)(a3 + 156)) >= 48 )
      {
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(a3 + 156)); ++k )
        {
          if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k) + 80) & 1) == 0
            && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k) + 80)
              & 0x400) == 0 )
          {
            v15 = (_DWORD **)rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k);
            rf_world_decal_remove_spatial_links_and_recycle(*v15);
            break;
          }
        }
      }
      if ( rf_receiver_get_first_dword((void *)(a3 + 156)) >= 40 )
      {
        for ( k = 0; k < rf_receiver_get_first_dword((void *)(a3 + 156)); ++k )
        {
          if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k) + 80) & 1) == 0
            && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k) + 80)
              & 0x40000000) == 0 )
          {
            v16 = rf_inline_dword_array4_element_address_unchecked((void *)(a3 + 156), k);
            *(_DWORD *)(*(_DWORD *)v16 + 80) |= 0x40000000u;
            break;
          }
        }
      }
    }
  }
  else
  {
    if ( rf_receiver_get_first_dword((void *)(a1 + 240)) >= 48 )
    {
      for ( k = 0; k < rf_receiver_get_first_dword((void *)(a1 + 240)); ++k )
      {
        if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k) + 80) & 1) == 0
          && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k) + 80)
            & 0x400) == 0 )
        {
          v11 = (_DWORD **)rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k);
          rf_world_decal_remove_spatial_links_and_recycle(*v11);
          break;
        }
      }
    }
    if ( rf_receiver_get_first_dword((void *)(a1 + 240)) >= 40 )
    {
      for ( k = 0; k < rf_receiver_get_first_dword((void *)(a1 + 240)); ++k )
      {
        if ( (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k) + 80) & 1) == 0
          && (*(_DWORD *)(*(_DWORD *)rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k) + 80)
            & 0x40000000) == 0 )
        {
          v12 = rf_inline_dword_array4_element_address_unchecked((void *)(a1 + 240), k);
          *(_DWORD *)(*(_DWORD *)v12 + 80) |= 0x40000000u;
          break;
        }
      }
    }
  }
  if ( (a9 & 0x100) != 0 )
  {
    while ( dword_A70630 >= 16 )
    {
      v89 = (_DWORD *)unk_A7051C;
      v90 = 0;
      while ( v89 )
      {
        if ( v89[56] == unk_A7051C )
          v49 = nullptr;
        else
          v49 = (_DWORD *)v89[56];
        v88 = v49;
        if ( (v89[20] & 0x100) != 0 && (v89[20] & 0x400) == 0 )
        {
          rf_world_decal_remove_spatial_links_and_recycle(v89);
          v90 = 1;
          break;
        }
        v89 = v88;
      }
      if ( !v90 )
        return nullptr;
    }
    if ( dword_A70630 >= 14 )
    {
      for ( m = unk_A7051C; m; m = v48 )
      {
        if ( (*(_DWORD *)(m + 80) & 0x40000000) == 0 && (*(_DWORD *)(m + 80) & 0x100) != 0 )
        {
          *(_DWORD *)(m + 80) |= 0x40000000u;
          break;
        }
        if ( *(_DWORD *)(m + 224) == unk_A7051C )
          v48 = 0;
        else
          v48 = *(_DWORD *)(m + 224);
      }
    }
    ++dword_A70630;
  }
  if ( (a9 & 0x200) != 0 )
  {
    while ( dword_A70634 >= 32 )
    {
      v85 = (_DWORD *)unk_A7051C;
      v86 = 0;
      while ( v85 )
      {
        if ( v85[56] == unk_A7051C )
          v47 = nullptr;
        else
          v47 = (_DWORD *)v85[56];
        v84 = v47;
        if ( (v85[20] & 0x200) != 0 && (v85[20] & 0x400) == 0 )
        {
          rf_world_decal_remove_spatial_links_and_recycle(v85);
          v86 = 1;
          break;
        }
        v85 = v84;
      }
      if ( !v86 )
        return nullptr;
    }
    if ( dword_A70634 >= 30 )
    {
      for ( n = unk_A7051C; n; n = v46 )
      {
        if ( (*(_DWORD *)(n + 80) & 0x40000000) == 0 && (*(_DWORD *)(n + 80) & 0x200) != 0 )
        {
          *(_DWORD *)(n + 80) |= 0x40000000u;
          break;
        }
        if ( *(_DWORD *)(n + 224) == unk_A7051C )
          v46 = 0;
        else
          v46 = *(_DWORD *)(n + 224);
      }
    }
    ++dword_A70634;
  }
  destination = (float *)rf_world_decal_pool_acquire_record();
  if ( !destination )
    return nullptr;
  if ( a2 )
  {
    rf_inline_pointer_array_append_capacity48((_DWORD *)(a2 + 156), (int)destination);
    if ( a3 )
      rf_inline_pointer_array_append_capacity48((_DWORD *)(a3 + 156), (int)destination);
  }
  else
  {
    rf_inline_pointer_array_append_capacity128((_DWORD *)(a1 + 240), (int)destination);
  }
  rf_vector_copy(destination, copy_result, lhs);
  rf_matrix3_copy(destination + 3, a5);
  rf_vector_copy(destination + 12, v73, source);
  *((_DWORD *)destination + 15) = a7;
  *((_DWORD *)destination + 16) = a2;
  *((_DWORD *)destination + 17) = a3;
  *((_DWORD *)destination + 18) = a1;
  *((_BYTE *)destination + 76) = a8;
  *((_DWORD *)destination + 20) = a9;
  *((_DWORD *)destination + 21) = a10;
  destination[58] = 0.0;
  destination[22] = a11;
  destination[53] = 0.0;
  destination[54] = 0.0;
  rf_world_decal_build_broadphase_aabb(destination);
  if ( (a9 & 2) == 0 )
    rf_world_decal_gather_faces_and_align_orientation(destination);
  v45 = source[1] * 0.5;
  v18 = rf_vector_multiply_scalar(destination + 6, scaled_result, v45);
  v19 = rf_vector_add(lhs, sum_result, v18);
  v20 = (float *)rf_plane_construct_from_normal_point(v72, destination + 6, (int)v19);
  rf_plane_copy(destination + 23, v20);
  v44 = source[1] * 0.5;
  v21 = rf_vector_multiply_scalar(destination + 6, v68, v44);
  scalar = rf_vector_subtract(lhs, out_vector, v21);
  v22 = rf_vector_negate(destination + 6, (float *)v66);
  v23 = (float *)rf_plane_construct_from_normal_point(v69, v22, (int)scalar);
  rf_plane_copy(destination + 27, v23);
  v43 = source[2] * 0.5;
  v24 = rf_vector_multiply_scalar(destination + 9, v64, v43);
  v25 = rf_vector_add(lhs, v63, v24);
  v26 = (float *)rf_plane_construct_from_normal_point(v65, destination + 9, (int)v25);
  rf_plane_copy(destination + 31, v26);
  v42 = source[2] * 0.5;
  v27 = rf_vector_multiply_scalar(destination + 9, v61, v42);
  scalara = rf_vector_subtract(lhs, v60, v27);
  v28 = rf_vector_negate(destination + 9, (float *)v59);
  v29 = (float *)rf_plane_construct_from_normal_point(v62, v28, (int)scalara);
  rf_plane_copy(destination + 35, v29);
  v41 = *source * 0.5;
  v30 = rf_vector_multiply_scalar(destination + 3, v57, v41);
  v31 = rf_vector_add(lhs, v56, v30);
  v32 = (float *)rf_plane_construct_from_normal_point(v58, destination + 3, (int)v31);
  rf_plane_copy(destination + 39, v32);
  v40 = *source * 0.5;
  v33 = rf_vector_multiply_scalar(destination + 3, v54, v40);
  scalarb = rf_vector_subtract(lhs, v53, v33);
  v34 = rf_vector_negate(destination + 3, (float *)v52);
  v35 = (float *)rf_plane_construct_from_normal_point(v55, v34, (int)scalarb);
  rf_plane_copy(destination + 43, v35);
  if ( ((_DWORD)destination[20] & 0x8000000) != 0 )
    rf_world_decal_visit_room_liquid_faces((int)destination);
  else
    rf_world_decal_project_candidate_or_tree_faces(destination);
  if ( ((_DWORD)destination[20] & 8) != 0 )
  {
    for ( ii = *((_DWORD **)destination + 53); ii; ii = v39 )
    {
      v79 = 17;
      rf_world_decal_collect_face_polygons_by_flags(ii[328], a1, (int)v82, &v79, 8, 0);
      v76 = -1;
      v77 = 0x7FFFFFFF;
      v78 = -1;
      v80 = 0;
      for ( jj = 0; jj < v79; ++jj )
      {
        if ( (_DWORD *)v82[jj] != ii )
        {
          v76 = rf_int_max(v76, *(_DWORD *)(v82[jj] + 200));
          if ( (*(_DWORD *)(*(_DWORD *)(v82[jj] + 1316) + 80) & 1) != 0 )
          {
            ++v80;
          }
          else if ( *(_DWORD *)(v82[jj] + 200) < v77 )
          {
            v77 = *(_DWORD *)(v82[jj] + 200);
            v78 = jj;
          }
        }
      }
      ii[50] = v76 + 1;
      if ( v79 > v80 && v79 - v80 >= 16 )
        rf_world_decal_remove_spatial_links_and_recycle(*(_DWORD **)(v82[v78] + 1316));
      if ( ii[330] == *((_DWORD *)destination + 53) )
        v39 = nullptr;
      else
        v39 = (_DWORD *)ii[330];
    }
  }
  return destination;
}

