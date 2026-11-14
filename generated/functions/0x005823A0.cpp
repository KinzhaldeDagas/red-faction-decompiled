// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005823A0 rf_short_quaternion_construct_0001
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Write four16-bit words exactly0,0,0,1 and return this. Used by snapshot common/blood/GeoMod constructors. This is not normalized fixed-point quaternion identity for decoder0x41F160(scale~1/16383); runtime packing normally overwrites components. No division or float normalization here.
_WORD *__thiscall rf_short_quaternion_construct_0001(_WORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  *(this + 2) = 0;
  *(this + 3) = 1;
  return this;
}

