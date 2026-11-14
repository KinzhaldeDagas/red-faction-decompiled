// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E970 rf_hud_ammo_special_power_render
// UNREALRED VERIFIED [hud-ammo-general] Renders Riot Stick and Flamethrower power ammo. It fills the bar from loaded/clip, formats reserve as ceil(reserve/clip), and emits only that one reserve numeral.
// UNREALRED VERIFIED [hud-status-tint-general] Special power-ammo renderer. Its bar and red/green signal inherit the packed default HUD color; only the ammo icon resets the current color to white.
void __cdecl rf_hud_ammo_special_power_render(int a1, int a2, int a3, char a4)
{
  int v4; // eax
  int v5; // eax
  unsigned __int8 *v6; // eax
  unsigned __int8 *v7; // eax
  unsigned int v8; // [esp-4h] [ebp-C4h]
  int v9; // [esp-4h] [ebp-C4h]
  int v10; // [esp+0h] [ebp-C0h]
  int v11; // [esp+0h] [ebp-C0h]
  _DWORD *v12; // [esp+Ch] [ebp-B4h]
  float v13; // [esp+3Ch] [ebp-84h]
  float v14; // [esp+40h] [ebp-80h]
  float v15; // [esp+44h] [ebp-7Ch]
  float v16; // [esp+50h] [ebp-70h]
  _DWORD v17[8]; // [esp+54h] [ebp-6Ch] BYREF
  int v18; // [esp+74h] [ebp-4Ch]
  int v19; // [esp+78h] [ebp-48h]
  int v20; // [esp+7Ch] [ebp-44h] BYREF
  int viewport_width; // [esp+80h] [ebp-40h] BYREF
  int viewport_height; // [esp+84h] [ebp-3Ch] BYREF
  float v23; // [esp+88h] [ebp-38h]
  int v24; // [esp+8Ch] [ebp-34h]
  int v25; // [esp+90h] [ebp-30h]
  char *v26; // [esp+94h] [ebp-2Ch]
  int v27; // [esp+98h] [ebp-28h]
  int v28; // [esp+9Ch] [ebp-24h]
  int v29; // [esp+A0h] [ebp-20h]
  int v30; // [esp+A4h] [ebp-1Ch]
  const char *v31[2]; // [esp+A8h] [ebp-18h] BYREF
  int v32; // [esp+B0h] [ebp-10h]
  int v33; // [esp+BCh] [ebp-4h]

  v16 = (double)*(int *)(a1 + 4 * dword_912024[340 * a2] + 684) / (double)unk_912088[340 * a2];
  v19 = (int)rf_math_ceil_float(v16);
  v25 = rf_hud_ammo_icon_resolve(a2);
  rf_string_construct_empty(v31);
  v33 = 0;
  v26 = (char *)&rf_weapon_records + 1360 * a2;
  viewport_width = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  rf_render_color_set_packed_rgba8(rf_hud_color_default_rgba);
  if ( a4 )
    rf_render_color_set_alpha8((int)(((double)unk_6EE6C7 * 0.300000011920929 + 0.5) * flt_661888));
  else
    rf_render_color_set_alpha8((int)((double)unk_6EE6C7 * flt_661888));
  rf_bitmap_draw_unscaled_clipped(dword_6618A4, unk_6EDF40, a3 + unk_6EDF44, unk_187CD38);
  if ( *(int *)(a1 + 4 * a2 + 812) <= 0 )
    rf_bitmap_draw_unscaled_clipped(dword_6618F0, unk_6EDF48, a3 + unk_6EDF4C, unk_187CD38);
  else
    rf_bitmap_draw_unscaled_clipped(dword_6618D4, unk_6EDF48, a3 + unk_6EDF4C, unk_187CD38);
  if ( v25 >= 0 )
  {
    rf_render_color_set_rgba8(255, 255, 255, (int)(flt_661888 * 255.0));
    rf_bitmap_draw_unscaled_clipped(v25, unk_6EDF50, unk_6EDF54, unk_187CD38);
  }
  v24 = *(_DWORD *)(a1 + 4 * a2 + 812);
  v27 = *((_DWORD *)v26 + 34);
  v18 = unk_6EDFD0;
  v29 = unk_6EDFD4;
  v30 = unk_6EDFDC;
  v23 = (double)v24 / (double)v27;
  v32 = (int)((double)unk_6EDFD8 * v23);
  rf_rgba8_default_construct_noop(&v20);
  v15 = fabs(v23 - 1.0);
  if ( v15 >= 0.00009999999747378752 )
  {
    v14 = fabs(v23 - 0.5);
    if ( v14 >= 0.00009999999747378752 )
    {
      v13 = fabs(v23 - 0.0);
      if ( v13 >= 0.00009999999747378752 )
      {
        if ( v23 <= 0.5 )
        {
          if ( v23 <= 0.0 )
          {
            v20 = unk_6EE69C;
          }
          else
          {
            HIBYTE(v20) = byte_6EE69E[1];
            v23 = v23 + v23;
            v17[2] = (int)((double)(rf_hud_color_mid_rgba - unk_6EE69C) * v23) + unk_6EE69C;
            v17[3] = (int)((double)(unk_6EE6B5 - unk_6EE69D) * v23) + unk_6EE69D;
            v5 = (int)((double)(unk_6EE6B6 - byte_6EE69E[0]) * v23);
            v17[4] = v5 + byte_6EE69E[0];
            LOBYTE(v20) = (int)((double)(rf_hud_color_mid_rgba - unk_6EE69C) * v23) + unk_6EE69C;
            BYTE1(v20) = (int)((double)(unk_6EE6B5 - unk_6EE69D) * v23) + unk_6EE69D;
            BYTE2(v20) = v5 + byte_6EE69E[0];
          }
        }
        else
        {
          HIBYTE(v20) = unk_6EE6B7;
          v23 = v23 - 0.5;
          v23 = v23 + v23;
          v17[5] = (int)((double)(rf_hud_color_full_rgba - rf_hud_color_mid_rgba) * v23) + rf_hud_color_mid_rgba;
          v17[6] = (int)((double)(unk_6EE6C1 - unk_6EE6B5) * v23) + unk_6EE6B5;
          v4 = (int)((double)(unk_6EE6C2 - unk_6EE6B6) * v23);
          v17[7] = v4 + unk_6EE6B6;
          LOBYTE(v20) = (int)((double)(rf_hud_color_full_rgba - rf_hud_color_mid_rgba) * v23) + rf_hud_color_mid_rgba;
          BYTE1(v20) = (int)((double)(unk_6EE6C1 - unk_6EE6B5) * v23) + unk_6EE6B5;
          BYTE2(v20) = v4 + unk_6EE6B6;
        }
      }
      else
      {
        v20 = unk_6EE69C;
      }
    }
    else
    {
      v20 = rf_hud_color_mid_rgba;
    }
  }
  else
  {
    v20 = rf_hud_color_full_rgba;
  }
  HIBYTE(v20) = 50;
  if ( a4 )
    HIBYTE(v20) = (int)(((double)HIBYTE(v20) * 0.300000011920929 + 0.5) * flt_661888);
  else
    HIBYTE(v20) = (int)((double)HIBYTE(v20) * flt_661888);
  rf_render_color_set_packed_rgba8((unsigned __int8 *)&v20);
  if ( v32 > 0 )
    rf_renderer_fill_rectangle_clipped(v18, v29, v32, v30, dword_182ABB8);
  rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_mid_rgba);
  if ( a4 )
    rf_render_color_set_alpha8((int)(((double)unk_6EE6B7 * 0.300000011920929 + 0.5) * flt_661888));
  else
    rf_render_color_set_alpha8((int)((double)unk_6EE6B7 * flt_661888));
  v12 = rf_string_format_int32_decimal(v17, v19);
  LOBYTE(v33) = 1;
  rf_string_assign_from_object(v31, (int)v12);
  LOBYTE(v33) = 0;
  rf_string_destroy_buffer(v17);
  v10 = dword_661690;
  v8 = rf_string_length_from_cstr(v31);
  v6 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v31);
  rf_font_measure_text_extent(&viewport_width, &viewport_height, v6, v8, v10);
  v28 = unk_6EDF68 + (unk_6EDF70 - viewport_width) / 2;
  v11 = dword_182ABBC;
  v9 = dword_661690;
  v7 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v31);
  rf_font_draw_text_screen(v28, a3 + unk_6EDF6C, v7, v9, v11);
  v33 = -1;
  rf_string_destroy_buffer(v31);
}

