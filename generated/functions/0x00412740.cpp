// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412740 rf_entity_construct_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Thiscall ECX caller-owned runtime ENTITY storage, no stack args/plainRET, EAX=this; not allocation or full gameplay spawn. In
// native order constructs COMMON members; AI block+672; retained vector+2004 and matrix+2016; invalid timestamps+2072,+2096; vector bundle+2144; capacity0 DWORD arrays+2252,+2264;
// invalid timestamps+4972,+4976,+4980,+4988,+5020,+5024,+5028; vector+5048; invalid timestamp+5068; vector+5088; invalid timestamps+5116,+5132,+5140; capacity0 array+5144;
// vectors+5172,+5184; invalid timestamp+5208; RGBA member+5236; invalid timestamp+5264. Vector/matrix/RGBA default constructors are no-ops, so these calls do not zero poses/colors;
// timestamp constructor writes-1, arrays establish empty storage. Numeric+5140 is runtime timestamp member, not class-definition metadata. MSVC SEH registers staged COMMON/AI/three
// arrays, unwind map657F8C with622400..622432 cleanup tails; no direct vtable stores or global registration in this body.
char *__thiscall rf_entity_construct_members(char *this)
{
  rf_common_object_construct_members(this);
  sub_412A80(this + 672);
  rf_vector3_default_construct_noop(this + 2004);
  rf_matrix3_construct(this + 2016);
  rf_timestamp4_construct_invalid((int *)this + 518);
  rf_timestamp4_construct_invalid((int *)this + 524);
  rf_vector_bundle_construct_invalid_timestamp92((int)(this + 2144));
  rf_dword_array_construct_capacity(this + 2252, 0);
  rf_dword_array_construct_capacity(this + 2264, 0);
  rf_timestamp4_construct_invalid((int *)this + 1243);
  rf_timestamp4_construct_invalid((int *)this + 1244);
  rf_timestamp4_construct_invalid((int *)this + 1245);
  rf_timestamp4_construct_invalid((int *)this + 1247);
  rf_timestamp4_construct_invalid((int *)this + 1255);
  rf_timestamp4_construct_invalid((int *)this + 1256);
  rf_timestamp4_construct_invalid((int *)this + 1257);
  rf_vector3_default_construct_noop(this + 5048);
  rf_timestamp4_construct_invalid((int *)this + 1267);
  rf_vector3_default_construct_noop(this + 5088);
  rf_timestamp4_construct_invalid((int *)this + 1279);
  rf_timestamp4_construct_invalid((int *)this + 1283);
  rf_timestamp4_construct_invalid((int *)this + 1285);
  rf_dword_array_construct_capacity(this + 5144, 0);
  rf_vector3_default_construct_noop(this + 5172);
  rf_vector3_default_construct_noop(this + 5184);
  rf_timestamp4_construct_invalid((int *)this + 1302);
  rf_rgba8_default_construct_noop(this + 5236);
  rf_timestamp4_construct_invalid((int *)this + 1316);
  return this;
}

