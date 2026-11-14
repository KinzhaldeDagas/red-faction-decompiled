// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00555B80 rf_solid_reverse_all_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Traverses intrusive solid face list112, calls face winding reversal on each, and advances via face next link. Does not rebuild solid/spatial indices here; return becomes null at list exhaustion.
int __thiscall rf_solid_reverse_all_faces(int this)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(this + 112));
  for ( i = result; i; i = result )
  {
    rf_geomod_face_reverse_winding(i);
    result = rf_solid_face_next_link(i);
  }
  return result;
}

