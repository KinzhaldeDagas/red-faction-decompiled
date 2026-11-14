// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047FFC0 rf_rfl_decals_read
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl stream. Constructs reusable decal parameter record and temporary RFString, reads signed row count. Each row consumes/discards id,string; reads position0,matrix12; discards
// string,bool(default1). Reads three floats into dimensions48/52/56, resets flagsDWORD72=0, reads bitmap name and loads bitmap(-1,1) intoDWORD60. Reads alpha int32(min95,default255),
// retains LOW BYTE at68 without clamp. Bool(min137,default0) nonzero sets flag0x20. Reads mode int32(min151,default0),scale FLOAT(min151,default1); mode1 sets0x40,mode2
// sets0x80,others neither; stores scale84.
// Calls room resolver480230(position,matrix,dimensions), saves returned pointer atDWORD64. Nonnull sets flags|0xB,world solid DWORD80,submits world decal. NULL skips submit; both
// paths invoke progress_update_poll_network_and_callback(0,0) per row. Constructor occurs ONCE before loop; no per-row full zeroing, bitmap failure rejection, finite/dimension
// validation or explicit bitmap release. Parameter constructor initializes offset76=-1 and does not establish meanings by matching runtime decal offsets. String destroyed on
// exit/unwind.
void __cdecl rf_rfl_decals_read(_DWORD *a1)
{
  char *v1; // eax
  int v2; // [esp+10h] [ebp-90h]
  int v3[2]; // [esp+14h] [ebp-8Ch] BYREF
  float v4; // [esp+1Ch] [ebp-84h]
  int int32_versioned; // [esp+24h] [ebp-7Ch]
  float v7; // [esp+28h] [ebp-78h]
  float v8[3]; // [esp+2Ch] [ebp-74h] BYREF
  char v9[36]; // [esp+38h] [ebp-68h] BYREF
  float v10[4]; // [esp+5Ch] [ebp-44h] BYREF
  char v12; // [esp+70h] [ebp-30h]
  int v13; // [esp+74h] [ebp-2Ch]
  int v14; // [esp+7Ch] [ebp-24h]
  float v15; // [esp+80h] [ebp-20h]
  int i; // [esp+88h] [ebp-18h]
  float v17; // [esp+8Ch] [ebp-14h]
  float float_versioned; // [esp+90h] [ebp-10h]
  int v19; // [esp+9Ch] [ebp-4h]

  rf_string_construct_empty(v3);
  v19 = 0;
  rf_decal_parameter_record_construct((int)v8);
  int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  for ( i = 0; i < int32_versioned; ++i )
  {
    rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v8, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v9, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v17 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    v4 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    rf_vector3_set_components_thiscall(v10, float_versioned, v17, v4);
    v13 = 0;
    rf_binary_stream_read_string_object_versioned(a1, v3, 0, nullptr);
    v1 = (char *)rf_string_object_c_str_or_empty(v3);
    LODWORD(v10[3]) = rf_bitmap_load_with_optional_mipmap_generation(v1, (void *)0xFFFFFFFF, 1);
    v12 = rf_binary_stream_read_int32_versioned(a1, 95, 255);
    if ( rf_binary_stream_read_bool_versioned(a1, 137, 0) )
      v13 |= 0x20u;
    v2 = rf_binary_stream_read_int32_versioned(a1, 151, 0);
    v7 = rf_binary_stream_read_float_versioned(a1, 151, 1.0);
    if ( v2 == 1 )
    {
      v13 |= 0x40u;
    }
    else if ( v2 == 2 )
    {
      v13 |= 0x80u;
    }
    v15 = v7;
    if ( rf_decal_find_room_at_center_or_box_corners((int)v8, (int)v9, v10) )
    {
      v13 |= 0xBu;
      v14 = rf_world_solid;
      rf_impact_decal_world_submit((int)v8);
    }
    rf_progress_update_poll_network_and_callback(0, 0);
  }
  v19 = -1;
  rf_string_destroy_buffer(v3);
}

