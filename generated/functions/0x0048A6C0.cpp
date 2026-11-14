// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A6C0 rf_moving_solid_submit_faces_unless_suppressed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Cdecl common object pointer. Unsigned suppression BYTE704604 ANY nonzero skips render and returns that byte EAX. Otherwise if geometry pointerDWORD660 nonnull calls
// renderer_submit_room_faces_backend_wrapper(geometry,common position60,orientation72,0), returns delegate. Null geometry returns zero from loaded suppression byte. No object NULL
// guard, mode/visibility test, world-coordinate modification or drawing of mover keys here.
int __cdecl rf_moving_solid_submit_faces_unless_suppressed(int a1)
{
  int result; // eax

  result = unk_704604;
  if ( !unk_704604 )
  {
    if ( *(_DWORD *)(a1 + 660) )
      return rf_renderer_submit_room_faces_backend_wrapper(*(_DWORD *)(a1 + 660), (float *)(a1 + 60), a1 + 72, 0);
  }
  return result;
}

