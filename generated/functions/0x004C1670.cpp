// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1670 rf_managed_particle_effect_list_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall circular sentinel. While next24!=receiver, saves first node into sentinel.prev20, advances sentinel.next24 to victim.next24 BEFORE invoking victim scalar deleting
// destructor(flags1). Does NOT repair live nodes prev links on each iteration; list is transiently inconsistent while draining. After loop restores both sentinel links to self, then
// releases sentinel OWN emitter/voice via4C15C0. Does not free sentinel allocation. Exception cleanup also invokes sentinel release if child destruction throws. NULL/corrupt links
// unguarded; node next is dereferenced before victim NULL check.
int *__thiscall rf_managed_particle_effect_list_destroy(int *this)
{
  while ( (int *)*(this + 6) != this )
  {
    *(this + 5) = *(this + 6);
    *(this + 6) = *(_DWORD *)(*(this + 6) + 24);
    if ( *(this + 5) )
      rf_managed_particle_effect_node_scalar_deleting_destructor((int *)*(this + 5), 1);
  }
  *(this + 6) = (int)this;
  *(this + 5) = (int)this;
  return rf_managed_particle_effect_node_release(this);
}

