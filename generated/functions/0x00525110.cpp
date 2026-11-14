// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525110 rf_decal_parameter_record_construct
// UNREALRED VERIFIED [decal-face-links-20261028]: Constructs vector/matrix/vector subobjects+0/+12/+48, then explicitly zeroes position/dimensions and writes identity matrix. Writes dword+60=-1,+64=0,byte+68=0xFF,dword+72=0,+76=-1,+80=0. Other bytes at+69..71 are not explicitly written. This parameter-record layout differs from236-byte runtime decal; do not transfer runtime field meanings by matching offsets.
int __thiscall rf_decal_parameter_record_construct(int this)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_matrix3_construct((char *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 48));
  rf_vector3_zero_return_destination((float *)this);
  rf_identity_orientation_matrix((float *)(this + 12));
  rf_vector3_zero_return_destination((float *)(this + 48));
  *(_DWORD *)(this + 60) = -1;
  *(_DWORD *)(this + 64) = 0;
  *(_BYTE *)(this + 68) = -1;
  *(_DWORD *)(this + 72) = 0;
  *(_DWORD *)(this + 76) = -1;
  *(_DWORD *)(this + 80) = 0;
  return this;
}

