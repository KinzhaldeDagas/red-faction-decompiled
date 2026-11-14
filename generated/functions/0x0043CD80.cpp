// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CD80 sub_43CD80
// UNREALRED VERIFIED [combat-named-sphere-capacity-20261112]: 40byte assignment copies scalar0/4/8/C/10/14,vector18..20,DWORD24 unchanged fromsource. Itdoesnot initialize missing SP/MPprofile slots. Together569350no-opand43C990copy, firstcacheinitialactivefactor1 isprovedbutunmatched storedSP/MPslots remainunknown; later43C4F0/580 profile reset cannotbe modeledas automatically1 withoutadditionalownerproof.
float *__thiscall sub_43CD80(float *this, float *a2)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  *(this + 4) = a2[4];
  *(this + 5) = a2[5];
  rf_vector_copy(this + 6, copy_result, a2 + 6);
  *(this + 9) = a2[9];
  return this;
}

