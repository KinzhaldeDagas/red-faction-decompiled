// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054AE50 rf_world_room_build_render_packets
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, complete world packet pass, room packet builder, BSP collection, draw order, buffer limits and original PE bytes): Cdecl(world,room),returns0 success/-1 failure. Saves whether room+4 wasNULL,immediately clears room+4,uses shared cursor1482004/end1482000. Collects eligible room faces and nonblocked detail-part faces into up to16384 entries;skips disabled,filtered portal/invisible,plus see-through detail faces. Marks rejected face index+80=-1. Multitexture available on backend102 or forced backend104 chooses one vs two packet layers;decal helper54AA10 can append derived faces. Associates scrolling/liquid data,constructs material/lightmap/special texture sort keys,sorts faces by decreasing auxiliary/material keys,then assigns unique world-vertex signed16 IDs through vertex+28. Copies XYZ into12-byte global-domain array.
// Builds up to512 groups,each run limited640 faces;without multitexture,ordinary groups may get second layer. Group vertex dedup is per world vertex AND exact equality of all4 UV floats,linked through vertex+30/global chains;no epsilon or NaN equivalence. Packet layout:36-byte header XYZptr0,worldVertexCount4,faceDomainCount8,28-byte face records12,visibilityBytes16,80-byte groups20,u16 groupCount24,BVHroot28,cacheState32=0. Group map40 holds local->global WORDs,UV44 has4floats/vertex,faces48 have countWORD0,indexPointer4,plane8,tail24 initially SOURCE FACE pointer;visible flags52,all index backing56,special face map60,texture handles64/68,short counts72/74/76. Debug modes/special decal groups select distinct descriptors/colors;UV scroll metadata records speed/time. Greedy54A180 face ordering/remap applied before source face indices/planes copied. Recursive54A7B0 builds44-byte BVH and
// sorted WORD face-index lists. Special groups map back to original ordinary face visibility;disable scrolling there. Initial scroll offsets reduced to minima of stored primary UV values. Success records newly tracked room owner when previously uncached,commits global cursor,returns0. Failure is NOT transactional:mutated source vertex/face fields,global staging lists and room pointer can remain changed. In particular54C6B5 publishes room+4 BEFORE final header/group/visibility bounds check;later -1 paths do not clear it or commit cursor. Some allocations reject cursor==end,one intermediate uses only> end;no rollback of prior mutations. No global vertex/signed16-ID/dedup-index capacity validation beyond observed face/group/arena checks.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): ADDITIONAL VERIFIED LIQUID-SCROLL QUIRK:temporary descriptor constructed at54AEFE with velocitiesU/V=0. Liquid fallback enabled only if room byte388 nonzero AND BOTH floatU436 andV440 compare !=0. On enabled path54AF4B..54AF51 copies ONLY U436 to descriptor+4;descriptor V+8 remains0,despite requiring V440 nonzero. Temporary descriptor is associated with eligible liquid faces lacking a later explicit UV-controller association;group speed fields copied from descriptor+4/+8. Thus fallback uses(U,0),not authored(U,V),and a zero component disables fallback entirely. Explicit controller association can replace temporary pointer. Separate539B30 authored-sky updater uses byte388==1 and OR of nonzero velocities,then
// applies BOTH. Preserve this distinction;previous packet layout/lifecycle findings retained.
int __cdecl rf_world_room_build_render_packets(int a1, int a2)
{
  int first_dword; // eax
  int *v4; // eax
  int *v5; // eax
  int *v6; // eax
  int *v7; // eax
  double v8; // st7
  double v9; // st7
  float **v10; // [esp+Ch] [ebp-1ACh]
  float **v11; // [esp+10h] [ebp-1A8h]
  float **v12; // [esp+14h] [ebp-1A4h]
  int v13; // [esp+18h] [ebp-1A0h]
  int v14; // [esp+1Ch] [ebp-19Ch]
  float **v15; // [esp+20h] [ebp-198h]
  float **v16; // [esp+24h] [ebp-194h]
  float **v17; // [esp+28h] [ebp-190h]
  char *v18; // [esp+2Ch] [ebp-18Ch]
  char *v19; // [esp+30h] [ebp-188h]
  int v20; // [esp+4Ch] [ebp-16Ch] BYREF
  int v21; // [esp+50h] [ebp-168h] BYREF
  int v22; // [esp+54h] [ebp-164h] BYREF
  int v23; // [esp+58h] [ebp-160h] BYREF
  int v24; // [esp+5Ch] [ebp-15Ch]
  float *v25; // [esp+68h] [ebp-150h]
  int v26; // [esp+6Ch] [ebp-14Ch]
  int v27; // [esp+70h] [ebp-148h]
  int v28; // [esp+74h] [ebp-144h]
  int v29; // [esp+78h] [ebp-140h]
  float v30[4]; // [esp+7Ch] [ebp-13Ch] BYREF
  int nn; // [esp+8Ch] [ebp-12Ch]
  float *v32; // [esp+90h] [ebp-128h]
  int mm; // [esp+94h] [ebp-124h]
  float *v34; // [esp+98h] [ebp-120h]
  float *v35; // [esp+9Ch] [ebp-11Ch]
  float *v36; // [esp+A0h] [ebp-118h]
  int v37; // [esp+A4h] [ebp-114h]
  int v38; // [esp+A8h] [ebp-110h]
  int v39; // [esp+ACh] [ebp-10Ch]
  int v40; // [esp+B0h] [ebp-108h]
  int v41; // [esp+B4h] [ebp-104h]
  int v42; // [esp+B8h] [ebp-100h]
  int v43; // [esp+BCh] [ebp-FCh]
  int v44; // [esp+C0h] [ebp-F8h]
  float *v45; // [esp+C4h] [ebp-F4h]
  char *v46; // [esp+C8h] [ebp-F0h]
  int v47; // [esp+CCh] [ebp-ECh]
  int v48; // [esp+D0h] [ebp-E8h]
  __int16 *v49; // [esp+D4h] [ebp-E4h]
  int v50; // [esp+D8h] [ebp-E0h]
  _WORD *v51; // [esp+DCh] [ebp-DCh]
  int v52; // [esp+E0h] [ebp-D8h]
  float *v53; // [esp+E4h] [ebp-D4h]
  int v54; // [esp+E8h] [ebp-D0h]
  int v55; // [esp+ECh] [ebp-CCh]
  int v56; // [esp+F0h] [ebp-C8h]
  int v57; // [esp+F4h] [ebp-C4h]
  int v58; // [esp+F8h] [ebp-C0h]
  int n; // [esp+FCh] [ebp-BCh]
  int v60; // [esp+100h] [ebp-B8h]
  _WORD *v61; // [esp+104h] [ebp-B4h]
  _WORD *v62; // [esp+108h] [ebp-B0h]
  int v63; // [esp+10Ch] [ebp-ACh]
  int v64; // [esp+110h] [ebp-A8h]
  int v65; // [esp+114h] [ebp-A4h]
  int v66; // [esp+118h] [ebp-A0h]
  _BYTE *v67; // [esp+11Ch] [ebp-9Ch]
  int k; // [esp+120h] [ebp-98h]
  float **ii; // [esp+124h] [ebp-94h]
  int v70; // [esp+128h] [ebp-90h]
  char *v71; // [esp+12Ch] [ebp-8Ch]
  char v72; // [esp+133h] [ebp-85h]
  int v73; // [esp+134h] [ebp-84h]
  char v74; // [esp+13Bh] [ebp-7Dh]
  char v75[4]; // [esp+13Ch] [ebp-7Ch] BYREF
  float v76; // [esp+140h] [ebp-78h]
  int v77; // [esp+154h] [ebp-64h]
  int jj; // [esp+158h] [ebp-60h]
  char v79; // [esp+15Fh] [ebp-59h]
  _DWORD *v80; // [esp+160h] [ebp-58h]
  int m; // [esp+164h] [ebp-54h]
  char *v82; // [esp+168h] [ebp-50h] BYREF
  char *v83; // [esp+16Ch] [ebp-4Ch]
  int v84; // [esp+170h] [ebp-48h] BYREF
  char *v85; // [esp+174h] [ebp-44h]
  char *v86; // [esp+178h] [ebp-40h]
  int i; // [esp+17Ch] [ebp-3Ch]
  int v88; // [esp+180h] [ebp-38h]
  void *v89; // [esp+184h] [ebp-34h]
  int v90; // [esp+188h] [ebp-30h]
  int v91; // [esp+18Ch] [ebp-2Ch]
  int v92; // [esp+190h] [ebp-28h]
  int v93; // [esp+194h] [ebp-24h]
  int j; // [esp+198h] [ebp-20h]
  bool v95; // [esp+19Fh] [ebp-19h]
  int v96; // [esp+1A0h] [ebp-18h]
  int kk; // [esp+1A4h] [ebp-14h]
  char v98; // [esp+1ABh] [ebp-Dh]
  int v99; // [esp+1B4h] [ebp-4h]

  v84 = 0;
  v95 = *(_DWORD *)(a2 + 4) == 0;
  *(_DWORD *)(a2 + 4) = 0;
  v82 = (char *)unk_1482004;
  v72 = 0;
  if ( dword_187CC9C == 102 )
  {
    v72 = rf_d3d8_multitexture_available;
  }
  else if ( dword_187CC9C == 104 )
  {
    v72 = 1;
  }
  if ( v72 )
    v73 = 1;
  else
    v73 = 2;
  rf_uv_scroll_descriptor_construct_invalid(v75);
  v99 = 0;
  if ( !*(_BYTE *)(a2 + 388) || *(float *)(a2 + 436) == 0.0 || *(float *)(a2 + 440) == 0.0 )
  {
    v74 = 0;
  }
  else
  {
    v74 = 1;
    v76 = *(float *)(a2 + 436);
  }
  dword_18CCFC4 = 0;
  unk_149CB18 = &unk_1462000;
  for ( i = rf_receiver_get_first_dword((void *)(a2 + 40)); i; i = rf_face_next_room_link(i) )
  {
    if ( (*(_DWORD *)(i + 40) & 1) != 0
      || !unk_A42094 && rf_face_is_portal((__int16 *)(i + 40))
      || !unk_A420A8 && rf_face_is_invisible((_DWORD *)(i + 40))
      || dword_18CCFC4 >= 0x4000 )
    {
      *(_WORD *)(i + 80) = -1;
    }
    else
    {
      unk_18BCFB8[dword_18CCFC4] = i;
      if ( v74 && rf_face_is_liquid((_DWORD *)(i + 40)) )
        v19 = v75;
      else
        v19 = nullptr;
      unk_1484718[dword_18CCFC4++] = (int)v19;
      v84 += v73;
      rf_world_packet_append_decal_derived_faces(a1, i, &v84);
    }
  }
  v90 = dword_18CCFC4;
  unk_143E978 = 0;
  for ( j = 0; ; ++j )
  {
    first_dword = rf_receiver_get_first_dword((void *)(a2 + 108));
    if ( j >= first_dword )
      break;
    v67 = *(_BYTE **)sub_552200((_DWORD *)(a2 + 108), j);
    if ( !sub_5211F0(v67) )
    {
      unk_145DD80[unk_143E978++] = (int)v67;
      for ( i = rf_receiver_get_first_dword(v67 + 40); i; i = rf_face_next_room_link(i) )
      {
        if ( (*(_DWORD *)(i + 40) & 1) != 0
          || !unk_A42094 && rf_face_is_portal((__int16 *)(i + 40))
          || !unk_A420A8 && rf_face_is_invisible((_DWORD *)(i + 40))
          || rf_face_is_see_through((_DWORD *)(i + 40))
          || dword_18CCFC4 >= 0x4000 )
        {
          *(_WORD *)(i + 80) = -1;
        }
        else
        {
          unk_18BCFB8[dword_18CCFC4] = i;
          if ( v74 && rf_face_is_liquid((_DWORD *)(i + 40)) )
            v18 = v75;
          else
            v18 = nullptr;
          unk_1484718[dword_18CCFC4++] = (int)v18;
          v84 += v73;
          rf_world_packet_append_decal_derived_faces(a1, i, &v84);
        }
      }
    }
  }
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    i = unk_18BCFB8[j];
    *(_DWORD *)(i + 44) = 0;
  }
  v70 = rf_receiver_get_first_dword((void *)(a1 + 756));
  for ( j = 0; j < v70; ++j )
  {
    v66 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 756), j);
    v65 = rf_receiver_get_first_dword((void *)(v66 + 12));
    for ( k = 0; k < v65; ++k )
    {
      v64 = *(_DWORD *)sub_552200((_DWORD *)(v66 + 12), k);
      if ( *(_DWORD *)(v64 + 68) == a2 || unknown_libname_11(*(void **)(v64 + 68)) )
        *(_DWORD *)(v64 + 44) = v66;
    }
  }
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    i = unk_18BCFB8[j];
    if ( *(_DWORD *)(i + 44) )
      unk_1484718[j] = *(_DWORD *)(i + 44);
  }
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    i = unk_18BCFB8[j];
    if ( dword_A42090 )
    {
      *(_DWORD *)(i + 44) = *(_DWORD *)(i + 68);
    }
    else
    {
      v63 = i + 44;
      v62 = (_WORD *)(i + 44);
      v61 = (_WORD *)(i + 46);
      if ( *(__int16 *)(i + 54) <= -1 )
      {
        *v62 = 0;
      }
      else
      {
        v60 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 192), *(__int16 *)(i + 54));
        *v62 = *(_WORD *)(*(_DWORD *)(v60 + 12) + 20);
      }
      if ( (*(_DWORD *)(i + 40) & 0x20000) != 0 )
      {
        *v61 = *(_WORD *)(*(_DWORD *)(*(_DWORD *)(i + 76) + 1316) + 60) | 0x8000;
      }
      else if ( j >= v90 && unknown_libname_11(*(void **)(i + 68)) && *(_BYTE *)(*(_DWORD *)(i + 68) + 106) )
      {
        *v61 = *(_WORD *)(i + 48) & 0x3FFF;
      }
      else
      {
        *v61 = *(_WORD *)(i + 48) & 0x3FFF | 0x4000;
      }
    }
  }
  v96 = dword_18CCFC4;
  if ( dword_18CCFC4 > 1 )
  {
    for ( m = v96 / 2; m > 0; m /= 2 )
    {
      for ( n = m; n < v96; ++n )
      {
        for ( k = n - m;
              k >= 0
           && (unk_1484718[k] < unk_1484718[m + k]
            || unk_1484718[k] == unk_1484718[m + k]
            && *(_DWORD *)(unk_18BCFB8[k] + 44) < *(_DWORD *)(unk_18BCFB8[m + k] + 44));
              k -= m )
        {
          v58 = unk_18BCFB8[k];
          v57 = unk_1484718[k];
          unk_18BCFB8[k] = unk_18BCFB8[m + k];
          unk_1484718[k] = unk_1484718[m + k];
          unk_18BCFB8[m + k] = v58;
          unk_1484718[m + k] = v57;
        }
      }
    }
  }
  v88 = 0;
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    v56 = unk_18BCFB8[j];
    for ( ii = *(float ***)(v56 + 64); ii; ii = v17 )
    {
      *((_WORD *)*ii + 14) = 1;
      if ( ii[5] == *(float **)(v56 + 64) )
        v17 = nullptr;
      else
        v17 = (float **)ii[5];
    }
  }
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    v55 = unk_18BCFB8[j];
    for ( ii = *(float ***)(v55 + 64); ii; ii = v16 )
    {
      if ( *((__int16 *)*ii + 14) > 0 )
        *((_WORD *)*ii + 14) = -(__int16)v88++;
      if ( ii[5] == *(float **)(v55 + 64) )
        v16 = nullptr;
      else
        v16 = (float **)ii[5];
    }
  }
  v71 = v82;
  v82 += 12 * v88;
  if ( (unsigned int)v82 >= unk_1482000 )
    goto LABEL_120;
  for ( j = 0; j < dword_18CCFC4; ++j )
  {
    v54 = unk_18BCFB8[j];
    for ( ii = *(float ***)(v54 + 64); ii; ii = v15 )
    {
      if ( *((__int16 *)*ii + 14) <= 0 )
      {
        *((_WORD *)*ii + 14) = -*((_WORD *)*ii + 14);
        v53 = (float *)&v71[12 * *((__int16 *)*ii + 14)];
        *v53 = **ii;
        v53[1] = (*ii)[1];
        v53[2] = (*ii)[2];
      }
      if ( ii[5] == *(float **)(v54 + 64) )
        v15 = nullptr;
      else
        v15 = (float **)ii[5];
    }
  }
  v85 = v82;
  v82 += 28 * v84;
  if ( (unsigned int)v82 >= unk_1482000 )
  {
LABEL_120:
    v99 = -1;
    rf_uv_scroll_descriptor_destroy((void **)v75);
    return -1;
  }
  v83 = v85;
  v77 = 0;
  jj = 0;
  v92 = 0;
  v98 = 0;
  v79 = 0;
  v91 = 0;
  while ( v91 < dword_18CCFC4 )
  {
    if ( v77 >= 512 )
    {
      v24 = -1;
      v99 = -1;
      rf_uv_scroll_descriptor_destroy((void **)v75);
      return v24;
    }
    v46 = (char *)&unk_149CB20 + 80 * v77;
    v50 = *(_DWORD *)(unk_18BCFB8[v91] + 44);
    v48 = unk_1484718[v91];
    for ( jj = v91 + 1; jj < dword_18CCFC4 && v50 == *(_DWORD *)(unk_18BCFB8[jj] + 44) && v48 == unk_1484718[jj]; ++jj )
      ;
    if ( jj - v91 > 640 )
      jj = v91 + 640;
    i = unk_18BCFB8[v91];
    v79 = 0;
    if ( dword_A42090 )
    {
      *((_DWORD *)v46 + 16) = -1;
      *((_DWORD *)v46 + 17) = -1;
      v42 = unk_18BCFB8[v91];
      if ( *(_DWORD *)(v42 + 68) )
      {
        v39 = *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 1;
        v40 = *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 2;
        v41 = *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 4;
        v39 += *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 8;
        v40 += *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 0x10;
        v41 += *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 0x20;
        v39 += *(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 0x40;
        LOBYTE(v40) = v40 + (*(_DWORD *)(*(_DWORD *)(v42 + 68) + 32) & 0x80);
        LOBYTE(v39) = 43 * v39;
        LOBYTE(v40) = 43 * v40;
        LOBYTE(v41) = 43 * v41;
        v39 = (unsigned __int8)v39;
        v40 = (unsigned __int8)v40;
        v41 = (unsigned __int8)v41;
        if ( (unsigned __int8)v41 + (unsigned __int8)v40 + (unsigned __int8)v39 <= 16 )
        {
          v39 = 48;
          v40 = 48;
          v41 = 48;
        }
      }
      else
      {
        v41 = 127;
        v40 = 127;
        v39 = 127;
      }
      *((_DWORD *)v46 + 9) = v41 | (v40 << 8) | (v39 << 16) | 0xFF000000;
      v4 = rf_render_state_pack(&v23, 0, 0, 0, 0, 4, 0);
      *((_DWORD *)v46 + 8) = *v4;
    }
    else if ( dword_A4208C )
    {
      *((_DWORD *)v46 + 16) = -1;
      *((_DWORD *)v46 + 17) = -1;
      *((_DWORD *)v46 + 9) = 1065320319;
      v5 = rf_render_state_pack(&v22, 0, 0, 0, 2, 0, 0);
      *((_DWORD *)v46 + 8) = *v5;
    }
    else
    {
      *((_DWORD *)v46 + 9) = -1;
      if ( (*(_DWORD *)(i + 40) & 0x20000) != 0 )
      {
        v46[24] = 1;
        v92 += jj - v91;
        *((_DWORD *)v46 + 16) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 76) + 1316) + 60);
        if ( (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 76) + 1316) + 80) & 0x20) != 0 )
        {
          *((_DWORD *)v46 + 8) = unk_18CCFE8;
        }
        else if ( (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 76) + 1316) + 80) & 0x40) != 0 )
        {
          *((_DWORD *)v46 + 8) = unk_18CCFD4;
        }
        else if ( (*(_DWORD *)(*(_DWORD *)(*(_DWORD *)(i + 76) + 1316) + 80) & 0x80) != 0 )
        {
          *((_DWORD *)v46 + 8) = unk_18CCFCC;
        }
        else
        {
          *((_DWORD *)v46 + 8) = unk_18CCFEC;
        }
      }
      else
      {
        v79 = 1;
        v46[24] = v98;
        *((_DWORD *)v46 + 16) = *(_DWORD *)(i + 48);
        if ( v72 )
        {
          if ( dword_A420A0 || dword_A4209C )
          {
            v7 = rf_render_state_pack(&v20, 1, 1, 0, 0, 4, 0);
            *((_DWORD *)v46 + 8) = *v7;
          }
          else
          {
            *((_DWORD *)v46 + 8) = unk_18CCFF0;
          }
        }
        else if ( v98 )
        {
          *((_DWORD *)v46 + 8) = unk_187CD20;
        }
        else
        {
          v6 = rf_render_state_pack(&v21, 1, 1, 0, 0, 4, 2);
          *((_DWORD *)v46 + 8) = *v6;
        }
        *((_DWORD *)v46 + 15) = 0;
      }
      if ( dword_A4209C || v98 )
      {
        if ( *(__int16 *)(i + 54) <= -1 )
          v14 = -1;
        else
          v14 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 192), *(__int16 *)(i + 54)) + 12) + 16);
        *((_DWORD *)v46 + 16) = v14;
        *((_DWORD *)v46 + 17) = -1;
      }
      else
      {
        if ( *(__int16 *)(i + 54) <= -1 )
          v13 = -1;
        else
          v13 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a1 + 192), *(__int16 *)(i + 54)) + 12) + 16);
        *((_DWORD *)v46 + 17) = v13;
      }
    }
    if ( v48 )
    {
      v46[16] = 1;
      *((float *)v46 + 2) = *(float *)(v48 + 4);
      *((float *)v46 + 3) = *(float *)(v48 + 8);
      *((float *)v46 + 5) = 0.0;
    }
    else
    {
      v46[16] = 0;
    }
    v44 = 0;
    v43 = 0;
    for ( j = v91; j < jj; ++j )
    {
      i = unk_18BCFB8[j];
      for ( ii = *(float ***)(i + 64); ii; ii = v12 )
      {
        *((_WORD *)*ii + 15) = -1;
        if ( ii[5] == *(float **)(i + 64) )
          v12 = nullptr;
        else
          v12 = (float **)ii[5];
      }
    }
    v52 = 0;
    j = v91;
LABEL_196:
    if ( j < jj )
    {
      i = unk_18BCFB8[j];
      v38 = 0;
      for ( ii = *(float ***)(i + 64); ; ii = v11 )
      {
        if ( !ii )
        {
          v52 += v38;
          v43 = v43 + v38 - 2;
          ++j;
          goto LABEL_196;
        }
        ++v38;
        if ( *((__int16 *)*ii + 15) < 0 )
          break;
        v37 = -1;
        for ( kk = *((__int16 *)*ii + 15); kk >= 0; kk = unk_1494B18[kk] )
        {
          v37 = kk;
          v36 = (float *)unk_1426C78[kk];
          if ( *((float *)ii + 1) == v36[1]
            && *((float *)ii + 2) == v36[2]
            && *((float *)ii + 3) == v36[3]
            && *((float *)ii + 4) == v36[4] )
          {
            break;
          }
        }
        if ( kk < 0 )
        {
          unk_1494B18[v37] = v44;
LABEL_214:
          unk_1426C78[v44] = (int)ii;
          unk_1494B18[v44++] = -1;
        }
        if ( ii[5] == *(float **)(i + 64) )
          v11 = nullptr;
        else
          v11 = (float **)ii[5];
      }
      *((_WORD *)*ii + 15) = v44;
      goto LABEL_214;
    }
    *((_WORD *)v46 + 36) = v44;
    *((_WORD *)v46 + 37) = jj - v91;
    *((_WORD *)v46 + 38) = v43;
    *((_DWORD *)v46 + 10) = v82;
    v82 += 2 * v44;
    *((_DWORD *)v46 + 11) = v82;
    v82 += 16 * v44;
    *((_DWORD *)v46 + 12) = v83;
    v83 += 28 * *((__int16 *)v46 + 37);
    *((_DWORD *)v46 + 14) = v82;
    v82 += 2 * v52;
    if ( (unsigned int)v82 > unk_1482000 )
      goto LABEL_266;
    v45 = *((float **)v46 + 11);
    v51 = *((_WORD **)v46 + 10);
    if ( dword_A4209C || v98 )
    {
      j = 0;
      while ( j < v44 )
      {
        v35 = (float *)unk_1426C78[j];
        *v51 = *(_WORD *)(*(_DWORD *)v35 + 28);
        *v45 = v35[3];
        v45[1] = v35[4];
        v45[2] = 0.0;
        v45[3] = 0.0;
        ++j;
        v45 += 4;
        ++v51;
      }
    }
    else
    {
      j = 0;
      while ( j < v44 )
      {
        v34 = (float *)unk_1426C78[j];
        *v51 = *(_WORD *)(*(_DWORD *)v34 + 28);
        *v45 = v34[1];
        v45[1] = v34[2];
        v45[2] = v34[3];
        v45[3] = v34[4];
        ++j;
        v45 += 4;
        ++v51;
      }
    }
    v49 = *((__int16 **)v46 + 12);
    v47 = *((_DWORD *)v46 + 14);
    for ( j = v91; j < jj; ++j )
    {
      i = unk_18BCFB8[j];
      *((_DWORD *)v49 + 6) = i;
      *v49 = 0;
      *((_DWORD *)v49 + 1) = v47;
      i = unk_18BCFB8[j];
      for ( ii = *(float ***)(i + 64); ii; ii = v10 )
      {
        for ( mm = *((__int16 *)*ii + 15); mm >= 0; mm = unk_1494B18[mm] )
        {
          v32 = (float *)unk_1426C78[mm];
          if ( *((float *)ii + 1) == v32[1]
            && *((float *)ii + 2) == v32[2]
            && *((float *)ii + 3) == v32[3]
            && *((float *)ii + 4) == v32[4] )
          {
            break;
          }
        }
        *(_WORD *)(v47 + 2 * (*v49)++) = mm;
        if ( ii[5] == *(float **)(i + 64) )
          v10 = nullptr;
        else
          v10 = (float **)ii[5];
      }
      v47 += 2 * *v49;
      v49 += 14;
    }
    if ( v72 || !v79 || v98 )
    {
      if ( v98 )
        v98 = 0;
    }
    else
    {
      jj = v91;
      v98 = 1;
    }
    v91 = jj;
    ++v77;
  }
  *(_DWORD *)(a2 + 4) = v82;
  v80 = v82;
  v82 += 36;
  v89 = v82;
  v82 += 80 * v77;
  v86 = v82;
  v82 += v84;
  if ( (unsigned int)v82 >= unk_1482000 )
    goto LABEL_266;
  memcpy(v89, &unk_149CB20, 80 * v77);
  v80[5] = v89;
  *((_WORD *)v80 + 12) = v77;
  v80[2] = v84;
  v80[4] = v86;
  v80[3] = v85;
  *v80 = v71;
  v80[1] = v88;
  v93 = 0;
  for ( j = 0; j < *((unsigned __int16 *)v80 + 12); ++j )
  {
    rf_world_packet_group_reorder_faces_and_vertices(v80[5] + 80 * j);
    *(_DWORD *)(v80[5] + 80 * j + 52) = v86;
    v86 += *(__int16 *)(v80[5] + 80 * j + 74);
    if ( *(_BYTE *)(v80[5] + 80 * j + 24) )
    {
      v93 += *(__int16 *)(v80[5] + 80 * j + 74);
    }
    else
    {
      for ( nn = 0; nn < *(__int16 *)(v80[5] + 80 * j + 74); ++nn )
      {
        v29 = *(_DWORD *)(v80[5] + 80 * j + 48) + 28 * nn;
        *(_WORD *)(*(_DWORD *)(v29 + 24) + 80) = v93++;
        rf_plane4_copy_normal_scalar(v30, *(float **)(v29 + 24));
        rf_plane_copy((float *)(v29 + 8), v30);
      }
    }
  }
  if ( rf_world_packet_build_bvh_node((void *)a2, (int)v80, &v82, 0, *(float **)(a2 + 60), (int)(v80 + 7)) )
  {
LABEL_266:
    v99 = -1;
    rf_uv_scroll_descriptor_destroy((void **)v75);
    return -1;
  }
  else
  {
    for ( j = 0; j < *((unsigned __int16 *)v80 + 12); ++j )
    {
      v28 = v80[5] + 80 * j;
      if ( *(_BYTE *)(v28 + 24) )
      {
        *(_BYTE *)(v28 + 16) = 0;
        *(_DWORD *)(v28 + 60) = v82;
        v82 += 2 * *(__int16 *)(v28 + 74);
        if ( (unsigned int)v82 >= unk_1482000 )
          goto LABEL_266;
        for ( k = 0; k < *(__int16 *)(v28 + 74); ++k )
        {
          v26 = *(_DWORD *)(v28 + 48) + 28 * k;
          v27 = *(_DWORD *)(v26 + 24);
          if ( (*(_DWORD *)(*(_DWORD *)(v26 + 24) + 40) & 0x20000) != 0 )
            v27 = *(_DWORD *)(v27 + 96);
          *(_WORD *)(*(_DWORD *)(v28 + 60) + 2 * k) = *(_WORD *)(v27 + 80);
        }
      }
      if ( *(_BYTE *)(v28 + 16) )
      {
        *(float *)v28 = **(float **)(v28 + 44);
        *(float *)(v28 + 4) = *(float *)(*(_DWORD *)(v28 + 44) + 4);
        v25 = (float *)(*(_DWORD *)(v28 + 44) + 16);
        k = 1;
        while ( k < *(__int16 *)(v28 + 72) )
        {
          v8 = rf_float_minimum_two_values(*(float *)v28, *v25);
          *(float *)v28 = v8;
          v9 = rf_float_minimum_two_values(*(float *)(v28 + 4), v25[1]);
          *(float *)(v28 + 4) = v9;
          ++k;
          v25 += 4;
        }
      }
    }
    v80[8] = 0;
    if ( v95 )
      unk_1494718[dword_1426C74++] = a2;
    unk_1482004 = v82;
    v99 = -1;
    rf_uv_scroll_descriptor_destroy((void **)v75);
    return 0;
  }
}

