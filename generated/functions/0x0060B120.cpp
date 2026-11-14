// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060B120 __allmul
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Compiler helper stdcall(two64bit values), full
// modulo64 product EDX:EAX, RET16callee cleanup. Both highDWORDs0 ->single unsignedMULlow*low. Otherwise sum LOW32(highA*lowB)+LOW32(lowA*highB) into highhalf ofunsigned
// lowA*lowB,ignoreallbitsabove64. Same productbits for signed/unsignedinterpretation; preservesEBX onhardpath,doesnotuseESI/EDI. No overflowcheck,x87,memoryoutput,errno,allocation or
// callbacks; modifiesonlyregistersandownstack.
__int64 __stdcall _allmul(__int64 a1, __int64 a2)
{
  if ( HIDWORD(a1) | HIDWORD(a2) )
    return a1 * a2;
  else
    return (unsigned int)a2 * (unsigned __int64)(unsigned int)a1;
}

