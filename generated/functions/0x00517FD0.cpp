// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517FD0 rf_solid_face_list_remove
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall counted solid-face-list(head0,count4),targetFace,RET4. Decrement count BEFORE membership test. Head match: head=target.next84,return targetEAX,and LEAVE removed next84 unchanged. Nonhead first matching predecessor: bypass target and clear target.next84=0,returntarget. Missing target still decrements count and returns original head residue. No lowerbound,count reconciliation,NULLtarget/cycle/duplicate checks; emptyNULLhead withNULLtarget dereferences84. Does not destroy face,clear room68/spatial72 or their separate92/88 links. Owner wrappers must handle lifetime/other lists separately. Earlier blanket removed-next clearing claim corrected to this branch-specific
// behavior.
int __thiscall rf_solid_face_list_remove(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  --*(this + 1);
  if ( *this == a2 )
  {
    *this = *(_DWORD *)(a2 + 84);
    return a2;
  }
  else
  {
    result = *this;
    for ( i = *this; i; i = *(_DWORD *)(i + 84) )
    {
      if ( *(_DWORD *)(i + 84) == a2 )
      {
        *(_DWORD *)(i + 84) = *(_DWORD *)(a2 + 84);
        *(_DWORD *)(a2 + 84) = 0;
        return a2;
      }
    }
  }
  return result;
}

