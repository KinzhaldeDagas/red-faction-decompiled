// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F24E0 rf_ui_checkbox_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Computes absolute x/y,then skips hidden predicate. Resets clip. Palette912 contains four16-byte blocks:normal0,highlighted16,pressed32,disabled48;block fields face0,check-line4,text8,shadow12. Blocked:draw disabled bitmap928 when>=0,else solid disabled face WITHOUT check cross,then disabled text/shadow. Visual908==1 selects checked920 or unchecked916 with normal face/check colors but highlighted text/shadow. Visual2 uses pressed924 if>=0,else pressed face plus X iff checked. Other visual values use normal checked/unchecked bitmap/fallback and normal text. Bitmap draw is white,unscaled;fallback check is two diagonals over box632/636. Label640 at(x+boxW+offset900,y+offset904),font896;shadow at+1,+1 only palette alpha15 of selected block. No child drawing,events,bitmap release or render state
// restore;return incidental final draw/predicate result.
int __thiscall rf_ui_checkbox_draw(int this)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  float v8; // [esp+0h] [ebp-50h]
  float v9; // [esp+0h] [ebp-50h]
  float v10; // [esp+0h] [ebp-50h]
  float v11; // [esp+0h] [ebp-50h]
  float v12; // [esp+0h] [ebp-50h]
  float v13; // [esp+0h] [ebp-50h]
  float v14; // [esp+4h] [ebp-4Ch]
  float v15; // [esp+4h] [ebp-4Ch]
  float v16; // [esp+4h] [ebp-4Ch]
  float v17; // [esp+4h] [ebp-4Ch]
  float v18; // [esp+4h] [ebp-4Ch]
  float v19; // [esp+4h] [ebp-4Ch]
  float v20; // [esp+8h] [ebp-48h]
  float v21; // [esp+8h] [ebp-48h]
  float v22; // [esp+8h] [ebp-48h]
  float v23; // [esp+8h] [ebp-48h]
  float v24; // [esp+8h] [ebp-48h]
  float v25; // [esp+8h] [ebp-48h]
  int v26; // [esp+Ch] [ebp-44h]
  int v27; // [esp+Ch] [ebp-44h]
  float v28; // [esp+Ch] [ebp-44h]
  float v29; // [esp+Ch] [ebp-44h]
  int v30; // [esp+Ch] [ebp-44h]
  int v31; // [esp+Ch] [ebp-44h]
  float v32; // [esp+Ch] [ebp-44h]
  float v33; // [esp+Ch] [ebp-44h]
  int v34; // [esp+Ch] [ebp-44h]
  float v35; // [esp+Ch] [ebp-44h]
  float v36; // [esp+Ch] [ebp-44h]
  int v37; // [esp+Ch] [ebp-44h]
  int v38; // [esp+10h] [ebp-40h]
  int v39; // [esp+10h] [ebp-40h]
  int v40; // [esp+10h] [ebp-40h]
  int v41; // [esp+10h] [ebp-40h]
  int v42; // [esp+10h] [ebp-40h]
  int v43; // [esp+10h] [ebp-40h]
  int v45; // [esp+48h] [ebp-8h]
  int v46; // [esp+4Ch] [ebp-4h]

  v45 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
  v46 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
  result = (*(int (__thiscall **)(int))(*(_DWORD *)this + 16))(this);
  if ( !(_BYTE)result )
  {
    rf_renderer_reset_viewport_full_screen();
    if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
    {
      if ( *(int *)(this + 928) < 0 )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 48));
        rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v38 = unk_187CD38;
        v26 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v2 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 928), v2, v26, v38);
      }
      if ( *(_BYTE *)(*(_DWORD *)(this + 912) + 63) )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 60));
        rf_font_draw_text_screen(
          *(_DWORD *)(this + 632) + v45 + *(_DWORD *)(this + 900) + 1,
          v46 + *(_DWORD *)(this + 904) + 1,
          (unsigned __int8 *)(this + 640),
          *(_DWORD *)(this + 896),
          dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 56));
      return rf_font_draw_text_screen(
               *(_DWORD *)(this + 900) + *(_DWORD *)(this + 632) + v45,
               *(_DWORD *)(this + 904) + v46,
               (unsigned __int8 *)(this + 640),
               *(_DWORD *)(this + 896),
               dword_182ABBC);
    }
    else if ( *(_DWORD *)(this + 908) == 1 )
    {
      if ( *(_BYTE *)(this + 628) )
      {
        if ( *(int *)(this + 920) < 0 )
        {
          rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 912));
          rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 4));
          v28 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v20 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          v14 = (float)v46;
          v8 = (float)v45;
          rf_renderer_draw_screen_line_clipped(v8, v14, v20, v28, dword_187CC5C);
          v29 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v21 = (float)v45;
          v15 = (float)v46;
          v9 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          rf_renderer_draw_screen_line_clipped(v9, v15, v21, v29, dword_187CC5C);
        }
        else
        {
          rf_render_color_set_rgba8(255, 255, 255, 255);
          v39 = unk_187CD38;
          v27 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
          v3 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
          rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 920), v3, v27, v39);
        }
      }
      else if ( *(int *)(this + 916) < 0 )
      {
        rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 912));
        rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v40 = unk_187CD38;
        v30 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v4 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 916), v4, v30, v40);
      }
      if ( *(_BYTE *)(*(_DWORD *)(this + 912) + 31) )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 28));
        rf_font_draw_text_screen(
          *(_DWORD *)(this + 632) + v45 + *(_DWORD *)(this + 900) + 1,
          v46 + *(_DWORD *)(this + 904) + 1,
          (unsigned __int8 *)(this + 640),
          *(_DWORD *)(this + 896),
          dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 24));
      return rf_font_draw_text_screen(
               *(_DWORD *)(this + 900) + *(_DWORD *)(this + 632) + v45,
               *(_DWORD *)(this + 904) + v46,
               (unsigned __int8 *)(this + 640),
               *(_DWORD *)(this + 896),
               dword_182ABBC);
    }
    else if ( *(_DWORD *)(this + 908) == 2 )
    {
      if ( *(int *)(this + 924) < 0 )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 32));
        rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
        if ( *(_BYTE *)(this + 628) )
        {
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 36));
          v32 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v22 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          v16 = (float)v46;
          v10 = (float)v45;
          rf_renderer_draw_screen_line_clipped(v10, v16, v22, v32, dword_187CC5C);
          v33 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v23 = (float)v45;
          v17 = (float)v46;
          v11 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          rf_renderer_draw_screen_line_clipped(v11, v17, v23, v33, dword_187CC5C);
        }
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v41 = unk_187CD38;
        v31 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v5 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 924), v5, v31, v41);
      }
      if ( *(_BYTE *)(*(_DWORD *)(this + 912) + 47) )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 44));
        rf_font_draw_text_screen(
          *(_DWORD *)(this + 632) + v45 + *(_DWORD *)(this + 900) + 1,
          v46 + *(_DWORD *)(this + 904) + 1,
          (unsigned __int8 *)(this + 640),
          *(_DWORD *)(this + 896),
          dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 40));
      return rf_font_draw_text_screen(
               *(_DWORD *)(this + 900) + *(_DWORD *)(this + 632) + v45,
               *(_DWORD *)(this + 904) + v46,
               (unsigned __int8 *)(this + 640),
               *(_DWORD *)(this + 896),
               dword_182ABBC);
    }
    else
    {
      if ( *(_BYTE *)(this + 628) )
      {
        if ( *(int *)(this + 920) < 0 )
        {
          rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 912));
          rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
          rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 4));
          v35 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v24 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          v18 = (float)v46;
          v12 = (float)v45;
          rf_renderer_draw_screen_line_clipped(v12, v18, v24, v35, dword_187CC5C);
          v36 = (float)(v46 + *(_DWORD *)(this + 636) - 1);
          v25 = (float)v45;
          v19 = (float)v46;
          v13 = (float)(v45 + *(_DWORD *)(this + 632) - 1);
          rf_renderer_draw_screen_line_clipped(v13, v19, v25, v36, dword_187CC5C);
        }
        else
        {
          rf_render_color_set_rgba8(255, 255, 255, 255);
          v42 = unk_187CD38;
          v34 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
          v6 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
          rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 920), v6, v34, v42);
        }
      }
      else if ( *(int *)(this + 916) < 0 )
      {
        rf_render_color_set_packed_rgba8(*(unsigned __int8 **)(this + 912));
        rf_renderer_fill_rectangle_clipped(v45, v46, *(_DWORD *)(this + 632), *(_DWORD *)(this + 636), dword_182ABB8);
      }
      else
      {
        rf_render_color_set_rgba8(255, 255, 255, 255);
        v43 = unk_187CD38;
        v37 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
        v7 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
        rf_bitmap_draw_unscaled_clipped(*(_DWORD *)(this + 916), v7, v37, v43);
      }
      if ( *(_BYTE *)(*(_DWORD *)(this + 912) + 15) )
      {
        rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 12));
        rf_font_draw_text_screen(
          *(_DWORD *)(this + 632) + v45 + *(_DWORD *)(this + 900) + 1,
          v46 + *(_DWORD *)(this + 904) + 1,
          (unsigned __int8 *)(this + 640),
          *(_DWORD *)(this + 896),
          dword_182ABBC);
      }
      rf_render_color_set_packed_rgba8((unsigned __int8 *)(*(_DWORD *)(this + 912) + 8));
      return rf_font_draw_text_screen(
               *(_DWORD *)(this + 900) + *(_DWORD *)(this + 632) + v45,
               *(_DWORD *)(this + 904) + v46,
               (unsigned __int8 *)(this + 640),
               *(_DWORD *)(this + 896),
               dword_182ABBC);
    }
  }
  return result;
}

