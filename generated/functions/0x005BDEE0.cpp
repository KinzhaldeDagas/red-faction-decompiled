// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BDEE0 rf_particle_definition_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, particle pool allocation, emission/integration branches, definition loader and original-PE math/constants): Calls base scene-node clear routine,then initializes220-byte definition selectively: name at0 and parent-name+65 to Unknown,owner+132=NULL,three channel pointers+136..144=NULL; clears high count flag+148 but preserves low31bits;maxParticles+152=0,flags+172=0,frameCount+204=0,key pointer+208=NULL,maxSpeed+212=-1e8,maxSpread+216=0,materialIndex+196=-1. Other emission/lifetime/shape/envelope fields are not reset here. Does not allocate or load resources.
void __thiscall rf_particle_definition_construct(_DWORD *this)
{
  int i; // [esp+4h] [ebp-4h]

  rf_scene_node_clear_names_and_link(this);
  *(this + 33) = 0;
  *this = 1852534357;
  *(this + 1) = &unk_6E776F;
  *(_DWORD *)((char *)this + 65) = 1852534357;
  *(_DWORD *)((char *)this + 69) = &unk_6E776F;
  *(this + 37) &= ~0x80000000;
  *(this + 43) = 0;
  for ( i = 0; i < 3; ++i )
    *(this + i + 34) = 0;
  *(this + 38) = 0;
  *(this + 51) = 0;
  *(this + 52) = 0;
  *((float *)this + 53) = -100000000.0;
  *((float *)this + 54) = 0.0;
  *(this + 49) = -1;
}

