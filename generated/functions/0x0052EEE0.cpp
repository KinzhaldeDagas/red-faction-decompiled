// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EEE0 rf_geomod_face_set_operand_exact_one
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): ThiscallmetadataDWORDpointer,intoperand RET4 returnspointer. Setmask0x00800000 ONLYwhenfullDWORDargument==1;ANYothervalueincluding2/-1clearswithFF7FFFFF. No bool-nonzeronormalizationor classchange;memorybaseismetadata,notwholeface.
unsigned int *__thiscall rf_geomod_face_set_operand_exact_one(unsigned int *this, int a2)
{
  unsigned int *result; // eax
  unsigned int v3; // ecx

  result = this;
  if ( a2 == 1 )
    v3 = (unsigned int)&unk_800000 | *this;
  else
    v3 = *this & 0xFF7FFFFF;
  *this = v3;
  return result;
}

