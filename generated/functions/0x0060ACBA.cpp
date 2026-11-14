// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060ACBA sub_60ACBA
// UNREALRED VERIFIED [reflection-uv-20260903]: Tail-dispatches the two x87 inputs through CRT descriptor 0x00665D60. That descriptor begins with the length-prefixed name 'atan2' and references __fFATN2/_rtforatn20 handlers.
long double __usercall sub_60ACBA@<st0>(long double a1@<st1>, long double a2@<st0>)
{
  return _cintrindisp2(&unk_665D60, a1, a2);
}

