// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005263D0 rf_light_additional_receiver_unregister_first
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, decal polygon ownership/pools,receiver registries,light-space transforms and coverage,original ECX/stack flow and PE bytes): Cdecl receiverSolid void. If global head-cell pointerD035F0 NULL or ringempty no action. Walk forward from head, terminate when next==originalhead; remove FIRST node whose solid8 pointer matches. Sole head clears head and node links; multihead advances head to next; all other removals splice prev.next/next.prev, clear removed links, free20-byte block. Duplicates beyond first remain. Does not free solid or borrowed transform pointers, update geometry, invalidate active list, or mutate other nodes except ring splice.
void __cdecl rf_light_additional_receiver_unregister_first(_DWORD *a1)
{
  _DWORD **v1; // [esp+0h] [ebp-8h]
  _DWORD **Block; // [esp+4h] [ebp-4h]

  if ( dword_D035F0 )
  {
    for ( Block = (_DWORD **)*dword_D035F0; ; Block = v1 )
    {
      if ( !Block )
        return;
      if ( Block[2] == a1 )
        break;
      if ( *Block == (_DWORD *)*dword_D035F0 )
        v1 = nullptr;
      else
        v1 = (_DWORD **)*Block;
    }
    if ( (_DWORD **)*dword_D035F0 == Block )
    {
      if ( *Block == Block )
      {
        *Block = nullptr;
        Block[1] = nullptr;
        *dword_D035F0 = 0;
LABEL_14:
        free(Block);
        return;
      }
      *dword_D035F0 = *Block;
    }
    *Block[1] = *Block;
    (*Block)[1] = Block[1];
    *Block = nullptr;
    Block[1] = nullptr;
    goto LABEL_14;
  }
}

