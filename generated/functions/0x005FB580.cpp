// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FB580 rf_scene_transform_range_read_binary
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args vfile,pool{used0,base4};NULL file no-op. Reads name/parent strings with max=-1 into260-byte stack buffer,unbounded copies into65-byte fields0/65;parent default Scene Root,otherwise suffix after firsthyphen/whole string. Reads start136,end140 int32. Version>=0x3000E count=end-start+1;older count=end-start. FramePointer144=base+28*oldUsed,used+=count;reads count frames{position3floats0,quaternion4floats12}. No capacity/order/overflow/status checks;negative count reduces used,skips loop. Sampler0x5FB8E0 independently excludes j>=end,so endpoint storage convention differs across version cutoff.
void __thiscall rf_scene_transform_range_read_binary(int this, int *a2, _DWORD *a3)
{
  char v3; // cl
  char v4; // dl
  char v5; // dl
  int v6; // edx
  _BYTE *v7; // [esp+8h] [ebp-14Ch]
  char *v8; // [esp+Ch] [ebp-148h]
  _BYTE *v9; // [esp+18h] [ebp-13Ch]
  char *v10; // [esp+1Ch] [ebp-138h]
  _BYTE *v11; // [esp+38h] [ebp-11Ch]
  char *p_Str; // [esp+3Ch] [ebp-118h]
  char *first_character; // [esp+44h] [ebp-110h]
  int v15; // [esp+48h] [ebp-10Ch]
  char Str; // [esp+4Ch] [ebp-108h] BYREF
  _BYTE v17[3]; // [esp+4Dh] [ebp-107h] BYREF
  int i; // [esp+150h] [ebp-4h]

  if ( a2 )
  {
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    p_Str = &Str;
    v11 = (_BYTE *)this;
    do
    {
      v3 = *p_Str;
      *v11++ = *p_Str++;
    }
    while ( v3 );
    strcpy((char *)(this + 65), "Scene Root");
    rf_binary_stream_read_nul_string_to_buffer(a2, &Str, -1, 0, nullptr);
    if ( &v17[strlen(&Str)] != v17 )
    {
      first_character = rf_cstring_find_first_character(&Str, 45);
      if ( first_character )
      {
        v10 = first_character + 1;
        v9 = (_BYTE *)(this + 65);
        do
        {
          v4 = *v10;
          *v9++ = *v10++;
        }
        while ( v4 );
      }
      else
      {
        v8 = &Str;
        v7 = (_BYTE *)(this + 65);
        do
        {
          v5 = *v8;
          *v7++ = *v8++;
        }
        while ( v5 );
      }
    }
    *(_DWORD *)(this + 136) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    *(_DWORD *)(this + 140) = rf_binary_stream_read_int32_versioned(a2, 0, 0);
    if ( rf_binary_stream_version_at_least(a2, 196622) )
      v6 = *(_DWORD *)(this + 140) - *(_DWORD *)(this + 136) + 1;
    else
      v6 = *(_DWORD *)(this + 140) - *(_DWORD *)(this + 136);
    v15 = v6;
    *(_DWORD *)(this + 144) = a3[1] + 28 * *a3;
    *a3 += v6;
    for ( i = 0; i < v15; ++i )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)(*(_DWORD *)(this + 144) + 28 * i), 0, unk_1C8FBDC);
      rf_binary_stream_read_float4_versioned(a2, (float *)(*(_DWORD *)(this + 144) + 28 * i + 12), 0, unk_1C8FC3C);
    }
  }
}

