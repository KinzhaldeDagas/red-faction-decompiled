// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1A70 rf_managed_particle_effect_node_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall node,flags stackDWORD RET4 (only bit1 consumed). Releases emitter/voice4C15C0, optional flags&1 operator delete(node), returns original receiver bits even after free. No
// list unlink or neighbor repair; caller owns unlink/drain. Does not recursively delete next/prev or reset voice sentinel.
int *__thiscall rf_managed_particle_effect_node_scalar_deleting_destructor(int *this, char a2)
{
  rf_managed_particle_effect_node_release(this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

