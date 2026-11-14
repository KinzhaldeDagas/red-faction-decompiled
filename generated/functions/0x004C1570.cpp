// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1570 rf_managed_particle_effect_node_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall32B node returns receiver. Layout emitter0=NULL, voiceHandle4=-1, position vec3+8 NOOP constructor (components untouched), prev20=NULL,next24=NULL,cachedRoom28=NULL. No
// allocation, list insertion, room lookup, particle enabling or sound playback.
_DWORD *__thiscall rf_managed_particle_effect_node_construct(_DWORD *this)
{
  rf_vector3_default_construct_noop(this + 2);
  *this = 0;
  *(this + 1) = -1;
  *(this + 6) = 0;
  *(this + 5) = 0;
  *(this + 7) = 0;
  return this;
}

