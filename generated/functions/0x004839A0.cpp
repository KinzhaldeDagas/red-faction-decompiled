// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004839A0 rf_geomod_georegion_init
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall80-byte region constructor, returns receiver. Calls no-op vector constructors for center16 and dimensions68, no-op matrix row constructor at28. Writes NO region fields:
// shape0,hardness4,directional8,ice9,padding10/11,scalar12,radius64 and vector/matrix payload retain allocation bytes. In particular legacy<99 loader clears directional8 but leaves
// ice9 untouched; this constructor supplies no default false ice or identity orientation. Actual field initialization is loader-version dependent.
char *__thiscall rf_geomod_georegion_init(char *this)
{
  rf_vector3_default_construct_noop(this + 16);
  rf_matrix3_construct(this + 28);
  rf_vector3_default_construct_noop(this + 68);
  return this;
}

