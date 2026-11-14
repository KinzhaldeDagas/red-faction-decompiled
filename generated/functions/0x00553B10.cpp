// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00553B10 rf_solid_repair_faces_incident_to_vertex
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): ECX is the solid receiver, with one stack argument vertex and RET4; old stdcall signature dropped the receiver. Iterates vertex incident-face array32 using live count and invokes 553B60(solid,face). Repair may mutate topology while this loop is running; no snapshot. Return EAX is incidental count.
void __thiscall rf_solid_repair_faces_incident_to_vertex(void *this, void *a2)
{
  int *v2; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((char *)a2 + 32); ++i )
  {
    v2 = (int *)sub_552200((_DWORD *)a2 + 8, i);
    rf_solid_triangulate_face_if_nonplanar(*v2);
  }
}

