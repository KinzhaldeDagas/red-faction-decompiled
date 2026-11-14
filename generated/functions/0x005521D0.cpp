// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005521D0 rf_lightmap_polygon2_32_construct_empty
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Runs no-op defaultvectorconstructor across32 slots of8bytes then writes DWORDcount atthis+256=0. Returns this. Does not zero256-byte coordinatepayload. Callerowns260-byte record; no allocation or capacity enforcement in constructor.
int __thiscall rf_lightmap_polygon2_32_construct_empty(int this)
{
  rf_vector_construct_no_unwind((char *)this, 8u, 32, rf_vector3_default_construct_noop);
  *(_DWORD *)(this + 256) = 0;
  return this;
}

