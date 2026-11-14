// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606D56 _free
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl block, no status return. NULL is immediate
// no-op after SEH setup. LIVE heap mode3: lock4, arm try0, find small-block region; nonNULL region calls sbh_free_block(region,block), then normal/unwind finally unlock4. Found
// region suppresses HeapFree regardless helper result; absent region or other mode calls HeapFree(heap2021854,0,block). On Windows failure get errno SLOT first, then GetLastError and
// get_errno_from_oserr, store mapped result. EH4 scope65E7E0 handler606DAC verified. No heap-handle initialization check, duplicate-free/pointer validation, retry or allocation-size
// query.
void __cdecl free(void *Block)
{
  _DWORD *v1; // eax
  int *v2; // esi
  DWORD LastError; // eax
  _DWORD *v4; // [esp+10h] [ebp-1Ch]

  if ( Block )
  {
    if ( unk_2021F40 != 3 )
      goto LABEL_10;
    _lock(4);
    v1 = __sbh_find_block(Block);
    v4 = v1;
    if ( v1 )
      __sbh_free_block(v1, Block);
    _unlock(4);
    if ( !v4 )
    {
LABEL_10:
      if ( !HeapFree(MEMORY[0x2021854], 0, Block) )
      {
        v2 = _errno();
        LastError = GetLastError();
        *v2 = _get_errno_from_oserr(LastError);
      }
    }
  }
}

