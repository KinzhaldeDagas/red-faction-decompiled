// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486950 rf_material_restitution_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl signed material id. IDs1..9 load FLOAT elasticity/restitution at0x6FFE98+28*id; every id<=0 or>=10 loads record0 offset0. Returns via x87 ST0 without clamping, normalization,
// pair combination or table-loading side effect. Default0 is a real authored record, not a hard-coded coefficient.
float __cdecl rf_material_restitution_get(int material_id)
{
  if ( material_id <= 0 || material_id >= 10 )
    return rf_material_physics_records[0].elasticity;
  else
    return rf_material_physics_records[material_id].elasticity;
}

