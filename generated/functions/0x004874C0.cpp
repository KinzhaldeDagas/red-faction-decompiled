// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004874C0 rf_moving_solid_aux_ring_free_at_exit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl no arguments, registered by mover registries initializer. Drains circular doubly linked malloc-node ring704600 using nextDWORD0/prevDWORD4. Single-node case zeros both links
// and head; otherwise advances head to victim.next, repairs neighbor links, zeros victim links, then free(victim). Continues until headNULL. Creation48A2B0 allocates20-byte nodes
// with solid pointer8 and borrowed live position/orientation pointers12/16. This cleanup frees ONLY auxiliary nodes, not geometry, common objects or borrowed transforms. Does not
// reset mover counter704608 or type8/type9 sentinel lists; no corrupt-link checks.
void __cdecl rf_moving_solid_aux_ring_free_at_exit()
{
  _DWORD *Block; // [esp+0h] [ebp-4h]

  while ( dword_704600 )
  {
    Block = dword_704600;
    if ( (_DWORD *)*dword_704600 == dword_704600 )
    {
      *dword_704600 = 0;
      Block[1] = 0;
      dword_704600 = nullptr;
    }
    else
    {
      dword_704600 = (_DWORD *)*dword_704600;
      *(_DWORD *)Block[1] = *Block;
      *(_DWORD *)(*Block + 4) = Block[1];
      *Block = 0;
      Block[1] = 0;
    }
    free(Block);
  }
}

