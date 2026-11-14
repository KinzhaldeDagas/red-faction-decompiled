// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00487570 rf_mover_reset_sequence_and_free_aux_ring
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL volume/decal layouts, cumulative corner room queries, mover list and auxiliary-node ownership, linked physics flags and native debug draw arguments): 
// Cdecl no arguments. Sets sequence DWORD704608=0, then drains/frees20-byte auxiliary moving-solid ring704600 with same next0/prev4 unlink behavior as exit cleanup4874C0. Explicitly
// sets headNULL after loop. Does not reset mover/moving-solid common sentinels, delete their objects, destroy geometry or free borrowed transform pointers in nodes. Return EAX
// incidental, not success/count. Native dead XOR/JNZ loops do not repeat reset/unlink.
int rf_mover_reset_sequence_and_free_aux_ring()
{
  int result; // eax
  _DWORD *Block; // [esp+0h] [ebp-4h]

  unk_704608 = 0;
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
  dword_704600 = nullptr;
  return result;
}

