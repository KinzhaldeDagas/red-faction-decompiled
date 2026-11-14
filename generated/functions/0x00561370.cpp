// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561370 rf_string_format_vector3_fixed_precision
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): cdecl(output RFString,XYZ pointer,precision). Formats exact pattern"< x, y, z >" with each scalar passed to fixed-precision float formatter and same precision. Uses many temporary8byte RFStrings with cleanup; no pointer/precision validation in this helper. Does not parse or normalize vector; returns output.
_DWORD *__cdecl rf_string_format_vector3_fixed_precision(_DWORD *a1, float *a2, int a3)
{
  int *v4; // [esp+20h] [ebp-D0h]
  int *v5; // [esp+28h] [ebp-C8h]
  int *v6; // [esp+30h] [ebp-C0h]
  int *v7; // [esp+38h] [ebp-B8h]
  int *v8; // [esp+40h] [ebp-B0h]
  int *v9; // [esp+48h] [ebp-A8h]
  _DWORD *v10; // [esp+50h] [ebp-A0h]
  _DWORD *v11; // [esp+58h] [ebp-98h]
  _DWORD *v12; // [esp+60h] [ebp-90h]
  _DWORD *v13; // [esp+68h] [ebp-88h]
  _DWORD *v14; // [esp+70h] [ebp-80h]
  _DWORD *v15; // [esp+78h] [ebp-78h]
  _DWORD v16[2]; // [esp+84h] [ebp-6Ch] BYREF
  _DWORD v17[2]; // [esp+8Ch] [ebp-64h] BYREF
  _DWORD v18[2]; // [esp+94h] [ebp-5Ch] BYREF
  _DWORD v19[2]; // [esp+9Ch] [ebp-54h] BYREF
  _DWORD v20[2]; // [esp+A4h] [ebp-4Ch] BYREF
  int v21[2]; // [esp+ACh] [ebp-44h] BYREF
  int v22[2]; // [esp+B4h] [ebp-3Ch] BYREF
  int v23[2]; // [esp+BCh] [ebp-34h] BYREF
  int v24[2]; // [esp+C4h] [ebp-2Ch] BYREF
  int v25[2]; // [esp+CCh] [ebp-24h] BYREF
  int v26[2]; // [esp+D4h] [ebp-1Ch] BYREF
  _DWORD v27[2]; // [esp+DCh] [ebp-14h] BYREF
  int v28; // [esp+ECh] [ebp-4h]

  v15 = rf_string_construct_from_cstr(v27, " >");
  v28 = 1;
  v14 = rf_string_format_float_fixed_precision(v26, a2[2], a3);
  LOBYTE(v28) = 2;
  v13 = rf_string_construct_from_cstr(v25, ", ");
  LOBYTE(v28) = 3;
  v12 = rf_string_format_float_fixed_precision(v24, a2[1], a3);
  LOBYTE(v28) = 4;
  v11 = rf_string_construct_from_cstr(v23, ", ");
  LOBYTE(v28) = 5;
  v10 = rf_string_format_float_fixed_precision(v22, *a2, a3);
  LOBYTE(v28) = 6;
  v9 = rf_string_construct_from_cstr(v21, "< ");
  LOBYTE(v28) = 7;
  v8 = rf_string_concat_two_objects(v20, v9, (int)v10);
  LOBYTE(v28) = 8;
  v7 = rf_string_concat_two_objects(v19, v8, (int)v11);
  LOBYTE(v28) = 9;
  v6 = rf_string_concat_two_objects(v18, v7, (int)v12);
  LOBYTE(v28) = 10;
  v5 = rf_string_concat_two_objects(v17, v6, (int)v13);
  LOBYTE(v28) = 11;
  v4 = rf_string_concat_two_objects(v16, v5, (int)v14);
  LOBYTE(v28) = 12;
  rf_string_concat_two_objects(a1, v4, (int)v15);
  LOBYTE(v28) = 11;
  rf_string_destroy_buffer(v16);
  LOBYTE(v28) = 10;
  rf_string_destroy_buffer(v17);
  LOBYTE(v28) = 9;
  rf_string_destroy_buffer(v18);
  LOBYTE(v28) = 8;
  rf_string_destroy_buffer(v19);
  LOBYTE(v28) = 7;
  rf_string_destroy_buffer(v20);
  LOBYTE(v28) = 6;
  rf_string_destroy_buffer(v21);
  LOBYTE(v28) = 5;
  rf_string_destroy_buffer(v22);
  LOBYTE(v28) = 4;
  rf_string_destroy_buffer(v23);
  LOBYTE(v28) = 3;
  rf_string_destroy_buffer(v24);
  LOBYTE(v28) = 2;
  rf_string_destroy_buffer(v25);
  LOBYTE(v28) = 1;
  rf_string_destroy_buffer(v26);
  LOBYTE(v28) = 0;
  rf_string_destroy_buffer(v27);
  return a1;
}

