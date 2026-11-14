// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F6790 rf_ui_staticbox_draw
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Hidden returns. Absolute position;blocked palette904+12,image940,else palette904,image908. Image draw helper gets stored drawW884/H888,cropX892/Y896;when it returns0,fills full gadget w20/h24 with palette firstRGBA. Nonempty text628 measured with font900,adjusted height-=fontHeight-metric58c0e0-1. Explicit text x980/y984>=0 override alignment as absolute origin+offset. Negative x uses hjustify972:0/other left,1center,2right;negative y uses vjustify976:0top,2bottom,othercenter. Selected12-byte palette block:background0,text4,shadow8(alpha11);optional shadow+1,+1 thenforeground. No initial clip reset before image/fallback;image helper may reset clip depending crop. Finally resets clip and calls draw-children-and-event2. No text wrapping,bitmap scaling,resource release or state restore;return
// incidental predicate/child helper.
int __thiscall rf_ui_staticbox_draw(int this)
{
  int result; // eax
  int height_select_current; // esi
  int spacing_select_current; // eax
  int v4; // esi
  int v5; // eax
  int v6; // [esp+4h] [ebp-60h]
  int v7; // [esp+8h] [ebp-5Ch]
  int v8; // [esp+1Ch] [ebp-48h]
  int v9; // [esp+20h] [ebp-44h]
  int v11; // [esp+38h] [ebp-2Ch]
  int v12; // [esp+3Ch] [ebp-28h] BYREF
  int v13; // [esp+40h] [ebp-24h] BYREF
  int v14; // [esp+44h] [ebp-20h]
  int v15; // [esp+48h] [ebp-1Ch]
  int v16; // [esp+4Ch] [ebp-18h] BYREF
  int v17; // [esp+50h] [ebp-14h] BYREF
  int v18; // [esp+54h] [ebp-10h]
  unsigned __int8 *v19; // [esp+58h] [ebp-Ch]
  int v20; // [esp+5Ch] [ebp-8h]
  int v21; // [esp+60h] [ebp-4h]

  result = (*(int (__thiscall **)(int))(*(_DWORD *)this + 16))(this);
  if ( !(_BYTE)result )
  {
    v20 = rf_ui_gadget_absolute_x((_DWORD *)this, 0);
    v21 = rf_ui_gadget_absolute_y((_DWORD *)this, 0);
    if ( rf_ui_gadget_is_interaction_blocked((_DWORD *)this) )
    {
      v19 = (unsigned __int8 *)(*(_DWORD *)(this + 904) + 12);
      if ( !rf_ui_state_image_draw(
              (int *)(this + 940),
              v20,
              v21,
              *(_DWORD *)(this + 884),
              *(_DWORD *)(this + 888),
              *(_DWORD *)(this + 892),
              *(_DWORD *)(this + 896)) )
      {
        rf_render_color_set_packed_rgba8(v19);
        rf_renderer_fill_rectangle_clipped(v20, v21, *(_DWORD *)(this + 20), *(_DWORD *)(this + 24), dword_182ABB8);
      }
      if ( this + 628 + strlen((const char *)(this + 628)) + 1 != this + 629 )
      {
        rf_font_measure_text_extent(&v16, &v17, (unsigned __int8 *)(this + 628), -1, *(_DWORD *)(this + 900));
        height_select_current = rf_font_get_height_select_current(*(_DWORD *)(this + 900));
        spacing_select_current = rf_font_get_spacing_select_current(*(_DWORD *)(this + 900));
        v17 -= height_select_current - spacing_select_current - 1;
        if ( *(int *)(this + 980) < 0 )
        {
          v9 = *(_DWORD *)(this + 972);
          if ( v9 == 1 )
          {
            v18 = v20 + *(_DWORD *)(this + 20) / 2 - v16 / 2;
          }
          else if ( v9 == 2 )
          {
            v18 = *(_DWORD *)(this + 20) + v20 - v16;
          }
          else
          {
            v18 = v20;
          }
        }
        else
        {
          v18 = *(_DWORD *)(this + 980) + v20;
        }
        if ( *(int *)(this + 984) < 0 )
        {
          v8 = *(_DWORD *)(this + 976);
          if ( v8 )
          {
            if ( v8 == 2 )
              v15 = *(_DWORD *)(this + 24) + v21 - v17;
            else
              v15 = v21 + *(_DWORD *)(this + 24) / 2 - v17 / 2;
          }
          else
          {
            v15 = v21;
          }
        }
        else
        {
          v15 = *(_DWORD *)(this + 984) + v21;
        }
        if ( v19[11] )
        {
          rf_render_color_set_packed_rgba8(v19 + 8);
          rf_font_draw_text_screen(
            v18 + 1,
            v15 + 1,
            (unsigned __int8 *)(this + 628),
            *(_DWORD *)(this + 900),
            dword_182ABBC);
        }
        rf_render_color_set_packed_rgba8(v19 + 4);
        rf_font_draw_text_screen(v18, v15, (unsigned __int8 *)(this + 628), *(_DWORD *)(this + 900), dword_182ABBC);
      }
    }
    else
    {
      v19 = *(unsigned __int8 **)(this + 904);
      if ( !rf_ui_state_image_draw(
              (int *)(this + 908),
              v20,
              v21,
              *(_DWORD *)(this + 884),
              *(_DWORD *)(this + 888),
              *(_DWORD *)(this + 892),
              *(_DWORD *)(this + 896)) )
      {
        rf_render_color_set_packed_rgba8(v19);
        rf_renderer_fill_rectangle_clipped(v20, v21, *(_DWORD *)(this + 20), *(_DWORD *)(this + 24), dword_182ABB8);
      }
      if ( this + 628 + strlen((const char *)(this + 628)) + 1 != this + 629 )
      {
        rf_font_measure_text_extent(&v12, &v13, (unsigned __int8 *)(this + 628), -1, *(_DWORD *)(this + 900));
        v4 = rf_font_get_height_select_current(*(_DWORD *)(this + 900));
        v5 = rf_font_get_spacing_select_current(*(_DWORD *)(this + 900));
        v13 -= v4 - v5 - 1;
        if ( *(int *)(this + 980) < 0 )
        {
          v7 = *(_DWORD *)(this + 972);
          if ( v7 == 1 )
          {
            v14 = v20 + *(_DWORD *)(this + 20) / 2 - v12 / 2;
          }
          else if ( v7 == 2 )
          {
            v14 = *(_DWORD *)(this + 20) + v20 - v12;
          }
          else
          {
            v14 = v20;
          }
        }
        else
        {
          v14 = *(_DWORD *)(this + 980) + v20;
        }
        if ( *(int *)(this + 984) < 0 )
        {
          v6 = *(_DWORD *)(this + 976);
          if ( v6 )
          {
            if ( v6 == 2 )
              v11 = *(_DWORD *)(this + 24) + v21 - v13;
            else
              v11 = v21 + *(_DWORD *)(this + 24) / 2 - v13 / 2;
          }
          else
          {
            v11 = v21;
          }
        }
        else
        {
          v11 = *(_DWORD *)(this + 984) + v21;
        }
        if ( v19[11] )
        {
          rf_render_color_set_packed_rgba8(v19 + 8);
          rf_font_draw_text_screen(
            v14 + 1,
            v11 + 1,
            (unsigned __int8 *)(this + 628),
            *(_DWORD *)(this + 900),
            dword_182ABBC);
        }
        rf_render_color_set_packed_rgba8(v19 + 4);
        rf_font_draw_text_screen(v14, v11, (unsigned __int8 *)(this + 628), *(_DWORD *)(this + 900), dword_182ABBC);
      }
    }
    rf_renderer_reset_viewport_full_screen();
    return rf_ui_gadget_draw_children_and_notify((_DWORD *)this);
  }
  return result;
}

