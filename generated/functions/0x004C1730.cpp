// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1730 rf_managed_particle_effect_list_clear_nodes
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall circular sentinel. Same destructive first-node drain as4C1670: sentinel.prev=victim, sentinel.next=victim.next, deleting-dtor(flags1); no per-step neighbor-prev repair.
// Restores prev20=next24=receiver, returns receiver. Crucially does NOT release sentinel own emitter/voice or free sentinel, unlike list destructor. No NULL/cycle validation; XOR/JNZ
// tail is dead.
_DWORD *__thiscall rf_managed_particle_effect_list_clear_nodes(_DWORD *this)
{
  while ( (_DWORD *)*(this + 6) != this )
  {
    *(this + 5) = *(this + 6);
    *(this + 6) = *(_DWORD *)(*(this + 6) + 24);
    if ( *(this + 5) )
      rf_managed_particle_effect_node_scalar_deleting_destructor((int *)*(this + 5), 1);
  }
  *(this + 6) = this;
  *(this + 5) = this;
  return this;
}

