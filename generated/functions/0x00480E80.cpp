// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00480E80 sub_480E80
// UNREALRED VERIFIED [ai-navigation-import-20261028] Point-pool loader for RFL0x00020000. Modern v140+ pass1 reads int32 UID, byte flag, float, vector3 position, float, int32, orientation-present byte (matrix3 iff1), three bool bytes (since138), float(since140), and int32 event count plus eventUIDs(since147). Then pass2 reads per-point byte adjacency count plus int32 point indices. Adjacency indices outside pool are ignored; valid neighbors appended uniquely. Events stored point+0x70; neighbors at+0x28; pool owned by world solid+0x300. Several serialized flags/floats are discarded by native loader; preserve as raw rather than inventing semantics. Native wait field+0x24 initialized0 despite trailing serializedfloat. Pre140 layout/storage offset differs and is not modern index format.
// UNREALRED VERIFIED [combat-panic-20261104]: Typed retained navigation source maps to native node:baseposition+0; firstfloatbeforeposition→height+20; float afterposition→+18 andradius+1C; rawinteger→+40; orientationpresent+44,matrix+48; PointUid+6C; validlinks appendeduniquely in sourceorder+28. Leading/3postorientation bools read/discarded. Serialized trailingfloat is read then native wait+24 explicitlyzeroed. Runtimeeligibility+35 and workingposition+0C are request scratch, not authored flags.
// UNREALRED VERIFIED [combat-native-directed-ai-20261111] Each v140+ source waypoint is separately operatornew0x7C before append to world-solid pool. This proves source vector insertion order, NOT monotonically increasing heap address order. Do not label source index comparisons exact native pointer order in directed edge scans.
int __cdecl sub_480E80(_DWORD *a1)
{
  int result; // eax
  int v2; // eax
  int v3; // eax
  int v4; // eax
  int v5; // [esp+0h] [ebp-9Ch]
  float *v6; // [esp+8h] [ebp-94h]
  float copy_result[3]; // [esp+Ch] [ebp-90h] BYREF
  void *v8; // [esp+18h] [ebp-84h]
  float *v9; // [esp+1Ch] [ebp-80h]
  int v10; // [esp+20h] [ebp-7Ch]
  unsigned __int8 byte_versioned; // [esp+27h] [ebp-75h]
  int v12; // [esp+28h] [ebp-74h]
  float *destination; // [esp+2Ch] [ebp-70h]
  int v14; // [esp+30h] [ebp-6Ch]
  int j; // [esp+34h] [ebp-68h]
  int v16; // [esp+38h] [ebp-64h] BYREF
  float v17; // [esp+3Ch] [ebp-60h] BYREF
  char v18; // [esp+43h] [ebp-59h] BYREF
  int v19; // [esp+44h] [ebp-58h]
  float float_versioned; // [esp+48h] [ebp-54h]
  float Buffer[9]; // [esp+4Ch] [ebp-50h] BYREF
  int first_dword; // [esp+70h] [ebp-2Ch]
  int v23; // [esp+74h] [ebp-28h] BYREF
  _DWORD *v24; // [esp+78h] [ebp-24h]
  int i; // [esp+7Ch] [ebp-20h]
  float source[3]; // [esp+80h] [ebp-1Ch] BYREF
  int int32_versioned; // [esp+8Ch] [ebp-10h]
  int v28; // [esp+98h] [ebp-4h]

  rf_vector3_default_construct_noop(source);
  rf_matrix3_construct((char *)Buffer);
  v24 = (_DWORD *)(rf_world_solid + 768);
  first_dword = 0;
  if ( rf_vfile_get_slot_version(a1) < 140 )
    first_dword = rf_receiver_get_first_dword(v24);
  result = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  v19 = result;
  for ( i = 0; i < v19; ++i )
  {
    int32_versioned = rf_binary_stream_read_int32_versioned(a1, 0, 0);
    rf_binary_stream_read_bool_versioned(a1, 0, 1);
    rf_binary_stream_serialize_float32(a1, &v17, 0, 0.0);
    rf_binary_stream_read_vector3_versioned(a1, source, 0, unk_1C8FBDC);
    rf_binary_stream_serialize_float32(a1, (float *)&v23, 0, 0.0);
    rf_binary_stream_serialize_int32(a1, &v16, 0, 0);
    if ( rf_vfile_get_slot_version(a1) < 139 )
      rf_binary_stream_read_int32_versioned(a1, 82, 0);
    rf_binary_stream_serialize_bool(a1, &v18, 82, 0);
    if ( v18 == 1 )
      rf_binary_stream_serialize_matrix3_vectors_201(a1, (char *)Buffer, 83, (int)unk_1C8FC18);
    rf_binary_stream_read_bool_versioned(a1, 138, 0);
    rf_binary_stream_read_bool_versioned(a1, 138, 0);
    rf_binary_stream_read_bool_versioned(a1, 138, 0);
    float_versioned = rf_binary_stream_read_float_versioned(a1, 140, 0.0);
    v8 = operator new(0x7Cu);
    v28 = 0;
    if ( v8 )
      v6 = (float *)rf_dual_array_pose_block_construct_empty((char *)v8);
    else
      v6 = nullptr;
    v9 = v6;
    v28 = -1;
    destination = v6;
    v14 = rf_binary_stream_read_int32_versioned(a1, 147, 0);
    for ( j = 0; j < v14; ++j )
    {
      v12 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      rf_pointer_array_append_dword((_DWORD *)destination + 28, v12);
    }
    *((_DWORD *)destination + 27) = int32_versioned;
    rf_vector_copy(destination, copy_result, source);
    destination[7] = *(float *)&v23;
    destination[6] = *(float *)&v23;
    destination[8] = v17;
    *((_DWORD *)destination + 16) = v16;
    *((_BYTE *)destination + 68) = v18;
    if ( v18 == 1 )
      rf_matrix3_copy(destination + 18, Buffer);
    destination[9] = float_versioned;
    result = rf_pointer_array_append_dword(v24, (int)destination);
  }
  for ( i = 0; i < v19; ++i )
  {
    byte_versioned = rf_binary_stream_read_byte_versioned(a1, 0, 0);
    for ( j = 0; j < byte_versioned; ++j )
    {
      v2 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
      v10 = first_dword + v2;
      if ( first_dword + v2 >= 0 )
      {
        v3 = rf_receiver_get_first_dword(v24);
        if ( v10 < v3 )
        {
          v5 = *(_DWORD *)sub_552200(v24, v10);
          v4 = sub_552200(v24, i);
          rf_pointer_array_append_unique((_DWORD *)(*(_DWORD *)v4 + 40), v5);
        }
      }
    }
    result = i + 1;
  }
  return result;
}

