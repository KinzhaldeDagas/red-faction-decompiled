// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483FE0 rf_geomod_debris_work_enqueue_fifo
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, geometry-operation phases, terrain/debris ownership, saved replay, native x87 gates and localized level-text lifecycle): 
// Cdecl44-byte record, appends to active tail sentinel0x6FDD18 using next+0/prev+4 and global tail0x6FDD1C, returns record EAX. Apparent aspect-priority block is unreachable: on
// nonempty list LEA ECX,[EBP-8] then TEST ECX,ECX/JNZ always branches to append for a valid stack. The local inserted flag stays0. No priority sorting, head insertion, existing-link
// unlink or record payload initialization. Caller must supply an already-unlinked record. Unreachable comparison block is retained original code, not executable behavior to
// reconstruct.
int __cdecl rf_geomod_debris_work_enqueue_fifo(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-8h] BYREF
  unsigned __int8 v3; // [esp+7h] [ebp-1h]

  v3 = 0;
  if ( (_DWORD *)rf_geomod_debris_work_active_head != &rf_geomod_debris_work_active_head )
  {
    v2 = rf_geomod_debris_work_active_head;
    while ( !&v2 )
    {
      if ( *(float *)(v2 + 36) < (double)*(float *)(a1 + 36) )
      {
        **(_DWORD **)(v2 + 4) = a1;
        *(_DWORD *)(a1 + 4) = *(_DWORD *)(v2 + 4);
        *(_DWORD *)(v2 + 4) = a1;
        *(_DWORD *)a1 = v2;
        v3 = 1;
      }
    }
  }
  result = v3;
  if ( !v3 )
  {
    *(_DWORD *)(a1 + 4) = rf_geomod_debris_work_active_tail;
    *(_DWORD *)a1 = &rf_geomod_debris_work_active_head;
    *rf_geomod_debris_work_active_tail = a1;
    rf_geomod_debris_work_active_tail = a1;
    return a1;
  }
  return result;
}

