// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057AC60 rf_string_format_bracketed_matrix3
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): cdecl output RFString storage, nine consecutive floats, decimal precision. Calls vector formatter57AA20 for groups at offsets24,12,0 in evaluation order, concatenates groups in0,12,24 order. Exact layout begins LF TAB [ SPACE, each subsequent vector preceded LF TAB SPACE SPACE, ends SPACE ]. Delegates numeric text to vector fixed-precision formatter; no transpose or matrix normalization. Final concat constructs output, returns output pointer, destroys eight temporary strings with compiler SEH cleanup paths.
_DWORD *__cdecl rf_string_format_bracketed_matrix3(_DWORD *a1, float *a2, int a3)
{
  char **v4; // [esp+4h] [ebp-90h]
  int *v5; // [esp+Ch] [ebp-88h]
  char **v6; // [esp+14h] [ebp-80h]
  int *v7; // [esp+1Ch] [ebp-78h]
  char **v8; // [esp+24h] [ebp-70h]
  char **v9; // [esp+2Ch] [ebp-68h]
  _DWORD *v10; // [esp+34h] [ebp-60h]
  _DWORD *v11; // [esp+3Ch] [ebp-58h]
  _DWORD v12[2]; // [esp+48h] [ebp-4Ch] BYREF
  _DWORD v13[2]; // [esp+50h] [ebp-44h] BYREF
  _DWORD v14[2]; // [esp+58h] [ebp-3Ch] BYREF
  _DWORD v15[2]; // [esp+60h] [ebp-34h] BYREF
  _DWORD v16[2]; // [esp+68h] [ebp-2Ch] BYREF
  _DWORD v17[2]; // [esp+70h] [ebp-24h] BYREF
  _DWORD v18[2]; // [esp+78h] [ebp-1Ch] BYREF
  _DWORD v19[2]; // [esp+80h] [ebp-14h] BYREF
  int v20; // [esp+90h] [ebp-4h]

  v11 = rf_string_format_angle_bracket_vector3(v19, a2 + 6, a3);
  v20 = 1;
  v10 = rf_string_format_angle_bracket_vector3(v18, a2 + 3, a3);
  LOBYTE(v20) = 2;
  v9 = (char **)rf_string_format_angle_bracket_vector3(v17, a2, a3);
  LOBYTE(v20) = 3;
  v8 = (char **)rf_string_concat_cstr_object(v16, "\n\t[ ", v9);
  LOBYTE(v20) = 4;
  v7 = rf_string_concat_object_cstr(v15, v8, "\n\t  ");
  LOBYTE(v20) = 5;
  v6 = (char **)rf_string_concat_two_objects(v14, v7, (int)v10);
  LOBYTE(v20) = 6;
  v5 = rf_string_concat_object_cstr(v13, v6, "\n\t  ");
  LOBYTE(v20) = 7;
  v4 = (char **)rf_string_concat_two_objects(v12, v5, (int)v11);
  LOBYTE(v20) = 8;
  rf_string_concat_object_cstr(a1, v4, " ]");
  LOBYTE(v20) = 7;
  rf_string_destroy_buffer(v12);
  LOBYTE(v20) = 6;
  rf_string_destroy_buffer(v13);
  LOBYTE(v20) = 5;
  rf_string_destroy_buffer(v14);
  LOBYTE(v20) = 4;
  rf_string_destroy_buffer(v15);
  LOBYTE(v20) = 3;
  rf_string_destroy_buffer(v16);
  LOBYTE(v20) = 2;
  rf_string_destroy_buffer(v17);
  LOBYTE(v20) = 1;
  rf_string_destroy_buffer(v18);
  LOBYTE(v20) = 0;
  rf_string_destroy_buffer(v19);
  return a1;
}

