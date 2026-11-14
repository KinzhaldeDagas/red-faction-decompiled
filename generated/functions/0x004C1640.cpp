// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1640 rf_managed_particle_effect_list_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall32B sentinel returns receiver. Calls node ctor4C1570, then prev20=next24=receiver, constructing empty circular doubly linked list. Sentinel
// emitterNULL,voice-1,roomNULL,position uninitialized. Native XOR ECX,ECX/JNZ following link stores is dead, not a repeated initialization loop.
_DWORD *__thiscall rf_managed_particle_effect_list_construct(_DWORD *this)
{
  rf_managed_particle_effect_node_construct(this);
  *(this + 6) = this;
  *(this + 5) = this;
  return this;
}

