// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605ADC _rand
// UNREALRED VERIFIED [combat-native-pickup-runtime-20261111]: CRT rand updates uint32 next=214013*state+2531011 modulo2^32, stores threadData+20, returns(next>>16)&7FFF. Shared by pickup4750C0 railgun(rand%4+1), routes and other consumers. Porting one caller cannot prove full original stream/call-order parity.
int __cdecl rand()
{
  DWORD *v0; // eax
  unsigned int v1; // ecx

  v0 = _getptd();
  v1 = 214013 * v0[5] + 2531011;
  v0[5] = v1;
  return HIWORD(v1) & 0x7FFF;
}

