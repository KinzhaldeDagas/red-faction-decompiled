// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EF60 rf_geomod_boolean_workspace_face_prepend
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Thiscallcountedfaceheader(head0,count4),face RET4 returnheader. IncrementDWORDcount, setface.nextSolid84=oldhead, thenhead=face. No tailupdate,duplicate/cycle/nullguard,allocation,room/spatial/decalownershiporvertexincidencechanges. Prependsbyidentityandcanloopifduplicate;distinctfromtailappend51EB60.
_DWORD *__thiscall rf_geomod_boolean_workspace_face_prepend(_DWORD *this, int a2)
{
  ++*(this + 1);
  *(_DWORD *)(a2 + 84) = *this;
  *this = a2;
  return this;
}

