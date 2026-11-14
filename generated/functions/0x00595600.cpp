// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00595600 rf_scene_point_definition_construct
// UNREALRED VERIFIED [transfer-scene-20261028]: Calls shared node initializer0x5963D0. Writes Unknown NUL-terminated text at name+0 and parent+65 (assembly DWORD constants, not pointer assignments); clears flags DWORD+136 bit0 only. Zeroes vector+160 and DWORDs+172,+176. Does not initialize scalar fields+140..156 or clear other flags. The preceding vector default constructor has no blanket zeroing effect.
void __thiscall rf_scene_point_definition_construct(_DWORD *this)
{
  float *v1; // eax
  float copy_result[3]; // [esp+14h] [ebp-24h] BYREF
  float v4[6]; // [esp+20h] [ebp-18h] BYREF

  rf_scene_node_clear_names_and_link(this);
  v4[5] = 0.0;
  rf_vector3_default_construct_noop(this + 40);
  *this = 1852534357;
  *(this + 1) = &unk_6E776F;
  *(_DWORD *)((char *)this + 65) = 1852534357;
  *(_DWORD *)((char *)this + 69) = &unk_6E776F;
  *(this + 34) &= ~1u;
  v1 = rf_vector3_set_components_return_destination(v4, 0.0, 0.0, 0.0);
  rf_vector_copy((float *)this + 40, copy_result, v1);
  *(this + 43) = 0;
  *(this + 44) = 0;
}

