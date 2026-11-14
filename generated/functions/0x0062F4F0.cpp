// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F4F0 rf_static_destroy_array_00912000
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 9-instruction/27-byte body independently matched to original PE. No consumed arguments/plain RET. Four raw stack slots passed to stdcall EH
// vector destructor6066BD are(base00912000,byteStride1360,signedCount64,thiscallCallback00512440 rf_weapon_record1360_destroy_members); RET16 in helper owns argument cleanup, wrapper
// does NOT ADD16. Verified helper starts at base+low32(count*stride), decrements count and pointer BEFORE callback, hence normal order indices63 down to0 at base+i*1360. No
// live-count/capacity/initialized-byte gate: destroys complete FIXED constructed extent. Callback receives each element in ECX with no stack argument. Original atexit registration
// PUSH at0x0062D52E. No containing static-array operator delete or wrapper reset/rollback; callback owns member cleanup. Exception handling and remaining reverse cleanup delegated
// to6066BD. Raw stride is proven by pushes and is not inferred from callback name or one named record size; shared prefix/string destructor may be used at other strides. Result
// register incidental, no normalized success value.
void rf_static_destroy_array_00912000()
{
  `eh vector destructor iterator'(
    rf_weapon_records,
    0x550u,
    64,
    (void (__thiscall *)(void *))rf_weapon_record1360_destroy_members);
}

