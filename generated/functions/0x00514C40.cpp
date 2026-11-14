// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00514C40 rf_mesh_decal_collection48_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscallcollection48,returnreceiver,no stackargs. Only calls514C60 onreceiver+4,which calls verified no-op vector-prefix default. Initializes NO bytes:neither textureDWORD0,embedded polygon-ring32/36,nor active/free links40/44. Recovered array constructor62D5E0 applies it to50records stride48;two recovered sentinel constructors apply same body. Runtime5144D0 initializes actual rings.
char *__thiscall rf_mesh_decal_collection48_construct_noop(char *this)
{
  rf_mesh_decal_polygon36_construct_noop(this + 4);
  return this;
}

