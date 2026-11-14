// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CED40 rf_scene_record44_construct_vector_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Loader uses44-byte records;constructor only calls no-op vector default at+12 and returns receiver. No member bytes initialized. Prior Concurrency::SchedulerCore constructor name/type is false SDK match;actual class semantics beyond scene pool record remain unproven.
void *__thiscall rf_scene_record44_construct_vector_noop(void *this)
{
  rf_vector3_default_construct_noop((char *)this + 12);
  return this;
}

