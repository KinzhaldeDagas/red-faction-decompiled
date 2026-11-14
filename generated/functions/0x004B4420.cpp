// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4420 rf_physics_work_batch_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX embedded batch plus object pointer stackarg,RET4. Signed/raw count DWORD0 compared for EXACT equality1024 only:equal returnsEAX-1 without mutation. Otherwise stores old count,index=count;incrementsDWORDcount;writes object at batch+4+4*oldCount and returns oldCount. Does NOT reject count>1024 or negative,check object,NULL,duplicates or allocation;no resizing. Existing generic comment retained;this refines equality-only capacity admission.
int __thiscall rf_physics_work_batch_append(_DWORD *this, int a2)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *this == 1024 )
    return -1;
  v3 = (*this)++;
  *(this + v3 + 1) = a2;
  return v3;
}

