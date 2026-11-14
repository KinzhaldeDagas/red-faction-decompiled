// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054D990 rf_lightmap_update_lighting_and_upload_rgb555
// UNREALRED VERIFIED [lightmap-pixels-20261028]: Actual operation on lightmaprecord plus solidcontext and shadowmode. Zero width+24 orheight+28 returnswithoutclearingflags. Recordatlas+12 points width+4,height+8,baseRGBbytes+12,bitmaphandle+16; regionorigin+16/+20,size+24/+28,worldAABB+52/+64,UVscales+76/+80,offsets+84/+88,mapperselector+92,ownerroomindex+104,normal+108. If flagsbyte+8 mask6set and byte+10clear,buildsactive-listquery(owner,AABB,0,1),syncreceivertransforms. Active0 fillsregionRGB with roomambient if ownerroombyte+69==1 elseglobalambient,scaled128; active>=64 fillsmagenta255,0,255. Both markbit8 andclearlist. For1..63 initializes floatplanes ambient*0.5,deletes oldtemporaryshadowrecords global0xD4C548,and buildsperlight masks initialized255. Shadowmode0 requestsrecompute withoutmask; mode1 calls0x550950 projectedshadow,mode2 calls0x5505A0 raymask,accordingrecordflag2
// orflag4+lightDWORD+80==2; lighttype0 alwaysrequestsrecompute. If requested,calls0x54F000 withmasks whenactive+nonzeromode,convertsfloatRGB backtoregion via0x54EB80,or3x3filter0x54EC70 only forbothdimensions>8 and interior2..dimension-3; marksbit8,clearsactive-list. If flag1set,usesexistingactive-list when0x528C10nonzero elsequeries(owner,AABB,1,0); synchronizesreceivertransforms. Oneligiblelights locksbitmap,pertexelmapsworldposition,computesnonworlddiffuse,addsbaseRGBbytes,shiftschannelsright3,saturates31,packs0x8000|(R<<10)|(G<<5)|B. Clearsbit8 onthatlocksuccess; ifnoeligiblelights marksbit8. Clearslistonlyifbuiltlocally. Remainingbit8 uploadsbaseRGBregion asopaqueRGB555 usinglockpitch andregionorigin. BOTH uploadpaths assume2bytes/pixel without inspecting returnedpixelformat. Finalflagsbyte+8=0 even iflockfailed; no retrydirtybitretained. No atlas-nullguard atentry beyond
// dimensions,globalfloatplanecapacity or lockformatcheck. Returnbyte incidentalpointer/bitmapunlockresult,not reliable updatesuccess.
char __thiscall rf_lightmap_update_lighting_and_upload_rgb555(int this, int a2, int a3)
{
  _DWORD *v3; // eax
  int first_dword; // eax
  int v6; // [esp+10h] [ebp-18Ch]
  int v7; // [esp+14h] [ebp-188h]
  int v8; // [esp+18h] [ebp-184h]
  void *v10; // [esp+38h] [ebp-164h]
  int i3; // [esp+44h] [ebp-158h]
  int v12; // [esp+48h] [ebp-154h]
  unsigned int v13; // [esp+50h] [ebp-14Ch]
  int i2; // [esp+58h] [ebp-144h]
  unsigned int v15[6]; // [esp+5Ch] [ebp-140h] BYREF
  int v16; // [esp+74h] [ebp-128h]
  _DWORD *v17; // [esp+7Ch] [ebp-120h]
  int v18[3]; // [esp+80h] [ebp-11Ch] BYREF
  _BYTE v19[5]; // [esp+8Fh] [ebp-10Dh] BYREF
  int v20; // [esp+94h] [ebp-108h]
  _WORD v21[3]; // [esp+9Ah] [ebp-102h] BYREF
  int v22; // [esp+A0h] [ebp-FCh]
  int v23; // [esp+A4h] [ebp-F8h]
  int v24; // [esp+A8h] [ebp-F4h]
  float v25; // [esp+ACh] [ebp-F0h]
  unsigned int v26; // [esp+B0h] [ebp-ECh]
  int v27; // [esp+B4h] [ebp-E8h]
  int v28; // [esp+B8h] [ebp-E4h]
  int v29; // [esp+BCh] [ebp-E0h]
  float v30; // [esp+C0h] [ebp-DCh]
  float v31; // [esp+C4h] [ebp-D8h]
  float v32; // [esp+C8h] [ebp-D4h]
  float v33; // [esp+CCh] [ebp-D0h]
  unsigned int v34; // [esp+D0h] [ebp-CCh]
  int v35; // [esp+D4h] [ebp-C8h]
  unsigned int v36[8]; // [esp+D8h] [ebp-C4h] BYREF
  int v37; // [esp+F8h] [ebp-A4h]
  int v38; // [esp+FCh] [ebp-A0h]
  char active_list_context_byte; // [esp+103h] [ebp-99h]
  unsigned int v40; // [esp+104h] [ebp-98h]
  int v41; // [esp+108h] [ebp-94h]
  int v42; // [esp+10Ch] [ebp-90h]
  int m; // [esp+110h] [ebp-8Ch]
  int k; // [esp+114h] [ebp-88h]
  int mm; // [esp+118h] [ebp-84h]
  _BYTE *v46; // [esp+11Ch] [ebp-80h]
  int kk; // [esp+120h] [ebp-7Ch]
  _BYTE *v48; // [esp+124h] [ebp-78h]
  int i1; // [esp+128h] [ebp-74h]
  int nn; // [esp+12Ch] [ebp-70h]
  int v51; // [esp+130h] [ebp-6Ch]
  int v52; // [esp+134h] [ebp-68h]
  int active_world_record_unchecked; // [esp+138h] [ebp-64h]
  int ii; // [esp+13Ch] [ebp-60h]
  int n; // [esp+140h] [ebp-5Ch]
  _BYTE *v56; // [esp+144h] [ebp-58h]
  float v57; // [esp+148h] [ebp-54h] BYREF
  float *v58; // [esp+14Ch] [ebp-50h]
  float *v59; // [esp+150h] [ebp-4Ch]
  float *v60; // [esp+154h] [ebp-48h]
  float v61; // [esp+158h] [ebp-44h] BYREF
  float v62; // [esp+15Ch] [ebp-40h] BYREF
  char v63; // [esp+163h] [ebp-39h]
  _BYTE *v64; // [esp+164h] [ebp-38h]
  float v65; // [esp+168h] [ebp-34h] BYREF
  int v66; // [esp+16Ch] [ebp-30h]
  int v67; // [esp+170h] [ebp-2Ch]
  int v68; // [esp+174h] [ebp-28h]
  int v69; // [esp+178h] [ebp-24h]
  int v70; // [esp+17Ch] [ebp-20h]
  float v71; // [esp+180h] [ebp-1Ch] BYREF
  int j; // [esp+184h] [ebp-18h]
  int i; // [esp+188h] [ebp-14h]
  float v74; // [esp+18Ch] [ebp-10h] BYREF
  int v75; // [esp+190h] [ebp-Ch]
  signed int active; // [esp+194h] [ebp-8h]
  int jj; // [esp+198h] [ebp-4h]

  LOBYTE(v3) = this;
  if ( !*(_DWORD *)(this + 24) || !*(_DWORD *)(this + 28) )
    return (char)v3;
  if ( (*(_BYTE *)(this + 8) & 6) != 0 && !*(_BYTE *)(this + 10) )
  {
    v75 = 0;
    if ( *(_DWORD *)(this + 104) != -1 )
      v75 = *(_DWORD *)sub_552200((_DWORD *)(a2 + 144), *(_DWORD *)(this + 104));
    active = rf_light_build_active_list_for_aabb_query(v75, (float *)(this + 52), (float *)(this + 64), 0, 1);
    rf_light_sync_active_receiver_space_if_enabled();
    if ( !active )
    {
      if ( *(_DWORD *)(this + 104) == -1
        || (v64 = *(_BYTE **)sub_552200((_DWORD *)(a2 + 144), *(_DWORD *)(this + 104)), v64[69] != 1) )
      {
        rf_light_get_ambient_rgb_floats(&v65, &v71, &v74);
      }
      else
      {
        v65 = (double)(unsigned __int8)v64[70] * 0.003921568859368563;
        v71 = (double)(unsigned __int8)v64[71] * 0.003921568859368563;
        v74 = (double)(unsigned __int8)v64[72] * 0.003921568859368563;
      }
      v66 = (int)(v65 * 128.0);
      v68 = (int)(v71 * 128.0);
      v69 = (int)(v74 * 128.0);
      v67 = 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4) * *(_DWORD *)(this + 20);
      for ( i = 0; i < *(_DWORD *)(this + 28); ++i )
      {
        v70 = 3 * *(_DWORD *)(this + 16);
        for ( j = 0; j < *(_DWORD *)(this + 24); ++j )
        {
          *(_BYTE *)(v67 + v70 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12)) = v66;
          *(_BYTE *)(v67 + v70 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 1) = v68;
          *(_BYTE *)(v67 + v70 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 2) = v69;
          v70 += 3;
        }
        v67 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
      }
      *(_BYTE *)(this + 8) |= 8u;
      goto LABEL_93;
    }
    if ( active >= 64 )
    {
      v41 = 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4) * *(_DWORD *)(this + 20);
      for ( k = 0; k < *(_DWORD *)(this + 28); ++k )
      {
        v42 = 3 * *(_DWORD *)(this + 16);
        for ( m = 0; m < *(_DWORD *)(this + 24); ++m )
        {
          *(_BYTE *)(v41 + v42 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12)) = -1;
          *(_BYTE *)(v41 + v42 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 1) = 0;
          *(_BYTE *)(v41 + v42 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12) + 2) = -1;
          v42 += 3;
        }
        v41 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
      }
      *(_BYTE *)(this + 8) |= 8u;
LABEL_93:
      rf_light_clear_active_world_list();
      goto LABEL_94;
    }
    if ( *(_DWORD *)(this + 104) == -1
      || (v56 = *(_BYTE **)sub_552200((_DWORD *)(a2 + 144), *(_DWORD *)(this + 104)), v56[69] != 1) )
    {
      rf_light_get_ambient_rgb_floats(&v57, &v61, &v62);
    }
    else
    {
      v57 = (double)(unsigned __int8)v56[70] * 0.003921568859368563;
      v61 = (double)(unsigned __int8)v56[71] * 0.003921568859368563;
      v62 = (double)(unsigned __int8)v56[72] * 0.003921568859368563;
    }
    v58 = unk_1566B20;
    v59 = unk_14A6B20;
    v60 = unk_14E6B20;
    for ( n = 0; n < *(_DWORD *)(this + 28); ++n )
    {
      for ( ii = 0; ii < *(_DWORD *)(this + 24); ++ii )
      {
        *v58++ = v57 * 0.5;
        *v59++ = v61 * 0.5;
        *v60++ = v62 * 0.5;
      }
    }
    for ( jj = 0; ; ++jj )
    {
      first_dword = rf_receiver_get_first_dword(&unk_D4C548);
      if ( jj >= first_dword )
        break;
      v10 = *(void **)sub_552200(&unk_D4C548, jj);
      operator delete(v10);
    }
    rf_pointer_array_release_storage((void **)&unk_D4C548);
    v63 = 0;
    if ( !a3 )
    {
      v63 = 1;
LABEL_54:
      if ( v63 )
      {
        if ( active && a3 )
          rf_lightmap_accumulate_float_rgb_samples(a2, this, 0, (int)&off_663D50);
        else
          rf_lightmap_accumulate_float_rgb_samples(a2, this, 0, 0);
        v52 = 3 * *(_DWORD *)(this + 16) + 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4) * *(_DWORD *)(this + 20);
        v51 = 0;
        if ( *(int *)(this + 24) <= 8 || *(int *)(this + 28) <= 8 )
        {
          for ( kk = 0; kk < *(_DWORD *)(this + 28); ++kk )
          {
            v46 = (_BYTE *)(v52 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12));
            for ( mm = 0; mm < *(_DWORD *)(this + 24); ++mm )
            {
              rf_lightmap_rgb_float_texel_to_bytes(mm + v51, v46);
              v46 += 3;
            }
            v52 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
            v51 += *(_DWORD *)(this + 24);
          }
        }
        else
        {
          for ( nn = 0; nn < *(_DWORD *)(this + 28); ++nn )
          {
            v48 = (_BYTE *)(v52 + *(_DWORD *)(*(_DWORD *)(this + 12) + 12));
            if ( nn >= 2 && nn <= *(_DWORD *)(this + 28) - 3 )
            {
              for ( i1 = 0; i1 < *(_DWORD *)(this + 24); ++i1 )
              {
                if ( i1 >= 2 && i1 <= *(_DWORD *)(this + 24) - 3 )
                {
                  rf_lightmap_rgb_filtered_texel_to_bytes(i1, nn, *(_DWORD *)(this + 24), *(_DWORD *)(this + 28), v48);
                  v48 += 3;
                }
                else
                {
                  rf_lightmap_rgb_float_texel_to_bytes(i1 + v51, v48);
                  v48 += 3;
                }
              }
            }
            else
            {
              for ( i1 = 0; i1 < *(_DWORD *)(this + 24); ++i1 )
              {
                rf_lightmap_rgb_float_texel_to_bytes(i1 + v51, v48);
                v48 += 3;
              }
            }
            v52 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
            v51 += *(_DWORD *)(this + 24);
          }
        }
        *(_BYTE *)(this + 8) |= 8u;
      }
      goto LABEL_93;
    }
    for ( jj = 0; ; ++jj )
    {
      if ( jj >= active )
        goto LABEL_54;
      active_world_record_unchecked = (int)rf_light_get_active_world_record_unchecked(jj);
      memset(*(&off_663D50 + jj), 255, *(_DWORD *)(this + 28) * *(_DWORD *)(this + 24));
      if ( !*(_DWORD *)(active_world_record_unchecked + 80) )
      {
        v63 = 1;
        continue;
      }
      if ( (*(_BYTE *)(this + 8) & 2) != 0 )
      {
        if ( a3 == 1 )
          goto LABEL_42;
        if ( a3 == 2 )
        {
          rf_lightmap_build_shadow_mask_by_face_rays(
            a2,
            this,
            active_world_record_unchecked,
            0,
            (char *)*(&off_663D50 + jj));
          v63 = 1;
        }
      }
      else if ( (*(_BYTE *)(this + 8) & 4) != 0 && *(_DWORD *)(active_world_record_unchecked + 80) == 2 )
      {
        if ( a3 == 1 )
        {
LABEL_42:
          rf_lightmap_build_projected_occluder_shadow_mask(
            a2,
            this,
            active_world_record_unchecked,
            0,
            (char *)*(&off_663D50 + jj));
          v63 = 1;
          continue;
        }
        if ( a3 == 2 )
        {
          rf_lightmap_build_shadow_mask_by_face_rays(
            a2,
            this,
            active_world_record_unchecked,
            0,
            (char *)*(&off_663D50 + jj));
          v63 = 1;
        }
      }
    }
  }
LABEL_94:
  if ( (*(_BYTE *)(this + 8) & 1) != 0 )
  {
    v38 = 0;
    if ( *(_DWORD *)(this + 104) != -1 )
      v38 = *(_DWORD *)sub_552200((_DWORD *)(a2 + 144), *(_DWORD *)(this + 104));
    active_list_context_byte = rf_light_get_active_list_context_byte();
    v40 = 1;
    if ( !active_list_context_byte )
      v40 = rf_light_build_active_list_for_aabb_query(v38, (float *)(this + 52), (float *)(this + 64), 1, 0);
    rf_light_sync_active_receiver_space_if_enabled();
    if ( v40 )
    {
      v37 = *(_DWORD *)(this + 12);
      if ( v37 && rf_bitmap_lock_pixels_backend_dispatch(*(_DWORD *)(v37 + 16), 0, (int)v36, 1) )
      {
        v34 = v36[3];
        v31 = 1.0 / (double)*(int *)(*(_DWORD *)(this + 12) + 4);
        v30 = 1.0 / (double)*(int *)(*(_DWORD *)(this + 12) + 8);
        v32 = 1.0 / *(float *)(this + 76);
        v33 = 1.0 / *(float *)(this + 80);
        v35 = 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4) * *(_DWORD *)(this + 20);
        v29 = 0;
        while ( v29 < *(_DWORD *)(this + 28) )
        {
          v27 = *(_DWORD *)(this + 20) + v29;
          v26 = v34 + 2 * (v27 * ((signed int)v36[6] / 2) + *(_DWORD *)(this + 16));
          v25 = ((double)v27 + 0.5) * v30;
          v25 = v25 - *(float *)(this + 88);
          v25 = v25 * v33;
          v28 = 3 * *(_DWORD *)(this + 16);
          v24 = 0;
          while ( v24 < *(_DWORD *)(this + 24) )
          {
            v22 = *(_DWORD *)(this + 16) + v24;
            *(float *)&v21[1] = ((double)v22 + 0.5) * v31;
            *(float *)&v21[1] = *(float *)&v21[1] - *(float *)(this + 84);
            *(float *)&v21[1] = *(float *)&v21[1] * v32;
            rf_vector3_default_construct_noop(v18);
            ((void (__thiscall *)(int, _DWORD, _DWORD, int *))unk_1425E98[4 * *(_DWORD *)(this + 92)])(
              unk_1425E9C[4 * *(_DWORD *)(this + 92)] + this,
              *(_DWORD *)&v21[1],
              LODWORD(v25),
              v18);
            rf_renderer_compute_nonworld_diffuse_rgb8(
              v19,
              v21,
              (_BYTE *)v21 + 1,
              0,
              (float *)v18,
              (float *)(this + 108),
              -1.0);
            *(_DWORD *)&v19[1] = *(unsigned __int8 *)(*(_DWORD *)(*(_DWORD *)(this + 12) + 12) + v28 + v35);
            v23 = *(unsigned __int8 *)(*(_DWORD *)(*(_DWORD *)(this + 12) + 12) + v28 + v35 + 1);
            v20 = *(unsigned __int8 *)(*(_DWORD *)(*(_DWORD *)(this + 12) + 12) + v28 + v35 + 2);
            *(_DWORD *)&v19[1] += v19[0];
            v23 += LOBYTE(v21[0]);
            v20 += HIBYTE(v21[0]);
            *(int *)&v19[1] >>= 3;
            v23 >>= 3;
            v20 >>= 3;
            if ( *(int *)&v19[1] <= 31 )
              v8 = *(_DWORD *)&v19[1];
            else
              v8 = 31;
            *(_DWORD *)&v19[1] = v8;
            if ( v23 <= 31 )
              v7 = v23;
            else
              v7 = 31;
            v23 = v7;
            if ( v20 <= 31 )
              v6 = v20;
            else
              v6 = 31;
            v20 = v6;
            *(_WORD *)(v26 + 2 * v24++) = v6 | (32 * v23) | (*(_WORD *)&v19[1] << 10) | 0x8000;
            v28 += 3;
          }
          ++v29;
          v35 += 3 * *(_DWORD *)(*(_DWORD *)(this + 12) + 4);
        }
        *(_BYTE *)(this + 8) &= ~8u;
        rf_bitmap_unlock_pixels_backend_dispatch(v36);
      }
    }
    else
    {
      *(_BYTE *)(this + 8) |= 8u;
    }
    if ( !active_list_context_byte )
      rf_light_clear_active_world_list();
  }
  LOBYTE(v3) = this;
  if ( (*(_BYTE *)(this + 8) & 8) != 0 )
  {
    v3 = *(_DWORD **)(this + 12);
    v17 = v3;
    if ( v3 )
    {
      LOBYTE(v3) = rf_bitmap_lock_pixels_backend_dispatch(v17[4], 0, (int)v15, 1);
      if ( (_BYTE)v3 )
      {
        v12 = 3 * *(_DWORD *)(this + 16) + 3 * v17[1] * *(_DWORD *)(this + 20) + v17[3];
        v13 = v15[3] + 2 * (*(_DWORD *)(this + 16) + *(_DWORD *)(this + 20) * (v16 / 2));
        for ( i2 = 0; i2 < *(_DWORD *)(this + 28); ++i2 )
        {
          for ( i3 = 0; i3 < *(_DWORD *)(this + 24); ++i3 )
            *(_WORD *)(v13 + 2 * i3) = (*(_BYTE *)(3 * i3 + v12 + 2) >> 3)
                                     | (32 * (*(_BYTE *)(3 * i3 + v12 + 1) >> 3))
                                     | (*(_BYTE *)(3 * i3 + v12) >> 3 << 10)
                                     | 0x8000;
          v12 += 3 * v17[1];
          v13 += 2 * (v16 / 2);
        }
        LOBYTE(v3) = rf_bitmap_unlock_pixels_backend_dispatch(v15);
      }
    }
  }
  *(_BYTE *)(this + 8) = 0;
  return (char)v3;
}

