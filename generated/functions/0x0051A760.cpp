// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051A760 rf_vertex_all_incident_faces_have_flag8
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): Returns byte1 only if EVERY face in vertex incident array32 has metadata DWORD40 bit0x8 set, via4C56E0; first clear bit returns0. Empty incidence returns1 vacuously. Clone welding compares only this boolean, not complete flags, room IDs, UVs, or normal data.
char __cdecl rf_vertex_all_incident_faces_have_flag8(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 32)); ++i )
  {
    v2 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 32), i);
    if ( !rf_face_metadata_has_flag8((_DWORD *)(v2 + 40)) )
      return 0;
  }
  return 1;
}

