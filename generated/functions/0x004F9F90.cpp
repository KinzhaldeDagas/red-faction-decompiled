// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F9F90 rf_event_goto_build_from_generic_fields
// UNREALRED VERIFIED [ai-goto-event-20260826]: Creates mission-event type 5 (Goto). It stores generic booleans at event +0x2B8/+0x2B9 and stores equality-to-one normalization of generic integers 0/1 at +0x2BA/+0x2BB.
// UNREALRED VERIFIED [serialized-event-bool-20260923]: The two char arguments are copied without normalization, but the RFL loader supplies normalized reader outputs. Thus serialized boolean byte 2 or 255 becomes event byte 1; arbitrary direct-builder byte 2/255 would remain 2/255 and fail downstream exact-one comparisons. Do not replace source-file nonzero semantics with exact-one semantics.
_BYTE *__cdecl rf_event_goto_build_from_generic_fields(float *a1, char a2, char a3, int a4, int a5)
{
  _BYTE *v6; // [esp+0h] [ebp-4h]

  v6 = (_BYTE *)rf_mission_event_create_at_position(a1, 5u);
  if ( v6 )
  {
    v6[696] = a2;
    v6[697] = a3;
    v6[698] = a4 == 1;
    v6[699] = a5 == 1;
  }
  return v6;
}

