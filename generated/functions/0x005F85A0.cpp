// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F85A0 rf_model_geometry_lod_table_construct_noop_vectors
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall68-byte table:invokes default vector constructor0x4F2700 at28(center),44(min),56(max). That callee returns this and writes nothing,so this routine leaves ALL table bytes uninitialized,including these vectors,count,pointers,distances,radius. Returns this;not a zero constructor.
int __thiscall rf_model_geometry_lod_table_construct_noop_vectors(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 28));
  rf_vector3_default_construct_noop((void *)(this + 44));
  rf_vector3_default_construct_noop((void *)(this + 56));
  return this;
}

