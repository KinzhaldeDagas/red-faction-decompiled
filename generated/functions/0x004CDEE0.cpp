// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CDEE0 rf_particle_emitter_set_world_frame
// UNREALRED VERIFIED [combat-native-followup-20261104]: Explicit frame setter assigns517060 return directly to runtime room+76, including null, then copies new position+8 and direction+20 without normalization. This differs from initializer4CDAA0 supplied-room fallback. Coordinates are still subject to4CD460 parent transformation; name world_frame alone does not prove caller supplied world coordinates.
float *__thiscall rf_particle_emitter_set_world_frame(int this, float *source, float *a3)
{
  float v5[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  *(_DWORD *)(this + 76) = rf_world_resolve_cached_room(
                             (void *)rf_world_solid,
                             *(void **)(this + 76),
                             (const float *)(this + 8),
                             source,
                             0);
  rf_vector_copy((float *)(this + 8), copy_result, source);
  return rf_vector_copy((float *)(this + 20), v5, a3);
}

