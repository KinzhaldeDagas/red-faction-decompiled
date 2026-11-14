// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DEEA0 rf_renderer_draw_cached_face_select_single_or_multipass
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments solidcontext,face,wireoverlaybyte. Lazily initializes4packedstates. Per circularcornervertex,if vertexDWORDstamp+24<solidstamp+860,updatesstamp,transformsworldXYZ via0x5817B0,caches cameraXYZ at+12 and outcodeDWORD+28. Accumulates AND/OR; nonzeroAND skipsdraw. Lazily loads fallback blahblah.tga via0x574E90; uses facebitmap+48 whennonnegative and resolvedlightmapbitmap for signedindex+54>=0. Sets auxiliarymode0. If debugglobals0xA4208C/90/A0 OR nolightmap,chooses singleface0x5D4390; debug8Cusesgrayalpha63,stateuntextured; debug90derivesRGBfromowner+32 bitmasks*43 modulo256 withdarkfallback48,ownerabsentgray127; otherwise white. Else invokes multipass0x5D49F0 withbase/lightmap. On backendresultnonzero increments0xA4205C and sets faceflag0x80000000. Backend0x5D49F0 may independently reject gate0x92DE28. Optionalwireoverlaybuilds25
// localclipvertices from originalworldpositions,sets currentcolorblack,and draws closededges even when fillsubmissionfailed. No cornercount<=25 guard or fallbackloadfailure check. Returnbyte varies byloops/pointers,not reliable success; cachedtransform invalidation controlledbysolidstamp.
char __usercall rf_renderer_draw_cached_face_select_single_or_multipass@<al>(double a1@<st0>, int a2, int a3, char a4)
{
  int v4; // eax
  unsigned __int8 v5; // al
  int v7; // [esp+4h] [ebp-540h]
  int v8; // [esp+Ch] [ebp-538h]
  float copy_result[3]; // [esp+10h] [ebp-534h] BYREF
  int k; // [esp+1Ch] [ebp-528h]
  int j; // [esp+20h] [ebp-524h]
  int v12; // [esp+24h] [ebp-520h]
  char v13[1204]; // [esp+28h] [ebp-51Ch] BYREF
  int v14; // [esp+4DCh] [ebp-68h]
  int v15; // [esp+4E0h] [ebp-64h]
  int v16; // [esp+4E4h] [ebp-60h]
  char v17; // [esp+4EBh] [ebp-59h]
  int v18; // [esp+4ECh] [ebp-58h]
  int v19; // [esp+4F0h] [ebp-54h]
  float source[12]; // [esp+4F4h] [ebp-50h] BYREF
  float *v21; // [esp+524h] [ebp-20h]
  int i; // [esp+528h] [ebp-1Ch]
  int v23; // [esp+52Ch] [ebp-18h]
  int *v24; // [esp+530h] [ebp-14h]
  int v25; // [esp+534h] [ebp-10h]
  int v26; // [esp+540h] [ebp-4h]

  v23 = -1;
  v25 = 0;
  if ( (dword_1E01544 & 1) == 0 )
  {
    dword_1E01544 |= 1u;
    rf_render_state_pack(&dword_1E01540, 5, 1, 2, 3, 4, 0);
    v26 = -1;
  }
  if ( (dword_1E01544 & 2) == 0 )
  {
    dword_1E01544 |= 2u;
    rf_render_state_pack(&dword_1E0153C, 1, 1, 2, 3, 4, 0);
    v26 = -1;
  }
  if ( (dword_1E01544 & 4) == 0 )
  {
    dword_1E01544 |= 4u;
    rf_render_state_pack(&dword_1E01538, 0, 0, 0, 3, 0, 0);
    v26 = -1;
  }
  if ( (dword_1E01544 & 8) == 0 )
  {
    dword_1E01544 |= 8u;
    rf_render_state_pack(&dword_1E01534, 0, 0, 0, 0, 4, 0);
    v26 = -1;
  }
  v4 = *(_DWORD *)(a3 + 64);
  for ( i = v4; i; i = v8 )
  {
    v21 = *(float **)i;
    if ( *((_DWORD *)v21 + 6) < *(_DWORD *)(a2 + 860) )
    {
      v21[6] = *(float *)(a2 + 860);
      rf_vector_prefix_construct_noop(source);
      v5 = rf_renderer_transform_world_point_backend_wrapper((int)source, v21);
      *((_DWORD *)v21 + 7) = v5;
      rf_vector_copy(v21 + 3, copy_result, source);
    }
    v23 &= *((_DWORD *)v21 + 7);
    v25 |= *((_DWORD *)v21 + 7);
    LOBYTE(v4) = a3;
    if ( *(_DWORD *)(i + 20) == *(_DWORD *)(a3 + 64) )
    {
      v8 = 0;
    }
    else
    {
      v4 = *(_DWORD *)(i + 20);
      v8 = v4;
    }
  }
  if ( !v23 )
  {
    if ( dword_664A50 == -1 )
      dword_664A50 = rf_bitmap_load_with_optional_mipmap_generation("blahblah.tga", (void *)0xFFFFFFFF, 1);
    v18 = dword_664A50;
    v19 = -1;
    if ( *(int *)(a3 + 48) > -1 )
      v18 = *(_DWORD *)(a3 + 48);
    if ( *(__int16 *)(a3 + 54) > -1 )
      v19 = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(a2 + 192), *(__int16 *)(a3 + 54)) + 12) + 16);
    rf_renderer_set_auxiliary_mode_clamped_0_16(0);
    if ( dword_A4208C || dword_A42090 || dword_A420A0 || v19 == -1 )
    {
      if ( dword_A4208C )
      {
        rf_render_color_set_rgba8(127, 127, 127, 63);
        v24 = &dword_1E01538;
      }
      else if ( dword_A42090 )
      {
        if ( *(_DWORD *)(a3 + 68) )
        {
          v14 = *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 1;
          v15 = *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 2;
          v16 = *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 4;
          v14 += *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 8;
          v15 += *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 0x10;
          v16 += *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 0x20;
          v14 += *(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 0x40;
          LOBYTE(v15) = v15 + (*(_DWORD *)(*(_DWORD *)(a3 + 68) + 32) & 0x80);
          LOBYTE(v14) = 43 * v14;
          LOBYTE(v15) = 43 * v15;
          LOBYTE(v16) = 43 * v16;
          v14 = (unsigned __int8)v14;
          v15 = (unsigned __int8)v15;
          v16 = (unsigned __int8)v16;
          if ( (unsigned __int8)v16 + (unsigned __int8)v15 + (unsigned __int8)v14 <= 16 )
          {
            v14 = 48;
            v15 = 48;
            v16 = 48;
          }
        }
        else
        {
          v16 = 127;
          v15 = 127;
          v14 = 127;
        }
        rf_render_color_set_rgba8(v14, v15, v16, 255);
        v24 = &dword_1E01534;
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v24 = &dword_1E0153C;
      }
      LOBYTE(v4) = rf_renderer_draw_single_face_backend_102(a2, a3, *v24, v18, v25);
      v17 = v4;
    }
    else
    {
      LOBYTE(v4) = rf_renderer_draw_face_multipass_backend_102(a2, (float *)a3, dword_1E01540, v18, v19, v25);
      v17 = v4;
    }
    if ( v17 )
    {
      ++*(_DWORD *)&byte_98967F[756189];
      LOBYTE(v4) = a3;
      *(_DWORD *)(a3 + 40) |= 0x80000000;
    }
    if ( a4 )
    {
      rf_vector_construct_no_unwind(v13, 0x30u, 25, rf_vector_prefix_construct_noop);
      v12 = 0;
      for ( j = *(_DWORD *)(a3 + 64); j; j = v7 )
      {
        rf_renderer_transform_world_point_backend_wrapper((int)&v13[48 * v12++], *(float **)j);
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(a3 + 64) )
          v7 = 0;
        else
          v7 = *(_DWORD *)(j + 20);
      }
      rf_render_color_set_rgba8(0, 0, 0, 255);
      for ( k = 0; ; ++k )
      {
        LOBYTE(v4) = k;
        if ( k >= v12 )
          break;
        rf_renderer_clip_and_draw_projected_line(a1, (int)&v13[48 * k], (int)&v13[48 * ((k + 1) % v12)], dword_182ABA0);
      }
    }
  }
  return v4;
}

