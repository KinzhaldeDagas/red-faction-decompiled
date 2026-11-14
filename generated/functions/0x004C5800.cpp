// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C5800 rf_glass_face_validate_and_register
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, original fragment spawn and bounded pool, eight-vertex twelve-triangle layout, fourteen-ray scoring, full room-pointer ABI and native glass branching): 
// Cdecl face ->canonical ALbool. NULLfalse. Calls531270 circular CORNER COUNT and requires exactly4, not geometry type code4. Looks up face DWORD68(owner/identity pointer) in pointer
// array823B68; existing index>-1 rejects, otherwise appends that DWORD and returns1. Registry keys are NOT face addresses: different faces sharing same owner collide; NULL owner can
// be registered once and then suppress other NULL-owner faces. No material/is-glass flag, geometric rectangle/planarity, distinct-position, authority,
// array-capacity/allocation-success or ownerNULL validation. Lookup/append precedes shatter; no registry rollback here.
char __cdecl rf_glass_face_validate_and_register(_DWORD *a1)
{
  if ( !a1 )
    return 0;
  if ( rf_geomod_face_corner_count(a1) != 4 )
    return 0;
  if ( rf_pointer_array_find_index(unk_823B68, a1[17]) > -1 )
    return 0;
  rf_pointer_array_append_dword(unk_823B68, a1[17]);
  return 1;
}

