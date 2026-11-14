// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051F150 rf_renderer_draw_and_clear_room_statistics
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): No arguments, draws five debug text lines at X0,Y300 with green RGBA(0,255,0,128), default/current fontID-1 and fifth DWORD argument global182ABBC forwarded to drawing. Strings: Rooms searched: A42054 / A4204C; Rooms rendered: A42050; Faces rendered: A42058; Objects rendered: A42060; Total faces: A4205C. Decimal integer formatting, concatenation and temporary string destruction have SEH cleanup. After EACH draw add current selected font height (five height calls total). Return finalY EAX. Then reset ALL SIX statistics DWORDs A4204C,50,54,58,5C,60 to0, including denominator; does not reset visible array countA42074 or room flags. Does not restore prior render color/font; no statistics
// display enable check inside body.
int rf_renderer_draw_and_clear_room_statistics()
{
  unsigned __int8 *v0; // eax
  unsigned __int8 *v1; // eax
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  unsigned __int8 *v4; // eax
  int result; // eax
  int v6; // [esp-4h] [ebp-ECh]
  int v7; // [esp-4h] [ebp-ECh]
  int v8; // [esp-4h] [ebp-ECh]
  int v9; // [esp-4h] [ebp-ECh]
  int v10; // [esp-4h] [ebp-ECh]
  std::exception *v11; // [esp+4h] [ebp-E4h]
  const void **v12; // [esp+Ch] [ebp-DCh]
  std::exception *v13; // [esp+14h] [ebp-D4h]
  const void **v14; // [esp+1Ch] [ebp-CCh]
  std::exception *v15; // [esp+24h] [ebp-C4h]
  const void **v16; // [esp+2Ch] [ebp-BCh]
  std::exception *v17; // [esp+34h] [ebp-B4h]
  const void **v18; // [esp+3Ch] [ebp-ACh]
  std::exception *v19; // [esp+44h] [ebp-A4h]
  int *v20; // [esp+4Ch] [ebp-9Ch]
  _DWORD *v21; // [esp+54h] [ebp-94h]
  const void **v22; // [esp+5Ch] [ebp-8Ch]
  _DWORD *v23; // [esp+64h] [ebp-84h]
  _BYTE v24[8]; // [esp+6Ch] [ebp-7Ch] BYREF
  _DWORD v25[2]; // [esp+74h] [ebp-74h] BYREF
  _BYTE v26[8]; // [esp+7Ch] [ebp-6Ch] BYREF
  _DWORD v27[2]; // [esp+84h] [ebp-64h] BYREF
  _BYTE v28[8]; // [esp+8Ch] [ebp-5Ch] BYREF
  _DWORD v29[2]; // [esp+94h] [ebp-54h] BYREF
  _BYTE v30[8]; // [esp+9Ch] [ebp-4Ch] BYREF
  _DWORD v31[2]; // [esp+A4h] [ebp-44h] BYREF
  _BYTE v32[8]; // [esp+ACh] [ebp-3Ch] BYREF
  _BYTE v33[8]; // [esp+B4h] [ebp-34h] BYREF
  _BYTE v34[8]; // [esp+BCh] [ebp-2Ch] BYREF
  _DWORD v35[2]; // [esp+C4h] [ebp-24h] BYREF
  _DWORD v36[2]; // [esp+CCh] [ebp-1Ch] BYREF
  int v37; // [esp+D4h] [ebp-14h]
  int v38; // [esp+D8h] [ebp-10h]
  int v39; // [esp+E4h] [ebp-4h]

  v37 = 0;
  v38 = 300;
  rf_render_color_set_rgba8(0, 255, 0, 128);
  v6 = dword_182ABBC;
  v23 = rf_string_format_int32_decimal(v36, *(int *)&byte_98967F[756173]);
  v39 = 0;
  v22 = (const void **)rf_string_format_int32_decimal(v35, *(int *)&byte_98967F[756181]);
  LOBYTE(v39) = 1;
  v21 = rf_string_concat_cstr_object(v34, "Rooms searched: ", v22);
  LOBYTE(v39) = 2;
  v20 = (int *)rf_string_concat_object_cstr(v33, v21, "/");
  LOBYTE(v39) = 3;
  v19 = (std::exception *)rf_string_concat_two_objects(v32, v20, (int)v23);
  LOBYTE(v39) = 4;
  v0 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v19);
  rf_font_draw_text_screen(v37, v38, v0, -1, v6);
  LOBYTE(v39) = 3;
  rf_string_destroy_buffer(v32);
  LOBYTE(v39) = 2;
  rf_string_destroy_buffer(v33);
  LOBYTE(v39) = 1;
  rf_string_destroy_buffer(v34);
  LOBYTE(v39) = 0;
  rf_string_destroy_buffer(v35);
  v39 = -1;
  rf_string_destroy_buffer(v36);
  v38 += rf_font_get_height_select_current(-1);
  v7 = dword_182ABBC;
  v18 = (const void **)rf_string_format_int32_decimal(v31, *(int *)&byte_98967F[756177]);
  v39 = 5;
  v17 = (std::exception *)rf_string_concat_cstr_object(v30, "Rooms rendered: ", v18);
  LOBYTE(v39) = 6;
  v1 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v17);
  rf_font_draw_text_screen(v37, v38, v1, -1, v7);
  LOBYTE(v39) = 5;
  rf_string_destroy_buffer(v30);
  v39 = -1;
  rf_string_destroy_buffer(v31);
  v38 += rf_font_get_height_select_current(-1);
  v8 = dword_182ABBC;
  v16 = (const void **)rf_string_format_int32_decimal(v29, *(int *)&byte_98967F[756185]);
  v39 = 7;
  v15 = (std::exception *)rf_string_concat_cstr_object(v28, "Faces rendered: ", v16);
  LOBYTE(v39) = 8;
  v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v15);
  rf_font_draw_text_screen(v37, v38, v2, -1, v8);
  LOBYTE(v39) = 7;
  rf_string_destroy_buffer(v28);
  v39 = -1;
  rf_string_destroy_buffer(v29);
  v38 += rf_font_get_height_select_current(-1);
  v9 = dword_182ABBC;
  v14 = (const void **)rf_string_format_int32_decimal(v27, *(int *)&byte_98967F[756193]);
  v39 = 9;
  v13 = (std::exception *)rf_string_concat_cstr_object(v26, "Objects rendered: ", v14);
  LOBYTE(v39) = 10;
  v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v13);
  rf_font_draw_text_screen(v37, v38, v3, -1, v9);
  LOBYTE(v39) = 9;
  rf_string_destroy_buffer(v26);
  v39 = -1;
  rf_string_destroy_buffer(v27);
  v38 += rf_font_get_height_select_current(-1);
  v10 = dword_182ABBC;
  v12 = (const void **)rf_string_format_int32_decimal(v25, *(int *)&byte_98967F[756189]);
  v39 = 11;
  v11 = (std::exception *)rf_string_concat_cstr_object(v24, "Total faces: ", v12);
  LOBYTE(v39) = 12;
  v4 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v11);
  rf_font_draw_text_screen(v37, v38, v4, -1, v10);
  LOBYTE(v39) = 11;
  rf_string_destroy_buffer(v24);
  v39 = -1;
  rf_string_destroy_buffer(v25);
  result = v38 + rf_font_get_height_select_current(-1);
  *(_DWORD *)&byte_98967F[756173] = 0;
  *(_DWORD *)&byte_98967F[756177] = 0;
  *(_DWORD *)&byte_98967F[756181] = 0;
  *(_DWORD *)&byte_98967F[756185] = 0;
  *(_DWORD *)&byte_98967F[756189] = 0;
  *(_DWORD *)&byte_98967F[756193] = 0;
  return result;
}

