// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FAF00 rf_scene_transform_track_definition_read_binary
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Args vfile,pool{usedCount0,base4};NULL file no-op. Reads name and parent NULstrings with max=-1 into260-byte stack local,then unbounded copies to65-byte names0/65. Parent default Scene Root;nonempty uses substring afterFIRST hyphen or whole string. Reads Boolean(defaulttrue,threshold0) into packedWORD164 bit15 preservinglow15;reads base position136,quaternion148. Reads int32count,stores low15bits intoWORD164 preservingflag15. Count for pool increment/loop is SIGNED15:signExtend16(WORD164<<1)>>1,so values0x4000..0x7FFF become negative. FramePointer168=pool.base+28*oldUsed,then used+=signedCount. Positive count reads28-byte records(position0,quaternion12). No pool-capacity,overflow,string or stream-status validation;negative packed count reduces used and skips loop. Constructor initializes
// count/flag0;reader suppliesbase pose independently of frames.
void __thiscall rf_scene_transform_track_definition_read_binary(int this, int *a2, _DWORD *a3)
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
    *(_WORD *)(this + 164) = (rf_binary_stream_read_bool_versioned(a2, 0, 1) << 15) | *(_WORD *)(this + 164) & 0x7FFF;
    rf_binary_stream_read_vector3_versioned(a2, (float *)(this + 136), 0, unk_1C8FBDC);
    rf_binary_stream_read_float4_versioned(a2, (float *)(this + 148), 0, unk_1C8FC3C);
    *(_WORD *)(this + 164) = rf_binary_stream_read_int32_versioned(a2, 0, 0) & 0x7FFF | *(_WORD *)(this + 164) & 0x8000;
    *(_DWORD *)(this + 168) = a3[1] + 28 * *a3;
    *a3 += (__int16)(2 * *(_WORD *)(this + 164)) >> 1;
    for ( i = 0; i < (__int16)(2 * *(_WORD *)(this + 164)) >> 1; ++i )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)(*(_DWORD *)(this + 168) + 28 * i), 0, unk_1C8FBDC);
      rf_binary_stream_read_float4_versioned(a2, (float *)(*(_DWORD *)(this + 168) + 28 * i + 12), 0, unk_1C8FC3C);
    }
  }
}

