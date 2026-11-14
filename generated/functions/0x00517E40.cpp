// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517E40 rf_geomod_room_face_list_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall counted-list receiver(head0,count4),face,RET4. Increment count BEFORE pointer checks. Empty head: face.next92=NULL,head=face. Nonempty: traverse face.next92 to finalNULL,write newface.next92=NULL and oldtail.next92=newface. On valid finite list returnEAX0 (loaded priorNULL head/tail link),not face/index/success. No tail cache,duplicate/member/cycle orNULLface checks; appending an existing tail can create a self-cycle. Does NOT set face.room68,expand room bounds,register solid/spatial ownership or change face84/88 links; room attach515E70 does additional work.
int __thiscall rf_geomod_room_face_list_append(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  ++*(this + 1);
  if ( *this )
  {
    for ( i = *this; *(_DWORD *)(i + 92); i = *(_DWORD *)(i + 92) )
      ;
    result = *(_DWORD *)(i + 92);
    *(_DWORD *)(a2 + 92) = result;
    *(_DWORD *)(i + 92) = a2;
  }
  else
  {
    result = *this;
    *(_DWORD *)(a2 + 92) = *this;
    *this = a2;
  }
  return result;
}

