// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051BF40 rf_solid_center_on_vertex_mean
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall no stack args. Constructs no-op local vector,computes arithmetic mean of stored vertex positions via51BEC0,then subtracts that vector from all vertices/stored bounds via51C4E0. Mean is vertex-weighted,not volume/area centroid or AABB midpoint. Empty vertex array produces zero local from mean helper;still executes translation/finalization helper. Does not recalculate bounds,center field,room tree or UVs. Stored int return follows translation-helper register residue.
int __thiscall rf_solid_center_on_vertex_mean(char *this)
{
  float mean[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(mean);
  rf_solid_compute_vertex_mean(this, mean);
  return rf_solid_translate_by_subtracting_offset((float *)this, mean);
}

