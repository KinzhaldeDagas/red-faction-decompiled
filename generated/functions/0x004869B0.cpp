// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004869B0 rf_material_density_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, material/foley parse and ownership, RFString input ABI, bitmap cache, property fallback and directional sound numbering): 
// Cdecl signed material id. IDs1..9 load FLOAT density at0x6FFE98+28*id+8; id<=0 or>=10 falls back to record0 offset8. No sign/finite/range validation or unit conversion; x87
// floating return.
float __cdecl rf_material_density_get(int material_id)
{
  if ( material_id <= 0 || material_id >= 10 )
    return rf_material_physics_records[0].density;
  else
    return rf_material_physics_records[material_id].density;
}

