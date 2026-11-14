// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005562C0 rf_vertex_component_record_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Constructs24-byte temporary component record used by5547E0: XYZ default constructor is a no-op, so coordinates remain uninitialized; initializes DWORD member pointer array at12 with capacity0. Returns receiver; caller must zero XYZ before accumulation.
_DWORD *__thiscall rf_vertex_component_record_construct(_DWORD *this)
{
  rf_vector3_default_construct_noop(this);
  rf_dword_array_construct_capacity(this + 3, 0);
  return this;
}

