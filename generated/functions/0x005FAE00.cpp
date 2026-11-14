// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FAE00 rf_scene_transform_track_definition_construct
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): 172-byte definition. Common scene-node initializer clears names/owner;vector default136 no-op,quaternion148=(0,0,0,1). Writes Unknown NUL strings atname0/65. Two WORD164 masks(&=0x7FFF then&=0x8000) produce0;frame pointer168=NULL. Position136 remains uninitialized;WORD166padding untouched. No allocation;packed count/flag initialized only at164.
void __thiscall rf_scene_transform_track_definition_construct(char *this)
{
  rf_scene_node_clear_names_and_link(this);
  rf_vector3_default_construct_noop(this + 136);
  rf_float4_construct_zero_zero_zero_one((float *)this + 37);
  *(_DWORD *)this = 1852534357;
  *((_DWORD *)this + 1) = &unk_6E776F;
  *(_DWORD *)(this + 65) = 1852534357;
  *(_DWORD *)(this + 69) = &unk_6E776F;
  *((_WORD *)this + 82) &= ~0x8000u;
  *((_WORD *)this + 82) &= 0x8000u;
  *((_DWORD *)this + 42) = 0;
}

