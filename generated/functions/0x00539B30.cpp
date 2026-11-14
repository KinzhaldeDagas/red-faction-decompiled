// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539B30 rf_world_step_uv_scroll_and_authored_sky_liquid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall world,delta float. Steps every UV descriptor in pointer-array world+756 through539990. Then iterates room array world+144;only authored-sky rooms with byte352 set,byte388 EXACTLY1,and (roomU436!=0 OR roomV440!=0) get direct liquid UV update. For each liquid face in room+40 face list,calls539A10 with both room velocities*delta. Ordinary non-sky rooms not processed by this second loop. No cache refresh or room packet invalidation;nominal return is room-array count at loop exit,not updated face count. Distinct from packet builder liquid fallback requiring both velocities and using onlyU.
int __thiscall rf_world_step_uv_scroll_and_authored_sky_liquid(int this, float a2)
{
  float **v2; // eax
  int result; // eax
  float v5; // [esp+Ch] [ebp-1Ch]
  int k; // [esp+10h] [ebp-18h]
  float v7; // [esp+14h] [ebp-14h]
  int v8; // [esp+18h] [ebp-10h]
  int first_dword; // [esp+1Ch] [ebp-Ch]
  int v10; // [esp+20h] [ebp-8h]
  int i; // [esp+24h] [ebp-4h]
  int j; // [esp+24h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword((void *)(this + 756));
  for ( i = 0; i < first_dword; ++i )
  {
    v2 = (float **)sub_552200((_DWORD *)(this + 756), i);
    rf_uv_scroll_descriptor_step_cached_faces(*v2, a2);
  }
  result = rf_receiver_get_first_dword((void *)(this + 144));
  v10 = result;
  for ( j = 0; j < v10; ++j )
  {
    v8 = *(_DWORD *)sub_552200((_DWORD *)(this + 144), j);
    if ( rf_room_is_authored_sky((_BYTE *)v8)
      && *(_BYTE *)(v8 + 352)
      && *(_BYTE *)(v8 + 388) == 1
      && (*(float *)(v8 + 436) != 0.0 || *(float *)(v8 + 440) != 0.0) )
    {
      v5 = *(float *)(v8 + 436) * a2;
      v7 = *(float *)(v8 + 440) * a2;
      for ( k = rf_receiver_get_first_dword((void *)(v8 + 40)); k; k = rf_face_next_room_link(k) )
      {
        if ( rf_face_is_liquid((_DWORD *)(k + 40)) )
          rf_face_translate_primary_uv_and_rebase((float *)k, v5, v7);
      }
    }
    result = j + 1;
  }
  return result;
}

