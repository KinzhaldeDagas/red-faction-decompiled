// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004129A0 rf_common_object_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Thiscall receiver,no stackargs. No-op vectorconstructors4/60/108/520/568/640,matrixconstructors72/532/580;constructs emptyRFString at24 (DWORDextent24=0,buffer28=NULL) and physics-state at136. Physics constructor writes ONLY sphere-collection header388/392/396=count0/capacity0/baseNULL;its other vector/matrix/contact constructors do not initialize bytes. Thus these five DWORDs are the only persistent normal receiver writes;runtime type36,UID44,commonflags/pose/model/scalars remain uninitialized. Returnsreceiver;no outer allocation,oldstorage release or complete object reset.
char *__thiscall rf_common_object_construct_members(char *this)
{
  rf_vector3_default_construct_noop(this + 4);
  rf_string_construct_empty((_DWORD *)this + 6);
  rf_vector3_default_construct_noop(this + 60);
  rf_matrix3_construct(this + 72);
  rf_vector3_default_construct_noop(this + 108);
  rf_physics_state_construct_empty_sphere_collection(this + 136);
  rf_vector3_default_construct_noop(this + 520);
  rf_matrix3_construct(this + 532);
  rf_vector3_default_construct_noop(this + 568);
  rf_matrix3_construct(this + 580);
  rf_vector3_default_construct_noop(this + 640);
  return this;
}

