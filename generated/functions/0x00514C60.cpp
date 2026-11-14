// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514C60 rf_mesh_decal_polygon36_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscallpolygon36,returnreceiver,no stackargs. Only calls491340 no-op vector-prefix constructor onreceiver;no bytewrites. Does not initialize vertex sentinel20/24,collection/free links28/32 orpayload. Recovered array constructor62D620 applies it to150records stride36;sentinel62D640 uses same body. Runtimepoolreset5144D0 supplies rings.
void *__thiscall rf_mesh_decal_polygon36_construct_noop(void *this)
{
  rf_vector_prefix_construct_noop(this);
  return this;
}

