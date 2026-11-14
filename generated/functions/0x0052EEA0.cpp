// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EEA0 rf_geomod_face_set_boolean_scratch_bit27
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataDWORDpointer,lowBYTEenable RET4 returnssamepointer. NonzerolowBYTE OR0x08000000;zerolowBYTE AND0xF7FFFFFF. Otherbitsunchanged,no class/operand/faceownershipwrites. Int256 passedthroughBYTE wouldclear,notset. Scratchsemanticrestrictedtobitidentityhere.
unsigned int *__thiscall rf_geomod_face_set_boolean_scratch_bit27(unsigned int *this, char a2)
{
  unsigned int v2; // edx

  if ( a2 )
    v2 = *this | 0x8000000;
  else
    v2 = *this & 0xF7FFFFFF;
  *this = v2;
  return this;
}

