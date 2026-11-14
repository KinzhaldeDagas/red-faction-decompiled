// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005521A0 rf_plane_construct_from_three_world_points
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Runs no-op defaultvectorconstructor onthis,then0x52AA00(this,p0,p1,p2),returns this. Actualgeometry initialized bysecondcall,notdefaultconstructor. No extra degeneracy handling.
void *__thiscall rf_plane_construct_from_three_world_points(void *this, float *a2, float *a3, float *a4)
{
  rf_vector3_default_construct_noop(this);
  rf_plane_set_from_three_world_points((float *)this, a2, a3, a4);
  return this;
}

