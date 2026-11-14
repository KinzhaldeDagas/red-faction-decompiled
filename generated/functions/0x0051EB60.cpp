// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EB60 rf_solid_face_list_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall counted intrusive header(head0,count4),face RET4. Increment count before any linking; empty head sets face.nextSolid84=NULL/head=face. Else linear search nextSolid84 forNULL, set new.nextSolid84=NULL and tail.nextSolid84=new. Does not establish ownership/incidence, spatial next88, room next92, face geometry or bounds. No duplicate/null/cycle guard; duplicate sole face can self-link. EAX terminalNULL normally0, not face. Separate list from51EA20 despite identical algorithm.
int __thiscall rf_solid_face_list_append(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  ++*(this + 1);
  if ( *this )
  {
    for ( i = *this; *(_DWORD *)(i + 84); i = *(_DWORD *)(i + 84) )
      ;
    result = *(_DWORD *)(i + 84);
    *(_DWORD *)(a2 + 84) = result;
    *(_DWORD *)(i + 84) = a2;
  }
  else
  {
    result = *this;
    *(_DWORD *)(a2 + 84) = *this;
    *this = a2;
  }
  return result;
}

