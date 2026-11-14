// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052E970 rf_geomod_boolean_run_synchronous
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Cdecl13args forwardedtoinit. IGNOREinitializerreturn. Do-call advanceATLEASTONCE, repeatwhileALnonzero,returnzero-extendedlastAL(normally0). No active-operation guard, timeout,budget,cancel or failurestatus. Ifinitfailedhypothetically,advancewouldoperatepreviousglobalstage; invalidstage>=8 canloop/writeoutofbounds instead ofsuccessfulcompletion.
int __cdecl rf_geomod_boolean_run_synchronous(
        int a1,
        int a2,
        int a3,
        char a4,
        int a5,
        int a6,
        int a7,
        int a8,
        float a9,
        int a10,
        char a11,
        int a12,
        int a13)
{
  int result; // eax

  rf_geomod_boolean_init(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);
  do
    result = (unsigned __int8)rf_geomod_boolean_advance();
  while ( (_BYTE)result );
  return result;
}

