// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F88E0 rf_scene_frame_channel_read_binary
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This224-byte channel,args vfile,pool descriptor{usedCount0,basePointer4};NULL vfile is complete no-op. Inserts this at tail of global circular cache(head0x1F67114,next136,prev140) UNCONDITIONALLY,without testing cache-enabled flag or prior membership. Copies basename from vfile helper0x592510 to source144 unbounded. Reads two NUL strings using max=-1 (up to65535 stored chars) into roughly260-byte stack local:copies first unbounded to name0;defaults name65 to Scene Root,then for nonempty second uses suffix AFTER FIRST hyphen,or whole string if no hyphen. Reads int32kind212,int32frameCount216;frames220=pool.base+48*pool.used;increments used by count with no capacity/overflow validation. Per frame reads vector3 offset0,float4 quaternion12,five floats28/32/36/40/44. No allocation of frames,stream
// status check,string bounds or rollback after cache insertion;negative count changes pool.used but skips frame loop.
void __thiscall rf_scene_frame_channel_read_binary(int this, char *a2, _DWORD *a3)
{
  char v3; // al
  char v4; // cl
  char v5; // dl
  char v6; // dl
  _BYTE *v7; // [esp+Ch] [ebp-15Ch]
  char *v8; // [esp+10h] [ebp-158h]
  _BYTE *v9; // [esp+1Ch] [ebp-14Ch]
  char *v10; // [esp+20h] [ebp-148h]
  _BYTE *v11; // [esp+3Ch] [ebp-12Ch]
  char *p_Str; // [esp+40h] [ebp-128h]
  _BYTE *v13; // [esp+4Ch] [ebp-11Ch]
  char *backslash_basename_pointer; // [esp+50h] [ebp-118h]
  int i; // [esp+58h] [ebp-110h]
  char *first_character; // [esp+5Ch] [ebp-10Ch]
  char Str; // [esp+60h] [ebp-108h] BYREF
  _BYTE v19[3]; // [esp+61h] [ebp-107h] BYREF

  if ( a2 )
  {
    if ( unk_1F67114 )
    {
      *(_DWORD *)(this + 140) = *(_DWORD *)(unk_1F67114 + 140);
      *(_DWORD *)(this + 136) = unk_1F67114;
      *(_DWORD *)(*(_DWORD *)(unk_1F67114 + 140) + 136) = this;
      *(_DWORD *)(unk_1F67114 + 140) = this;
    }
    else
    {
      *(_DWORD *)(this + 136) = this;
      *(_DWORD *)(this + 140) = this;
      unk_1F67114 = this;
    }
    backslash_basename_pointer = rf_vfile_get_backslash_basename_pointer(a2);
    v13 = (_BYTE *)(this + 144);
    do
    {
      v3 = *backslash_basename_pointer;
      *v13++ = *backslash_basename_pointer++;
    }
    while ( v3 );
    rf_binary_stream_read_nul_string_to_buffer((int *)a2, &Str, -1, 0, nullptr);
    p_Str = &Str;
    v11 = (_BYTE *)this;
    do
    {
      v4 = *p_Str;
      *v11++ = *p_Str++;
    }
    while ( v4 );
    strcpy((char *)(this + 65), "Scene Root");
    rf_binary_stream_read_nul_string_to_buffer((int *)a2, &Str, -1, 0, nullptr);
    if ( &v19[strlen(&Str)] != v19 )
    {
      first_character = rf_cstring_find_first_character(&Str, 45);
      if ( first_character )
      {
        v10 = first_character + 1;
        v9 = (_BYTE *)(this + 65);
        do
        {
          v5 = *v10;
          *v9++ = *v10++;
        }
        while ( v5 );
      }
      else
      {
        v8 = &Str;
        v7 = (_BYTE *)(this + 65);
        do
        {
          v6 = *v8;
          *v7++ = *v8++;
        }
        while ( v6 );
      }
    }
    *(_DWORD *)(this + 212) = rf_binary_stream_read_int32_versioned((int *)a2, 0, 0);
    *(_DWORD *)(this + 216) = rf_binary_stream_read_int32_versioned((int *)a2, 0, 0);
    *(_DWORD *)(this + 220) = a3[1] + 48 * *a3;
    *a3 += *(_DWORD *)(this + 216);
    for ( i = 0; i < *(_DWORD *)(this + 216); ++i )
    {
      rf_binary_stream_read_vector3_versioned(a2, (float *)(*(_DWORD *)(this + 220) + 48 * i), 0, unk_1C8FBDC);
      rf_binary_stream_read_float4_versioned(
        (int *)a2,
        (float *)(*(_DWORD *)(this + 220) + 48 * i + 12),
        0,
        unk_1C8FC3C);
      *(float *)(*(_DWORD *)(this + 220) + 48 * i + 28) = rf_binary_stream_read_float_versioned((int *)a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 220) + 48 * i + 32) = rf_binary_stream_read_float_versioned((int *)a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 220) + 48 * i + 36) = rf_binary_stream_read_float_versioned((int *)a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 220) + 48 * i + 40) = rf_binary_stream_read_float_versioned((int *)a2, 0, 0.0);
      *(float *)(*(_DWORD *)(this + 220) + 48 * i + 44) = rf_binary_stream_read_float_versioned((int *)a2, 0, 0.0);
    }
  }
}

