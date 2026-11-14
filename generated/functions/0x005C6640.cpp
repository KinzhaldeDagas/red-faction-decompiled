// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C6640 rf_exception_code_description
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): Builds a 24-entry code/string table on the stack and returns the description for a matching exception code, or "Unknown exception type". Includes Control-C/Break, alignment, breakpoint, access violation, in-page, memory, instruction, floating point, integer, stack, DLL initialization and Microsoft C++ exceptions. The decompiler expression v4[2*i-1] at i=0 addresses the preceding initialized first-code local; it is a contiguous table layout artifact, not an uninitialized read.
const char *__cdecl rf_exception_code_description(int a1)
{
  unsigned int i; // [esp+0h] [ebp-C4h]
  int v3; // [esp+4h] [ebp-C0h]
  _DWORD v4[47]; // [esp+8h] [ebp-BCh]

  v3 = 1073807365;
  v4[0] = "a Control-C";
  v4[1] = 1073807368;
  v4[2] = "a Control-Break";
  v4[3] = -2147483646;
  v4[4] = "a Datatype Misalignment";
  v4[5] = -2147483645;
  v4[6] = "a Breakpoint";
  v4[7] = -1073741819;
  v4[8] = "an Access Violation";
  v4[9] = -1073741818;
  v4[10] = "an In Page Error";
  v4[11] = -1073741801;
  v4[12] = "a No Memory";
  v4[13] = -1073741795;
  v4[14] = "an Illegal Instruction";
  v4[15] = -1073741787;
  v4[16] = "a Noncontinuable Exception";
  v4[17] = -1073741786;
  v4[18] = "an Invalid Disposition";
  v4[19] = -1073741684;
  v4[20] = "a Array Bounds Exceeded";
  v4[21] = -1073741683;
  v4[22] = "a Float Denormal Operand";
  v4[23] = -1073741682;
  v4[24] = "a Float Divide by Zero";
  v4[25] = -1073741681;
  v4[26] = "a Float Inexact Result";
  v4[27] = -1073741680;
  v4[28] = "a Float Invalid Operation";
  v4[29] = -1073741679;
  v4[30] = "a Float Overflow";
  v4[31] = -1073741678;
  v4[32] = "a Float Stack Check";
  v4[33] = -1073741677;
  v4[34] = "a Float Underflow";
  v4[35] = -1073741676;
  v4[36] = "an Integer Divide by Zero";
  v4[37] = -1073741675;
  v4[38] = "an Integer Overflow";
  v4[39] = -1073741674;
  v4[40] = "a Privileged Instruction";
  v4[41] = -1073741571;
  v4[42] = "a Stack Overflow";
  v4[43] = -1073741502;
  v4[44] = "a DLL Initialization Failed";
  v4[45] = -529697949;
  v4[46] = "a Microsoft C++ Exception";
  for ( i = 0; i < 0x18; ++i )
  {
    if ( a1 == v4[2 * i - 1] )
      return (const char *)v4[2 * i];
  }
  return "Unknown exception type";
}

