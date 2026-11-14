// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F6B2 __msize
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) here means storing errno E, invoking
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if the handler returns. Cdecl(block), returns raw unsigned size orUINT_MAX. NULL ->invalid(22)/UINT_MAX.
// Mode3: lock4/armSEH, find small-block region; found ->read rawDWORD[block-4]-9 wrapped, save; finally unlock4. Absent region falls back HeapSize(heap2021854,0,block), replacing
// irrelevant uninitialized scratch loaded in no-region branch. Other modes directly HeapSize. No masking/validation of small header or block alignment. Return native HeapSize result
// unchanged, includingUINT_MAX failure; no own GetLastError mapping on that branch. EH4 scope65ECA0 handler60F744 restores registers and unlocks via60F74C on unwind.
size_t __cdecl _msize(void *Block)
{
  size_t v2; // esi
  _DWORD *v3; // [esp+10h] [ebp-20h]
  int v4; // [esp+14h] [ebp-1Ch]

  if ( Block )
  {
    if ( unk_2021F40 != 3 )
      return HeapSize(MEMORY[0x2021854], 0, Block);
    _lock(4);
    v3 = __sbh_find_block(Block);
    v2 = v3 ? *((_DWORD *)Block - 1) - 9 : v4;
    _unlock(4);
    if ( !v3 )
      return HeapSize(MEMORY[0x2021854], 0, Block);
    return v2;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

