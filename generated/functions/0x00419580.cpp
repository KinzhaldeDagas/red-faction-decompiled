// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419580 rf_geomod_debris_spawn_config_init
// UNREALRED VERIFIED [reload-clip-physics-20261013] Zeroes position, linear velocity config+48 and angular velocity config+60 via0x5595E0; installs identity orientation at+12. Reload clip caller0x421480 overwrites position, linear velocity and orientation but leaves angular velocity zero. Do not infer randomized magazine spin from the unused normalized local temporary in that caller.
int __thiscall rf_geomod_debris_spawn_config_init(int this)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_matrix3_construct((char *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 48));
  rf_vector3_default_construct_noop((void *)(this + 60));
  rf_vector3_zero_return_destination((float *)this);
  rf_identity_orientation_matrix((float *)(this + 12));
  rf_vector3_zero_return_destination((float *)(this + 48));
  rf_vector3_zero_return_destination((float *)(this + 60));
  *(_DWORD *)(this + 72) = 1000;
  *(_DWORD *)(this + 76) = 0;
  *(_DWORD *)(this + 80) = -1;
  *(_DWORD *)(this + 84) = 0;
  *(_DWORD *)(this + 88) = 0;
  *(_DWORD *)(this + 96) = 0;
  *(_DWORD *)(this + 92) = 0;
  return this;
}

