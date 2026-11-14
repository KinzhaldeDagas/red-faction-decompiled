// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE1E0 rf_scene_definition_get_flat_object_count
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Returns modelCount+76 + sum(each emitter.maxParticles) + pointCount+84 + transformCount+100 + emitterCount+92. Last emitterCount covers type4 emitter-definition/anchor entries,distinct from type1 individual particles. Does not include force channels,visibility lists or transform ranges. Signed arithmetic/counts unchecked.
int __thiscall rf_scene_definition_get_flat_object_count(_DWORD *this)
{
  int v2; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  v2 = *(this + 19);
  for ( i = 0; i < *(this + 23); ++i )
    v2 += *(_DWORD *)(*(this + 22) + 220 * i + 152);
  return *(this + 23) + *(this + 25) + *(this + 21) + v2;
}

