// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE3B0 rf_scene_model_state152_default_construct_members
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Default constructor for152-byte model states: calls no-op vector defaults at+4,+32,+80 and no-op3x3 matrix defaults at+44,+92. Consequently no object bytes initialized here. Explicit bind constructor5B2500 supplies state afterward; owned pointers+128/+132 not reset by this callback.
void __thiscall rf_scene_model_state152_default_construct_members(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_vector3_default_construct_noop(this + 32);
  rf_matrix3_construct(this + 44);
  rf_vector3_default_construct_noop(this + 80);
  rf_matrix3_construct(this + 92);
}

