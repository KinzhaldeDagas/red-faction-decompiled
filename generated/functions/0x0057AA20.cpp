// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057AA20 rf_string_format_angle_bracket_vector3
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric grammar and rounding, structured-value layouts, ignored list limits, callback/flag behavior and formatter cleanup): cdecl output RFString storage, pointer to three floats, fixed decimal precision. Constructs RFString text < x, y, z > using5610F0 float formatter, comma-space separators and spaces inside angle brackets. Builds component temporaries in z,y,x call order but concatenates x,y,z; destroys all nine temporary strings on normal completion with compiler SEH unwind paths. Final concat constructs output and returns output pointer; output is return-object storage rather than an already assigned string. No numeric normalization or parser state.
_DWORD *__cdecl rf_string_format_angle_bracket_vector3(_DWORD *a1, float *a2, int a3)
{
  char **v4; // [esp+20h] [ebp-A0h]
  int *v5; // [esp+28h] [ebp-98h]
  char **v6; // [esp+30h] [ebp-90h]
  int *v7; // [esp+38h] [ebp-88h]
  char **v8; // [esp+40h] [ebp-80h]
  int *v9; // [esp+48h] [ebp-78h]
  _DWORD *v10; // [esp+50h] [ebp-70h]
  _DWORD *v11; // [esp+58h] [ebp-68h]
  _DWORD *v12; // [esp+60h] [ebp-60h]
  _DWORD v13[2]; // [esp+6Ch] [ebp-54h] BYREF
  _DWORD v14[2]; // [esp+74h] [ebp-4Ch] BYREF
  _DWORD v15[2]; // [esp+7Ch] [ebp-44h] BYREF
  _DWORD v16[2]; // [esp+84h] [ebp-3Ch] BYREF
  _DWORD v17[2]; // [esp+8Ch] [ebp-34h] BYREF
  int v18[2]; // [esp+94h] [ebp-2Ch] BYREF
  int v19[2]; // [esp+9Ch] [ebp-24h] BYREF
  int v20[2]; // [esp+A4h] [ebp-1Ch] BYREF
  int v21[2]; // [esp+ACh] [ebp-14h] BYREF
  int v22; // [esp+BCh] [ebp-4h]

  v12 = rf_string_format_float_fixed_precision(v21, a2[2], a3);
  v22 = 1;
  v11 = rf_string_format_float_fixed_precision(v20, a2[1], a3);
  LOBYTE(v22) = 2;
  v10 = rf_string_format_float_fixed_precision(v19, *a2, a3);
  LOBYTE(v22) = 3;
  v9 = rf_string_construct_from_cstr(v18, "< ");
  LOBYTE(v22) = 4;
  v8 = (char **)rf_string_concat_two_objects(v17, v9, (int)v10);
  LOBYTE(v22) = 5;
  v7 = rf_string_concat_object_cstr(v16, v8, ", ");
  LOBYTE(v22) = 6;
  v6 = (char **)rf_string_concat_two_objects(v15, v7, (int)v11);
  LOBYTE(v22) = 7;
  v5 = rf_string_concat_object_cstr(v14, v6, ", ");
  LOBYTE(v22) = 8;
  v4 = (char **)rf_string_concat_two_objects(v13, v5, (int)v12);
  LOBYTE(v22) = 9;
  rf_string_concat_object_cstr(a1, v4, " >");
  LOBYTE(v22) = 8;
  rf_string_destroy_buffer(v13);
  LOBYTE(v22) = 7;
  rf_string_destroy_buffer(v14);
  LOBYTE(v22) = 6;
  rf_string_destroy_buffer(v15);
  LOBYTE(v22) = 5;
  rf_string_destroy_buffer(v16);
  LOBYTE(v22) = 4;
  rf_string_destroy_buffer(v17);
  LOBYTE(v22) = 3;
  rf_string_destroy_buffer(v18);
  LOBYTE(v22) = 2;
  rf_string_destroy_buffer(v19);
  LOBYTE(v22) = 1;
  rf_string_destroy_buffer(v20);
  LOBYTE(v22) = 0;
  rf_string_destroy_buffer(v21);
  return a1;
}

