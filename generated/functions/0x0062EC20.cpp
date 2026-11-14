// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EC20 rf_static_destroy_array_006edee0
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 9-instruction/24-byte body independently matched to original PE. No consumed arguments/plain RET. Four raw stack slots passed to stdcall EH
// vector destructor6066BD are(base006EDEE0,byteStride12,signedCount4,thiscallCallback004873C0 rf_glare_definition52_destroy_name_member); RET16 in helper owns argument cleanup,
// wrapper does NOT ADD16. Verified helper starts at base+low32(count*stride), decrements count and pointer BEFORE callback, hence normal order indices3 down to0 at base+i*12. No
// live-count/capacity/initialized-byte gate: destroys complete FIXED constructed extent. Callback receives each element in ECX with no stack argument. Original atexit registration
// PUSH at0x0062A2FB. No containing static-array operator delete or wrapper reset/rollback; callback owns member cleanup. Exception handling and remaining reverse cleanup delegated
// to6066BD. Raw stride is proven by pushes and is not inferred from callback name or one named record size; shared prefix/string destructor may be used at other strides. Result
// register incidental, no normalized success value.
void rf_static_destroy_array_006edee0()
{
  `eh vector destructor iterator'(byte_6EDEE0, 0xCu, 4, rf_glare_definition52_destroy_name_member);
}

