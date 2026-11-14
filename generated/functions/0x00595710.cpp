// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595710 rf_scene_point_definition_read_binary
// UNREALRED VERIFIED [transfer-scene-20261028]: Thiscall definition,optional binary stream,shared sample cursor pair(index,base). Null stream does nothing. Reads name to+0; defaults parent+65 to Scene Root, then replaces with nonempty second string, stripping prefix through first hyphen via0x483940. Updates flags+136 bits0 and1 from bools, reads position+160 and scalars+144,+140,+148,+152,+156. Reads sample count+172, assigns sample pointer+176=cursor.base+36*cursor.index and advances index by count. Each sample: vector+0,scalar+28,+24,+12,+16,+20 and bool bit0 at+32. No cursor capacity/count validation or string capacity checks. Scalar units and flag meanings are left unassigned pending consumer verification.
void __thiscall rf_scene_point_definition_read_binary(int this, int *a2, _DWORD *a3)
{
  char v3; // cl
  char v4; // dl
  char v5; // dl
  _BYTE *v6; // [esp+Ch] [ebp-14Ch]
  char *v7; // [esp+10h] [ebp-148h]
  _BYTE *v8; // [esp+1Ch] [ebp-13Ch]
  char *v9; // [esp+20h] [ebp-138h]
  _BYTE *v10; // [esp+3Ch] [ebp-11Ch]
  char *p_Str; // [esp+40h] [ebp-118h]
  int i; // [esp+48h] [ebp-110h]
  char *first_character; // [esp+4Ch] [ebp-10Ch]
  char Str; // [esp+50h] [ebp-108h] BYREF
  _BYTE v16[3]; // [esp+51h] [ebp-107h] BYREF

  if ( a2 )
  {
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    p_Str = &Str;
    v10 = (_BYTE *)this;
    do
    {
      v3 = *p_Str;
      *v10++ = *p_Str++;
    }
    while ( v3 );
    strcpy((char *)(this + 65), "Scene Root");
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    if ( &v16[strlen(&Str)] != v16 )
    {
      first_character = rf_cstring_find_first_character(&Str, 45);
      if ( first_character )
      {
        v9 = first_character + 1;
        v8 = (_BYTE *)(this + 65);
        do
        {
          v4 = *v9;
          *v8++ = *v9++;
        }
        while ( v4 );
      }
      else
      {
        v7 = &Str;
        v6 = (_BYTE *)(this + 65);
        do
        {
          v5 = *v7;
          *v6++ = *v7++;
        }
        while ( v5 );
      }
    }
    *(_DWORD *)(this + 136) = (rf_binary_stream_read_bool_versioned(a2, 0, 1) != 0)
                            | *(_DWORD *)(this + 136) & 0xFFFFFFFE;
    rf_binary_stream_read_vector3_versioned(a2, (float *)(this + 160), 0, unk_1C8FBDC);
    *(float *)(this + 144) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(this + 140) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(this + 148) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(this + 152) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(float *)(this + 156) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
    *(_DWORD *)(this + 136) = (2 * (rf_binary_stream_read_bool_versioned(a2, 0, 1) & 1))
                            | *(_DWORD *)(this + 136) & 0xFFFFFFFD;
    *(_DWORD *)(this + 172) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(this + 176) = a3[1] + 36 * *a3;
    *a3 += *(_DWORD *)(this + 172);
    for ( i = 0; i < *(_DWORD *)(this + 172); ++i )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)(*(_DWORD *)(this + 176) + 36 * i), 0, unk_1C8FBDC);
      *(float *)(*(_DWORD *)(this + 176) + 36 * i + 28) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 176) + 36 * i + 24) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 176) + 36 * i + 12) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 176) + 36 * i + 16) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 176) + 36 * i + 20) = rf_binary_stream_read_float_versioned(a2, 0, 0.0);
      *(_DWORD *)(*(_DWORD *)(this + 176) + 36 * i + 32) = rf_binary_stream_read_bool_versioned(a2, 0, 1) & 1
                                                         | *(_DWORD *)(*(_DWORD *)(this + 176) + 36 * i + 32)
                                                         & 0xFFFFFFFE;
    }
  }
}

