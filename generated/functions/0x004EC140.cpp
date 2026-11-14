// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC140 rf_player_render_scanner_to_capture_bitmap
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, scope/scanner rendering, alt-zoom/lock/custom-action state and x87 duration/native caller ABI): Before player guard, lazily cache F32 reciprocals of squared-distance globals663014(SP)/663010(MP/split), both original defaults900, under guard87FBC4 masks1/2. Later range tests read current globals but intensity uses cached reciprocal. Require nonNULL equal-local player and own entity; lazy load128BlackCircle.tga(-1,0) into66300C, fail-1 exits, resolve dimensions once. Read camera196 pose; calculate projection from player viewport width208/height212: effective height=trunc(H/2) SP orFTOL(H*stored.9) MP/split; F32 t=tan(F32.2617994)*effectiveHeight/W, F32 a=atan(t), F32 FOV=(2a)*180/storedPi. Set viewport0,0,64,64/projection(...,1,1),clear black,set global87C640=player. Iterate entity ring68211C/sentinel681E90 via652:
// inactive rejects, field508 mustEXACT3, frustum sphere(pos60,radius120) mustpass; ORDERED squared camera distance<threshold ->F32 intensity1-distance*cachedReciprocal, playerRGBA4018=(FTOL(intensity*255),0,0,255),call42BD40(entity). Corpses ring681AF8 uses own eligibility/frustum BUT native4EC4FE reads completed ENTITY iterator var_40 (sentinel681E90)+60 for distance, NOT current corpse. Thus all admitted corpses use sentinel-based intensity/range; RGBA=(FTOL(intensity*127),0,same,255),call corpse_render_alpha. No NaN admission, LOS, alive/player exclusion or intensity clamp. Draw black-circle bitmap as four mirrored half-viewport quadrants, white color, capture0,0,64,64 to player bitmap4232. Does not restore viewport/projection/current-player/color itself. ReturnAL incidental/capture residue, not uniform success.
char __cdecl rf_player_render_scanner_to_capture_bitmap(_DWORD *a1)
{
  int v1; // eax
  double v2; // st7
  float v4; // [esp+Ch] [ebp-98h]
  float v5; // [esp+10h] [ebp-94h]
  double v6; // [esp+14h] [ebp-90h]
  float v7; // [esp+1Ch] [ebp-88h]
  float v8; // [esp+20h] [ebp-84h]
  float v9[3]; // [esp+24h] [ebp-80h] BYREF
  float v10; // [esp+30h] [ebp-74h]
  float v11; // [esp+34h] [ebp-70h]
  float v12; // [esp+38h] [ebp-6Ch]
  float out_vector[3]; // [esp+3Ch] [ebp-68h] BYREF
  float v14; // [esp+48h] [ebp-5Ch]
  float rhs[3]; // [esp+4Ch] [ebp-58h] BYREF
  int v16; // [esp+58h] [ebp-4Ch] BYREF
  int v17; // [esp+5Ch] [ebp-48h]
  float v18; // [esp+60h] [ebp-44h]
  int i; // [esp+64h] [ebp-40h]
  int v20; // [esp+68h] [ebp-3Ch]
  int v21; // [esp+6Ch] [ebp-38h]
  int v22; // [esp+70h] [ebp-34h]
  int v23; // [esp+74h] [ebp-30h]
  int v24[9]; // [esp+78h] [ebp-2Ch] BYREF
  int j; // [esp+9Ch] [ebp-8h]
  int v26; // [esp+A0h] [ebp-4h]

  LOBYTE(v1) = dword_87FBC4 & 1;
  if ( (dword_87FBC4 & 1) == 0 )
  {
    dword_87FBC4 |= 1u;
    unk_87FBC0 = 1.0 / flt_663014;
  }
  if ( (dword_87FBC4 & 2) == 0 )
  {
    LOBYTE(v1) = dword_87FBC4 | 2;
    dword_87FBC4 |= 2u;
    unk_87FBBC = 1.0 / flt_663010;
  }
  if ( a1 )
  {
    if ( a1 == (_DWORD *)rf_local_fpgun_player )
    {
      v1 = rf_entity_resolve_handle(a1[5]);
      v26 = v1;
      if ( v1 )
      {
        if ( dword_66300C == -1 )
        {
          v1 = rf_bitmap_load_with_optional_mipmap_generation("128BlackCircle.tga", (void *)0xFFFFFFFF, 0);
          dword_66300C = v1;
          if ( v1 == -1 )
            return v1;
          rf_bitmap_get_resolved_dimensions(dword_66300C, &dword_87FBB4, &dword_87FBB8);
        }
        rf_entity_view_copy_referenced_position(rhs, a1[49]);
        rf_entity_view_copy_referenced_matrix_2016((int)v24, (_DWORD *)a1[49]);
        v21 = a1[52];
        v22 = a1[53];
        if ( rf_splitscreen_runtime_active || rf_multiplayer_runtime_mode )
          v17 = (int)((double)v22 * 0.8999999761581421);
        else
          v17 = v22 / 2;
        v6 = (double)v17;
        v2 = rf_tan_float(0.2617994);
        v5 = v2 * v6 / (double)v21;
        v18 = rf_atan_float_wrapper(v5);
        rf_renderer_set_viewport_and_relative_clip(0, 0, 64, 64);
        v4 = (v18 + v18) * 180.0 / 3.141592741012573;
        rf_renderer_set_camera_projection_dispatch((int)v24, (int)rhs, v4, 1, 1);
        rf_render_color_set_rgba8(0, 0, 0, 255);
        rf_renderer_clear_color_backend_dispatch();
        unk_87C640 = a1;
        for ( i = dword_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
        {
          if ( !rf_object_has_respawn_inactive_flag(i)
            && *(_DWORD *)(i + 508) == 3
            && !rf_frustum_reject_sphere((float *)(i + 60), *(float *)(i + 120)) )
          {
            rf_vector_subtract((const float *)(i + 60), out_vector, rhs);
            v14 = rf_vector_length_squared(out_vector);
            if ( rf_splitscreen_runtime_active || rf_multiplayer_runtime_mode )
            {
              if ( flt_663010 > (double)v14 )
              {
                v11 = 1.0 - v14 * unk_87FBBC;
                rf_color4_set_bytes_return_destination((_BYTE *)a1 + 4018, (int)(v11 * 255.0), 0, 0, 255);
                rf_entity_render_body_and_attachments_with_view_gates(i);
              }
            }
            else if ( flt_663014 > (double)v14 )
            {
              v12 = 1.0 - v14 * unk_87FBC0;
              rf_color4_set_bytes_return_destination((_BYTE *)a1 + 4018, (int)(v12 * 255.0), 0, 0, 255);
              rf_entity_render_body_and_attachments_with_view_gates(i);
            }
          }
        }
        for ( j = rf_corpse_list_head; (_UNKNOWN *)j != &unk_681AF8; j = *(_DWORD *)(j + 652) )
        {
          if ( !rf_object_has_respawn_inactive_flag(j)
            && *(_DWORD *)(j + 508) == 3
            && !rf_frustum_reject_sphere((float *)(j + 60), *(float *)(j + 120)) )
          {
            rf_vector_subtract((const float *)(i + 60), v9, rhs);
            v10 = rf_vector_length_squared(v9);
            if ( rf_splitscreen_runtime_active || rf_multiplayer_runtime_mode )
            {
              if ( flt_663010 > (double)v10 )
              {
                v7 = 1.0 - v10 * unk_87FBBC;
                rf_color4_set_bytes_return_destination((_BYTE *)a1 + 4018, (int)(v7 * 127.0), 0, (int)(v7 * 127.0), 255);
                rf_corpse_render_alpha(j);
              }
            }
            else if ( flt_663014 > (double)v10 )
            {
              v8 = 1.0 - v10 * unk_87FBC0;
              rf_color4_set_bytes_return_destination((_BYTE *)a1 + 4018, (int)(v8 * 127.0), 0, (int)(v8 * 127.0), 255);
              rf_corpse_render_alpha(j);
            }
          }
        }
        v23 = rf_renderer_get_viewport_width() >> 1;
        v20 = rf_renderer_get_viewport_height() >> 1;
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_render_state_pack(&v16, 2, 1, 2, 3, 0, 3);
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_66300C,
          0,
          0,
          v23,
          v20,
          0,
          0,
          dword_87FBB4,
          dword_87FBB8,
          0,
          0,
          v16);
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_66300C,
          v23,
          0,
          v23,
          v20,
          0,
          0,
          dword_87FBB4,
          dword_87FBB8,
          1,
          0,
          v16);
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_66300C,
          0,
          v20,
          v23,
          v20,
          0,
          0,
          dword_87FBB4,
          dword_87FBB8,
          0,
          1,
          v16);
        rf_bitmap_blit_subrectangle_backend_dispatch(
          dword_66300C,
          v23,
          v20,
          v23,
          v20,
          0,
          0,
          dword_87FBB4,
          dword_87FBB8,
          1,
          1,
          v16);
        LOBYTE(v1) = rf_bitmap_capture_backbuffer_into_bitmap(0, 0, 64, 64, a1[1058]);
      }
    }
  }
  return v1;
}

