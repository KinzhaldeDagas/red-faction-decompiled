// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051EA20 rf_geomod_spatial_node_face_list_append
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall list header(head0,count4),face RET4. Increment DWORD count BEFORE linking. Empty head: set face.nextSpatial88=head(NULL), set head=face. Nonempty: linear walk existing face+88 untilNULL, set new face+88 to terminalNULL then tail+88=new. No duplicate/cycle/null/member-owner checks, tail cache or allocation. Appending same sole existing face can produce self-cycle. Does not set face spatial-owner72, room-next92, solid-next84 or node bounds. Returns EAX terminalNULL (normally0), not inserted face or index.
int __thiscall rf_geomod_spatial_node_face_list_append(int *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  ++*(this + 1);
  if ( *this )
  {
    for ( i = *this; *(_DWORD *)(i + 88); i = *(_DWORD *)(i + 88) )
      ;
    result = *(_DWORD *)(i + 88);
    *(_DWORD *)(a2 + 88) = result;
    *(_DWORD *)(i + 88) = a2;
  }
  else
  {
    result = *this;
    *(_DWORD *)(a2 + 88) = *this;
    *this = a2;
  }
  return result;
}

