// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517EC0 rf_geomod_room_face_detach
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall counted room-face-list(head0,count4),targetFace,RET4. Decrement count UNCONDITIONALLY before checking membership. Head match updates head=target.next92,returns targetEAX WITHOUT clearing target.next92. Nonhead first predecessor match bypasses target,clears target.next92=0,returns target. Missing target changes count only; EAX retains original head. No count underflow,NULLtarget,cycle or membership guard; headNULL/targetNULL dereferences target+92. Does NOT clear face.room68,repair bounds,unlink solid84/spatial88 or free anything; called by515E70 which replaces room68 afterward.
int __thiscall rf_geomod_room_face_detach(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  --*(this + 1);
  if ( *this == a2 )
  {
    *this = *(_DWORD *)(a2 + 92);
    return a2;
  }
  else
  {
    result = *this;
    for ( i = *this; i; i = *(_DWORD *)(i + 92) )
    {
      if ( *(_DWORD *)(i + 92) == a2 )
      {
        *(_DWORD *)(i + 92) = *(_DWORD *)(a2 + 92);
        *(_DWORD *)(a2 + 92) = 0;
        return a2;
      }
    }
  }
  return result;
}

