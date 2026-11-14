// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B6AC0 rf_download_draw_progress_overlay
// UNREALRED VERIFIED [file-transfer-20261028]: Uses global tracked slot0x7B4DE4; starts fraction0 and queries0x598310 unless slot=-1. Calls0x571C20, sets render color RGBA(0,255,0,128), draws Downloading file text with requested name0x6FC31C and integer fraction*100+0.5 at(5,20), and Press ESC to abort at(5,40), via text renderer0x58CFC0 and font0x182ABBC. No input polling or abort action in this body. Invalid tracked slot can yield negative displayed percentage; no clamp. Constructs/destroys an otherwise unused local virtual file.
int rf_download_draw_progress_overlay()
{
  unsigned __int8 *v0; // eax
  int v2; // [esp-4h] [ebp-184h]
  std::exception *v3; // [esp+4h] [ebp-17Ch]
  _DWORD *v4; // [esp+Ch] [ebp-174h]
  int *v5; // [esp+14h] [ebp-16Ch]
  _DWORD *v6; // [esp+1Ch] [ebp-164h]
  _DWORD *v7; // [esp+24h] [ebp-15Ch]
  _BYTE v8[8]; // [esp+2Ch] [ebp-154h] BYREF
  _BYTE v9[8]; // [esp+34h] [ebp-14Ch] BYREF
  _BYTE v10[8]; // [esp+3Ch] [ebp-144h] BYREF
  _BYTE v11[8]; // [esp+44h] [ebp-13Ch] BYREF
  _DWORD v12[2]; // [esp+4Ch] [ebp-134h] BYREF
  int self[70]; // [esp+54h] [ebp-12Ch] BYREF
  float progress_fraction; // [esp+170h] [ebp-10h]
  int v15; // [esp+17Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v15 = 0;
  progress_fraction = 0.0;
  if ( dword_7B4DE4 != -1 )
    progress_fraction = rf_file_transfer_get_progress_fraction(dword_7B4DE4);
  rf_renderer_reset_viewport_full_screen();
  rf_render_color_set_rgba8(0, 255, 0, 128);
  v2 = dword_182ABBC;
  v7 = rf_string_format_int32_decimal(v12, (int)(progress_fraction * 100.0 + 0.5));
  LOBYTE(v15) = 1;
  v6 = rf_string_concat_cstr_object(v11, "Downloading file: ", (const void **)unk_6FC31C);
  LOBYTE(v15) = 2;
  v5 = (int *)rf_string_concat_object_cstr(v10, v6, " (");
  LOBYTE(v15) = 3;
  v4 = rf_string_concat_two_objects(v9, v5, (int)v7);
  LOBYTE(v15) = 4;
  v3 = (std::exception *)rf_string_concat_object_cstr(v8, v4, "%)");
  LOBYTE(v15) = 5;
  v0 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v3);
  rf_font_draw_text_screen(5, 20, v0, -1, v2);
  LOBYTE(v15) = 4;
  rf_string_destroy_buffer(v8);
  LOBYTE(v15) = 3;
  rf_string_destroy_buffer(v9);
  LOBYTE(v15) = 2;
  rf_string_destroy_buffer(v10);
  LOBYTE(v15) = 1;
  rf_string_destroy_buffer(v11);
  LOBYTE(v15) = 0;
  rf_string_destroy_buffer(v12);
  rf_font_draw_text_screen(5, 40, "(Press ESC to abort)", -1, dword_182ABBC);
  v15 = -1;
  return rf_vfile_destruct_close_if_open(self);
}

