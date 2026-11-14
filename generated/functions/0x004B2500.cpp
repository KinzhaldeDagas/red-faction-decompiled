// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B2500 rf_motion_sample_buffer_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): ECX buffer,no stackargs. Invokes20 vector constructors at EACH of five contiguous240-byte arrays offsets0/240/480/720/960;vector constructor writes no object bytes,so these arrays remain uninitialized. Constructs two padded Catmull-Rom objects at1424 and1812,then delegates reset25B0. Returns bufferEAX. Does not allocate or own-free storage,initialize sample arrays/timestamps/cursor1324 or create a complete sample. No NULL guard.
char *__thiscall rf_motion_sample_buffer_construct(char *this)
{
  rf_vector_construct_no_unwind(this, 0xCu, 20, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(this + 240, 0xCu, 20, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(this + 480, 0xCu, 20, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(this + 720, 0xCu, 20, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(this + 960, 0xCu, 20, rf_vector3_default_construct_noop);
  rf_catmull_rom32_construct_points(this + 1424);
  rf_catmull_rom32_construct_points(this + 1812);
  rf_motion_sample_buffer_reset((int)this);
  return this;
}

