// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561190 rf_string_format_byte_count_units
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): cdecl(output RFString,signed byteCount). If count<999 (including negatives), decimal integer plus literal" bytes". Else rounds count/1024 to float; if below float999.989990234375 formats2fixed decimal plus verified literal" KB", otherwise divides again by1024 and formats2decimals plus" MB". No GB branch or localization. Builds/destroys RFString temporaries and returns output.
_DWORD *__cdecl rf_string_format_byte_count_units(_DWORD *a1, int a2)
{
  int *v3; // [esp+10h] [ebp-78h]
  float v4; // [esp+18h] [ebp-70h]
  _DWORD *v5; // [esp+1Ch] [ebp-6Ch]
  int *v6; // [esp+24h] [ebp-64h]
  _DWORD *v7; // [esp+2Ch] [ebp-5Ch]
  int *v8; // [esp+34h] [ebp-54h]
  _DWORD *v9; // [esp+3Ch] [ebp-4Ch]
  int v10[2]; // [esp+48h] [ebp-40h] BYREF
  int v11[2]; // [esp+50h] [ebp-38h] BYREF
  int v12[2]; // [esp+58h] [ebp-30h] BYREF
  _DWORD v13[2]; // [esp+60h] [ebp-28h] BYREF
  _DWORD v14[2]; // [esp+68h] [ebp-20h] BYREF
  _DWORD v15[2]; // [esp+70h] [ebp-18h] BYREF
  float v16; // [esp+78h] [ebp-10h]
  int v17; // [esp+84h] [ebp-4h]

  if ( a2 >= 999 )
  {
    v16 = (double)a2 / 1024.0;
    if ( v16 >= 999.989990234375 )
    {
      v5 = rf_string_construct_from_cstr(v11, " MB");
      v17 = 5;
      v4 = v16 / 1024.0;
      v3 = rf_string_format_float_fixed_precision(v10, v4, 2);
      LOBYTE(v17) = 6;
      rf_string_concat_two_objects(a1, v3, (int)v5);
      LOBYTE(v17) = 5;
      rf_string_destroy_buffer(v10);
      LOBYTE(v17) = 0;
      rf_string_destroy_buffer(v11);
    }
    else
    {
      v7 = rf_string_construct_from_cstr(v13, (char *)off_64082C);
      v17 = 3;
      v6 = rf_string_format_float_fixed_precision(v12, v16, 2);
      LOBYTE(v17) = 4;
      rf_string_concat_two_objects(a1, v6, (int)v7);
      LOBYTE(v17) = 3;
      rf_string_destroy_buffer(v12);
      LOBYTE(v17) = 0;
      rf_string_destroy_buffer(v13);
    }
    return a1;
  }
  else
  {
    v9 = rf_string_construct_from_cstr(v15, " bytes");
    v17 = 1;
    v8 = rf_string_format_int32_decimal(v14, a2);
    LOBYTE(v17) = 2;
    rf_string_concat_two_objects(a1, v8, (int)v9);
    LOBYTE(v17) = 1;
    rf_string_destroy_buffer(v14);
    LOBYTE(v17) = 0;
    rf_string_destroy_buffer(v15);
    return a1;
  }
}

