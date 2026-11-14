// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486A10 rf_material_traction_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl signed material id. IDs1..9 load FLOAT traction at0x6FFE98+28*id+16; id<=0 or>=10 falls back to record0 offset16. No clamping, speed calculation or mutation; x87 floating
// return.
float __cdecl rf_material_traction_get(int material_id)
{
  if ( material_id <= 0 || material_id >= 10 )
    return rf_material_physics_records[0].traction;
  else
    return rf_material_physics_records[material_id].traction;
}

