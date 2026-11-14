// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2AE0 rf_mesh_decal_request80_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projected mesh decal pools,shadow records,x87 unordered filters and recovered no-op constructors,original ECX/stack flow and PE bytes): Thiscall80-byte request,no stackargs,returnreceiver. Vector defaults12/24 andmatrix36 are no-ops,then explicitly ownerDWORD0=0,textureDWORD4=-1,radiusF32+8=+0;copy threefloat globalvector17F10B0 into BOTH start12/end24;write identitymatrix36..71;flagsDWORD72=2. SelectorDWORD76 NOT initialized. Copies current globalvector,not literal zero;no full-record memset,allocation,owner retention or positive radius. Caller4E22D0 later supplies actual owner/texture/radius/basis/flags/selector.
char *__thiscall rf_mesh_decal_request80_construct(char *this)
{
  float v3[3]; // [esp+4h] [ebp-18h] BYREF
  float copy_result[3]; // [esp+10h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 24);
  rf_matrix3_construct(this + 36);
  *(_DWORD *)this = 0;
  *((_DWORD *)this + 1) = -1;
  *((float *)this + 2) = 0.0;
  rf_vector_copy((float *)this + 3, copy_result, flt_17F10B0);
  rf_vector_copy((float *)this + 6, v3, flt_17F10B0);
  rf_identity_orientation_matrix((float *)this + 9);
  *((_DWORD *)this + 18) = 2;
  return this;
}

