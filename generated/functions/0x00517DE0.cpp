// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00517DE0 rf_face_metadata_set_flag_40_lowbyte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, room destruction/reconstruction,shared-vertex portal-side voting,detail references and intrusive list edge cases,original ECX/stack flow and PE bytes): Thiscall flags/metadataDWORD receiver,one stackDWORD whose LOWBYTE is tested,RET4,return receiverEAX. NonzeroLOWBYTE sets bit0x40; zeroLOWBYTE clears0x40; allother flag bits preserved. Fullinteger256 therefore CLEARS bit rather than setting it. No normalization ofstoredbyte,portal/liquid/material checks,geometry changes,allocation or secondary fields touched.
unsigned int *__thiscall rf_face_metadata_set_flag_40_lowbyte(unsigned int *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 )
    v2 = *this | 0x40;
  else
    v2 = *this & 0xFFFFFFBF;
  *this = v2;
  return this;
}

