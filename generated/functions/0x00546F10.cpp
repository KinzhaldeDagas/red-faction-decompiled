// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00546F10 rf_level_read_lightmap_descriptors
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl stream-adapter pointer,solid/world receiver;version gates below are DECIMAL. If stream version<128,captures current global atlas-page array15A7148 count as page-index bias;otherwise bias0. Reads signed descriptor count. ANY nonzero count,including negative,with no atlas pages allocates/registers default24-byte128x128 page before loop. Iterates i<count;allocates124-byte registered descriptor536740(receiver),then reads page index+bias;invalid signed result<0 or>=current page count becomes0,and unchecked getter supplies page pointer at descriptor12. Allocation/page/stream failures do not abort or roll back registered objects. FILE FIELD ORDER/destination BYTE
// offsets:page index,4 unsigned bytes widened toDWORD16/20/24/28;version<115 reads/discards orientation9 floats and vector3;always float44,float48,vector52,vector64;min110 vector108(defaultzero),float120(default0),int->boolBYTE9(default0);min123 int->boolBYTE10(default0);min110 ints92/96/100(default0/1/2),floats84/88(default0/0),floats76/80(default1/1). For110<=version<115,reads signed discarded-record count then per record2 floats+2 vector3(eight floats total). Finally min115 int104(default-1),then assigns ENTIRE flagsBYTE8=1. Missing/version-gated values come from reader defaults. Constructor already registered descriptor index0 and handle4=-1;no face-ID assignment here. No descriptor count cap,payload-size/end-of-stream reconciliation,final read-status gate or ownership cleanup. EAX is last helper/page/count residue,not a uniform success value.
int __cdecl rf_level_read_lightmap_descriptors(void **a1, int a2)
{
  int result; // eax
  int int32; // eax
  int v4; // eax
  int *v5; // eax
  unsigned __int8 byte_versioned; // al
  unsigned __int8 v7; // al
  unsigned __int8 v8; // al
  unsigned __int8 v9; // al
  double float_versioned; // st7
  double v11; // st7
  double v12; // st7
  int v13; // eax
  int v14; // eax
  int v15; // eax
  double v16; // st7
  double v17; // st7
  double v18; // st7
  double v19; // st7
  int *v20; // [esp+8h] [ebp-8Ch]
  int v21; // [esp+Ch] [ebp-88h]
  int *v22; // [esp+10h] [ebp-84h]
  void *v23; // [esp+18h] [ebp-7Ch]
  float v24[3]; // [esp+20h] [ebp-74h] BYREF
  float v25[3]; // [esp+2Ch] [ebp-68h] BYREF
  int j; // [esp+38h] [ebp-5Ch]
  int v27; // [esp+3Ch] [ebp-58h]
  float v28[3]; // [esp+40h] [ebp-54h] BYREF
  float v29[9]; // [esp+4Ch] [ebp-48h] BYREF
  int v30; // [esp+70h] [ebp-24h]
  int *v31; // [esp+74h] [ebp-20h]
  int int32_versioned; // [esp+78h] [ebp-1Ch]
  int first_dword; // [esp+7Ch] [ebp-18h]
  int v34; // [esp+80h] [ebp-14h]
  int i; // [esp+84h] [ebp-10h]
  int v36; // [esp+90h] [ebp-4h]

  first_dword = 0;
  if ( rf_stream_adapter_get_cached_or_vfile_version(a1) < 128 )
    first_dword = rf_receiver_get_first_dword(unk_15A7148);
  result = rf_stream_adapter_read_int32(a1);
  v34 = result;
  if ( result )
  {
    result = rf_receiver_get_first_dword(unk_15A7148);
    if ( !result )
    {
      v23 = operator new(0x18u);
      v36 = 0;
      if ( v23 )
        v21 = rf_lightmap_atlas_page24_construct_register((int)v23, 128, 128, 0, 0);
      else
        v21 = 0;
      result = v21;
      v36 = -1;
    }
  }
  for ( i = 0; i < v34; ++i )
  {
    v22 = (int *)operator new(0x7Cu);
    v36 = 1;
    if ( v22 )
      v20 = rf_lightmap_descriptor124_construct_register(v22, a2);
    else
      v20 = nullptr;
    v36 = -1;
    v31 = v20;
    int32 = rf_stream_adapter_read_int32(a1);
    v30 = first_dword + int32;
    if ( first_dword + int32 < 0 || (v4 = rf_receiver_get_first_dword(unk_15A7148), v30 >= v4) )
      v30 = 0;
    v5 = (int *)sub_552200(unk_15A7148, v30);
    v31[3] = *v5;
    byte_versioned = rf_stream_adapter_read_byte_versioned(a1, 0, 0);
    v31[4] = byte_versioned;
    v7 = rf_stream_adapter_read_byte_versioned(a1, 0, 0);
    v31[5] = v7;
    v8 = rf_stream_adapter_read_byte_versioned(a1, 0, 0);
    v31[6] = v8;
    v9 = rf_stream_adapter_read_byte_versioned(a1, 0, 0);
    v31[7] = v9;
    if ( rf_stream_adapter_get_cached_or_vfile_version(a1) < 115 )
    {
      rf_matrix3_construct((char *)v29);
      rf_vector3_default_construct_noop(v28);
      rf_binary_stream_read_orientation(a1, v29, 0, unk_1C8FC18);
      rf_stream_adapter_read_vector3_versioned(a1, v28, 0, unk_1C8FBDC);
    }
    float_versioned = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
    *((float *)v31 + 11) = float_versioned;
    v11 = rf_stream_adapter_read_float_versioned(a1, 0, 0.0);
    *((float *)v31 + 12) = v11;
    rf_stream_adapter_read_vector3_versioned(a1, (float *)v31 + 13, 0, unk_1C8FBDC);
    rf_stream_adapter_read_vector3_versioned(a1, (float *)v31 + 16, 0, unk_1C8FBDC);
    rf_stream_adapter_read_vector3_versioned(a1, (float *)v31 + 27, 110, unk_1C8FBDC);
    v12 = rf_stream_adapter_read_float_versioned(a1, 110, 0.0);
    *((float *)v31 + 30) = v12;
    int32_versioned = rf_stream_adapter_read_int32_versioned(a1, 110, 0);
    *((_BYTE *)v31 + 9) = int32_versioned != 0;
    int32_versioned = rf_stream_adapter_read_int32_versioned(a1, 123, 0);
    *((_BYTE *)v31 + 10) = int32_versioned != 0;
    v13 = rf_stream_adapter_read_int32_versioned(a1, 110, 0);
    v31[23] = v13;
    v14 = rf_stream_adapter_read_int32_versioned(a1, 110, 1);
    v31[24] = v14;
    v15 = rf_stream_adapter_read_int32_versioned(a1, 110, 2);
    v31[25] = v15;
    v16 = rf_stream_adapter_read_float_versioned(a1, 110, 0.0);
    *((float *)v31 + 21) = v16;
    v17 = rf_stream_adapter_read_float_versioned(a1, 110, 0.0);
    *((float *)v31 + 22) = v17;
    v18 = rf_stream_adapter_read_float_versioned(a1, 110, 1.0);
    *((float *)v31 + 19) = v18;
    v19 = rf_stream_adapter_read_float_versioned(a1, 110, 1.0);
    *((float *)v31 + 20) = v19;
    if ( rf_stream_adapter_get_cached_or_vfile_version(a1) >= 110
      && rf_stream_adapter_get_cached_or_vfile_version(a1) < 115 )
    {
      v27 = rf_stream_adapter_read_int32_versioned(a1, 110, 0);
      for ( j = 0; j < v27; ++j )
      {
        rf_stream_adapter_read_float_versioned(a1, 110, 0.0);
        rf_stream_adapter_read_float_versioned(a1, 110, 0.0);
        rf_vector3_default_construct_noop(v24);
        rf_vector3_default_construct_noop(v25);
        rf_stream_adapter_read_vector3_versioned(a1, v24, 110, unk_1C8FBDC);
        rf_stream_adapter_read_vector3_versioned(a1, v25, 110, unk_1C8FBDC);
      }
    }
    result = rf_stream_adapter_read_int32_versioned(a1, 115, -1);
    v31[26] = result;
    *((_BYTE *)v31 + 8) = 1;
  }
  return result;
}

