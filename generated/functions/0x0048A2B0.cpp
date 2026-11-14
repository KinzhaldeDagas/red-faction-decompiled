// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A2B0 rf_moving_solid_create
// UNREALRED VERIFIED [mission-mover-geometry-20261013] Creates common type9 solid with authored UID at +0x20 and deserialized solid pointer at +0x294. Stores independent authored position/orientation and links to moving-solid collision list. Runtime mover controller is a separate type8 object, not this solid and not an editor placement.
// UNREALRED VERIFIED [moving-shadow-receiver-20261027] A successful live type-9 creation appends exactly one owner into 0x704BCC/0x704BD0 sentinel list through +0x28C/+0x290, after storing the imported geometry at +0x294. This is the same instance registry traversed by the projected-shadow builder at 0x51367C, independently of how many mover controllers contribute to the solid pose.
// UNREALRED VERIFIED [combat-native-pickup-dependencies-20261111]: Type9 solid common setup radius at+84hex is binary32(length(solid spherecenter+64hex)+solid radius+60hex). Native sphere comes from519E60→5198B0 original vertex order, not rendered mesh bounds or authored roomAABB. Creates common9, attaches rawsolid+294, then4BC330 initializes current/common/predicted position and outer bounds before linking type9 list.
// UNREALRED VERIFIED [combat-original-physics-20261112]: Type9 creation calls4B7E00(type9,flags0,NULL room hint). With a present worldsolid, the initial517060/532BA0 classification returning NULL prevents allocation in BOTH SP and MP: the multiplayer NULL-room exception in4B7E00 applies only to type0 (types6/8 separately exempt), not type9. Accepted objects append in native type9 list order. Later4BC330 position writes do not reclassify the cached initial room. A later topology edit is not evidence that an initially rejected type9 was allocated.
_DWORD *__cdecl rf_moving_solid_create(int a1, int a2, float *source, float *a4)
{
  int v5; // [esp+4h] [ebp-D0h]
  float v6[3]; // [esp+8h] [ebp-CCh] BYREF
  float copy_result[3]; // [esp+18h] [ebp-BCh] BYREF
  _DWORD *v8; // [esp+24h] [ebp-B0h]
  void *v9[39]; // [esp+28h] [ebp-ACh] BYREF
  int v10; // [esp+C4h] [ebp-10h]
  int v11; // [esp+D0h] [ebp-4h]

  rf_object_setup152_construct_members((char *)v9);
  v11 = 0;
  memset(v9, 0, 0x98u);
  v9[0] = nullptr;
  v9[1] = nullptr;
  *(float *)&v9[5] = 1.0;
  *(float *)&v9[33] = rf_vector3_length((float *)(a2 + 100)) + *(float *)(a2 + 96);
  rf_vector_copy((float *)&v9[15], copy_result, source);
  rf_matrix3_copy((float *)&v9[18], a4);
  v9[37] = (void *)112;
  v10 = rf_object_create(9, -1, -1, (int)v9, 0, 0);
  if ( v10 )
  {
    *(_DWORD *)(v10 + 32) = a1;
    *(_DWORD *)(v10 + 660) = a2;
    rf_vector_copy((float *)(v10 + 240), v6, (const float *)(v10 + 228));
    rf_object_publish_position_and_bounds(v10, (float *)(v10 + 240));
    *(_DWORD *)(v10 + 656) = unk_704BD0;
    *(_DWORD *)(v10 + 652) = &unk_704940;
    *(_DWORD *)(unk_704BD0 + 652) = v10;
    unk_704BD0 = v10;
    v8 = malloc(0x14u);
    v8[3] = v10 + 60;
    v8[4] = v10 + 72;
    v8[2] = a2;
    if ( dword_704600 )
    {
      v8[1] = dword_704600[1];
      *v8 = dword_704600;
      *(_DWORD *)dword_704600[1] = v8;
      dword_704600[1] = v8;
    }
    else
    {
      *v8 = v8;
      v8[1] = v8;
      dword_704600 = v8;
    }
    v5 = v10;
    v11 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return (_DWORD *)v5;
  }
  else
  {
    v11 = -1;
    rf_object_setup152_destroy_array_backing(v9);
    return nullptr;
  }
}

