// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B5650 rf_network_bandwidth_overlay_render
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): No arguments. Requires DWORD7B4DDC!=0, local player nonNULL, resolved player entity handle20 nonNULL; resolved entity used only
// as admission gate. Gets default font heightH. Draws black backing with alphaDWORD662D58 (original164) at(firstX-10,firstY-10,firstW,firstH) from662D60/64/68/6C. Four rows use
// shared SIGNED history count1BDB2D8: if count>0 select index count-1 when count<30, else EXACT28 (not29). Pair arrays per row: In=(1BCA398,1BDB260), Out=(1BCA320,1BDB2E0),
// In(r)=(1C0C378,1BDB358), Out(r)=(1BDB1E8,1C0C300), DWORD stride4. Divide each signed sample by FLOAT limit662D5C (original5000), store binary32 fractions. If ORDERED limit<signed32
// pair sum, replace fractions1/0 and both fill colors red; equality/unordered do not trigger. Normal fills(4,176,24,255)/(212,255,9,255), outline(0,246,139,255). Bars call4B5590 with
// firstX,firstY+runningY,firstW-20,H. Regardless count, print white signed pair total (0 if no history) via sprintf local64 and default-font strings In/Out/In (r)/Out (r): N
// bytes/sec. RunningY advances by H for bar/text plus native half/full-line gaps; no reset before reliable rows. Before third row draws SECOND black backing using662D70/74/78/7C, but
// ALL bars/text continue using FIRST geometry origin/width. Original geometries=(10,2,179,70)/(10,74,179,70). No own runtime/server check, divisor-zero guard, sampling/timer
// advancement, UI scaling or history mutation.
void rf_network_bandwidth_overlay_render()
{
  int v0; // [esp+18h] [ebp-BCh]
  int v1; // [esp+20h] [ebp-B4h]
  int v2; // [esp+28h] [ebp-ACh]
  int v3; // [esp+30h] [ebp-A4h]
  int v4; // [esp+34h] [ebp-A0h] BYREF
  int v5; // [esp+38h] [ebp-9Ch]
  __int16 v6; // [esp+3Ch] [ebp-98h] BYREF
  char v7; // [esp+3Eh] [ebp-96h]
  __int16 v8; // [esp+40h] [ebp-94h] BYREF
  char v9; // [esp+42h] [ebp-92h]
  int v10; // [esp+44h] [ebp-90h] BYREF
  int v11; // [esp+48h] [ebp-8Ch]
  __int16 v12; // [esp+4Ch] [ebp-88h] BYREF
  char v13; // [esp+4Eh] [ebp-86h]
  __int16 v14; // [esp+50h] [ebp-84h] BYREF
  char v15; // [esp+52h] [ebp-82h]
  int v16; // [esp+54h] [ebp-80h] BYREF
  int v17; // [esp+58h] [ebp-7Ch]
  __int16 v18; // [esp+5Ch] [ebp-78h] BYREF
  char v19; // [esp+5Eh] [ebp-76h]
  __int16 v20; // [esp+60h] [ebp-74h] BYREF
  char v21; // [esp+62h] [ebp-72h]
  int v22; // [esp+64h] [ebp-70h] BYREF
  int v23; // [esp+68h] [ebp-6Ch]
  __int16 v24; // [esp+6Ch] [ebp-68h] BYREF
  char v25; // [esp+6Eh] [ebp-66h]
  __int16 v26; // [esp+70h] [ebp-64h] BYREF
  char v27; // [esp+72h] [ebp-62h]
  char Buffer[64]; // [esp+74h] [ebp-60h] BYREF
  int v29; // [esp+B8h] [ebp-1Ch]
  int v30; // [esp+BCh] [ebp-18h]
  float v31; // [esp+C0h] [ebp-14h]
  int height_select_current; // [esp+C8h] [ebp-Ch]
  int v34; // [esp+CCh] [ebp-8h]
  float v35; // [esp+D0h] [ebp-4h]

  if ( unk_7B4DDC )
  {
    v34 = rf_local_fpgun_player;
    if ( rf_local_fpgun_player )
    {
      if ( rf_entity_resolve_handle(*(_DWORD *)(v34 + 20)) )
      {
        height_select_current = rf_font_get_height_select_current(-1);
        v30 = 0;
        rf_render_color_set_rgba8(0, 0, 0, dword_662D58);
        rf_renderer_fill_rectangle_clipped(
          dword_662D60 - 10,
          dword_662D64 - 10,
          dword_662D68,
          dword_662D6C,
          dword_182ABB8);
        v35 = 0.0;
        v31 = 0.0;
        v29 = 0;
        if ( dword_1BDB2D8 > 0 )
        {
          if ( dword_1BDB2D8 < 30 )
            v3 = dword_1BDB2D8 - 1;
          else
            v3 = 28;
          v23 = v3;
          rf_rgba8_construct_components_return_self(&v24, 4, 176, 24, 255);
          rf_rgba8_construct_components_return_self(&v26, 212, 255, 9, 255);
          rf_rgba8_construct_components_return_self(&v22, 0, 246, 139, 255);
          v35 = (double)dword_1BCA398[v23] / flt_662D5C;
          v31 = (double)dword_1BDB260[v23] / flt_662D5C;
          if ( flt_662D5C < (double)(dword_1BDB260[v23] + dword_1BCA398[v23]) )
          {
            v35 = 1.0;
            v31 = 0.0;
            v24 = 255;
            v25 = 0;
            v26 = 255;
            v27 = 0;
          }
          v29 = dword_1BDB260[v23] + dword_1BCA398[v23];
          rf_network_bandwidth_draw_stacked_bar(
            dword_662D60,
            v30 + dword_662D64,
            dword_662D68 - 20,
            height_select_current,
            v35,
            v31,
            (unsigned __int8 *)&v22,
            (unsigned __int8 *)&v24,
            (unsigned __int8 *)&v26);
        }
        v30 += height_select_current;
        sprintf(Buffer, "In : %d bytes/sec", v29);
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_font_draw_text_screen(dword_662D60, v30 + dword_662D64, (unsigned __int8 *)Buffer, -1, dword_182ABBC);
        v30 += height_select_current;
        v30 += height_select_current / 2;
        v35 = 0.0;
        v31 = 0.0;
        v29 = 0;
        if ( dword_1BDB2D8 > 0 )
        {
          if ( dword_1BDB2D8 < 30 )
            v2 = dword_1BDB2D8 - 1;
          else
            v2 = 28;
          v17 = v2;
          rf_rgba8_construct_components_return_self(&v18, 4, 176, 24, 255);
          rf_rgba8_construct_components_return_self(&v20, 212, 255, 9, 255);
          rf_rgba8_construct_components_return_self(&v16, 0, 246, 139, 255);
          v35 = (double)dword_1BCA320[v17] / flt_662D5C;
          v31 = (double)dword_1BDB2E0[v17] / flt_662D5C;
          if ( flt_662D5C < (double)(dword_1BDB2E0[v17] + dword_1BCA320[v17]) )
          {
            v35 = 1.0;
            v31 = 0.0;
            v18 = 255;
            v19 = 0;
            v20 = 255;
            v21 = 0;
          }
          v29 = dword_1BDB2E0[v17] + dword_1BCA320[v17];
          rf_network_bandwidth_draw_stacked_bar(
            dword_662D60,
            v30 + dword_662D64,
            dword_662D68 - 20,
            height_select_current,
            v35,
            v31,
            (unsigned __int8 *)&v16,
            (unsigned __int8 *)&v18,
            (unsigned __int8 *)&v20);
        }
        v30 += height_select_current;
        sprintf(Buffer, "Out : %d bytes/sec", v29);
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_font_draw_text_screen(dword_662D60, v30 + dword_662D64, (unsigned __int8 *)Buffer, -1, dword_182ABBC);
        v30 += height_select_current;
        v30 += height_select_current;
        rf_render_color_set_rgba8(0, 0, 0, dword_662D58);
        rf_renderer_fill_rectangle_clipped(
          dword_662D70 - 10,
          dword_662D74 - 10,
          dword_662D78,
          dword_662D7C,
          dword_182ABB8);
        v35 = 0.0;
        v31 = 0.0;
        v29 = 0;
        if ( dword_1BDB2D8 > 0 )
        {
          if ( dword_1BDB2D8 < 30 )
            v1 = dword_1BDB2D8 - 1;
          else
            v1 = 28;
          v11 = v1;
          rf_rgba8_construct_components_return_self(&v12, 4, 176, 24, 255);
          rf_rgba8_construct_components_return_self(&v14, 212, 255, 9, 255);
          rf_rgba8_construct_components_return_self(&v10, 0, 246, 139, 255);
          v35 = (double)dword_1C0C378[v11] / flt_662D5C;
          v31 = (double)dword_1BDB358[v11] / flt_662D5C;
          if ( flt_662D5C < (double)(dword_1BDB358[v11] + dword_1C0C378[v11]) )
          {
            v35 = 1.0;
            v31 = 0.0;
            v12 = 255;
            v13 = 0;
            v14 = 255;
            v15 = 0;
          }
          v29 = dword_1BDB358[v11] + dword_1C0C378[v11];
          rf_network_bandwidth_draw_stacked_bar(
            dword_662D60,
            v30 + dword_662D64,
            dword_662D68 - 20,
            height_select_current,
            v35,
            v31,
            (unsigned __int8 *)&v10,
            (unsigned __int8 *)&v12,
            (unsigned __int8 *)&v14);
        }
        v30 += height_select_current;
        sprintf(Buffer, "In (r) : %d bytes/sec", v29);
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_font_draw_text_screen(dword_662D60, v30 + dword_662D64, (unsigned __int8 *)Buffer, -1, dword_182ABBC);
        v30 += height_select_current;
        v30 += height_select_current / 2;
        v35 = 0.0;
        v31 = 0.0;
        v29 = 0;
        if ( dword_1BDB2D8 > 0 )
        {
          if ( dword_1BDB2D8 < 30 )
            v0 = dword_1BDB2D8 - 1;
          else
            v0 = 28;
          v5 = v0;
          rf_rgba8_construct_components_return_self(&v6, 4, 176, 24, 255);
          rf_rgba8_construct_components_return_self(&v8, 212, 255, 9, 255);
          rf_rgba8_construct_components_return_self(&v4, 0, 246, 139, 255);
          v35 = (double)dword_1BDB1E8[v5] / flt_662D5C;
          v31 = (double)dword_1C0C300[v5] / flt_662D5C;
          if ( flt_662D5C < (double)(dword_1C0C300[v5] + dword_1BDB1E8[v5]) )
          {
            v35 = 1.0;
            v31 = 0.0;
            v6 = 255;
            v7 = 0;
            v8 = 255;
            v9 = 0;
          }
          v29 = dword_1C0C300[v5] + dword_1BDB1E8[v5];
          rf_network_bandwidth_draw_stacked_bar(
            dword_662D60,
            v30 + dword_662D64,
            dword_662D68 - 20,
            height_select_current,
            v35,
            v31,
            (unsigned __int8 *)&v4,
            (unsigned __int8 *)&v6,
            (unsigned __int8 *)&v8);
        }
        v30 += height_select_current;
        sprintf(Buffer, "Out (r) : %d bytes/sec", v29);
        rf_render_color_set_rgba8(255, 255, 255, 255);
        rf_font_draw_text_screen(dword_662D60, v30 + dword_662D64, (unsigned __int8 *)Buffer, -1, dword_182ABBC);
      }
    }
  }
}

