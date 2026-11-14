// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F7410 rf_scene_key_tracks_evaluate_quaternion_eased
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl(track,destination float4,fromIndex,toIndex,t). If fromIndex<0,fetches to packed quaternion and unpacks directly via0x41F160. Otherwise if indices differ,reads outgoing ease signedBYTE16/127 from from key and incoming signedBYTE15/127 from to key,remaps t via0x5F76E0. Constructs packed0001 temporary,fetches four signed16 components at key+4 of both indices,interpolates via0x584060,then unpacks each using exact multiplier0.00006103888154029846,NO normalization. No index/count/parameter guard;copy/getter operations use stack temporaries. Return incidental unpack helper source pointer,not destination/status.
__int16 *__cdecl rf_scene_key_tracks_evaluate_quaternion_eased(_DWORD *a1, float *a2, int a3, int a4, float a5)
{
  __int16 *v5; // eax
  __int16 *v7; // eax
  float quaternion_outgoing_ease; // [esp+4h] [ebp-28h]
  _WORD *packed_quaternion; // [esp+4h] [ebp-28h]
  float quaternion_incoming_ease; // [esp+8h] [ebp-24h]
  _WORD v11[4]; // [esp+Ch] [ebp-20h] BYREF
  _WORD v12[4]; // [esp+14h] [ebp-18h] BYREF
  __int16 v13[4]; // [esp+1Ch] [ebp-10h] BYREF
  __int16 v14[4]; // [esp+24h] [ebp-8h] BYREF

  if ( a3 >= 0 )
  {
    if ( a3 != a4 )
    {
      quaternion_incoming_ease = rf_scene_key_tracks_get_quaternion_incoming_ease(a1, a4);
      quaternion_outgoing_ease = rf_scene_key_tracks_get_quaternion_outgoing_ease(a1, a3);
      a5 = rf_keytrack_remap_ease_parameter(a5, quaternion_outgoing_ease, quaternion_incoming_ease);
    }
    rf_short_quaternion_construct_0001(v14);
    packed_quaternion = rf_scene_key_tracks_get_packed_quaternion(a1, v12, a4);
    v7 = rf_scene_key_tracks_get_packed_quaternion(a1, v11, a3);
    rf_short_quaternion_interpolate_wrapped(v14, v7, packed_quaternion, a5);
    return rf_snapshot_unpack_quaternion_s16(a2, v14);
  }
  else
  {
    v5 = rf_scene_key_tracks_get_packed_quaternion(a1, v13, a4);
    return rf_snapshot_unpack_quaternion_s16(a2, v5);
  }
}

