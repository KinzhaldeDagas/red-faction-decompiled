// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047F930 rf_rfl_volume_effects_read
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl stream, reads signed row count and iterates in file order. Each row consumes discarded int32 id,string,position3f,matrix3,string,extra string only version<67,discarded
// bool(default1),shape int32. Shape1 reads radius float; shape2 reads THREE floats in destination component order Y,X,Z. Other shapes read no shape-specific float payload. All shapes
// then consume packed4 color and strength float. Native matrix read uses ECX=stream and stack(destination,min0,defaultmatrix), even if pseudocode hides stream.
// Shape1 creates sphere(position,radius,strength,RGB bytes). Shape2 creates box(position,authored matrix,dimensions,strength,RGB); verified box delegate copies matrix THEN overwrites
// with identity, so created box ignores authored orientation. Creator owns136-byte records appended to global18CCFF4; loader does not clear previous volumes. Unknown shape consumes
// common trailing fields and creates nothing. Native MOVZX supplies unsigned RGB bytes; char-typed pseudocode is not signed color interpretation, alpha discarded. No
// count/radius/dimension/strength clamp, read-status aggregation or rollback. Normal EAX is count/loop artifact, not creation success.
int __cdecl rf_rfl_volume_effects_read(_DWORD *a1)
{
  int result; // eax
  float v2[3]; // [esp+1Ch] [ebp-54h] BYREF
  int int32_versioned; // [esp+28h] [ebp-48h]
  int v4; // [esp+2Ch] [ebp-44h] BYREF
  float float_versioned; // [esp+30h] [ebp-40h]
  char v6[36]; // [esp+34h] [ebp-3Ch] BYREF
  int v7[3]; // [esp+58h] [ebp-18h] BYREF
  float v8; // [esp+64h] [ebp-Ch]
  int v9; // [esp+68h] [ebp-8h]
  int i; // [esp+6Ch] [ebp-4h]

  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v9 = result;
  for ( i = 0; i < v9; ++i )
  {
    rf_vector3_default_construct_noop(v2);
    rf_matrix3_construct(v6);
    rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_vector3_versioned(a1, v2, 0, unk_1C8FBDC);
    rf_binary_stream_read_matrix3_vectors_201_versioned(v6, 0, (int)unk_1C8FC18);
    rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    if ( rf_vfile_get_slot_version(a1) < 67 )
      rf_binary_stream_read_string_object_versioned(a1, unk_6FCCC0, 0, nullptr);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    float_versioned = 0.0;
    rf_vector3_default_construct_noop(v7);
    if ( int32_versioned == 1 )
    {
      float_versioned = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    }
    else if ( int32_versioned == 2 )
    {
      *(float *)&v7[1] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *(float *)v7 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
      *(float *)&v7[2] = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    }
    rf_binary_stream_read_packed4bytes_versioned(a1, &v4, 0, &dword_1C8FC4C);
    v8 = rf_binary_stream_read_float_versioned(a1, 0, 0.0);
    if ( int32_versioned == 1 )
    {
      rf_volume_sphere_create((int)v2, float_versioned, v8, v4, SBYTE1(v4), SBYTE2(v4));
    }
    else if ( int32_versioned == 2 )
    {
      rf_volume_box_create_identity_orientation((int)v2, (int)v6, (int)v7, v8, v4, SBYTE1(v4), SBYTE2(v4));
    }
    result = i + 1;
  }
  return result;
}

