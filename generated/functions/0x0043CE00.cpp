// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CE00 rf_entity_class5396_construct_members
// [UnrealRed physical spheres 2026-11-12; verified startup629B18 operand/ASM] This function is EntityInfo class-definition constructor (former bogus FLIRT NumaInformation label/type corrected by verified constructor analysis), used by vector construction of75 records at683548 stride1514. Constructs sourcearrayB68 and40-byte cachearray wrappers CEC/E30. No class initialization reset of bit40000000 is proved from model resource retirement.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall self in ECX, no stack arguments, returns self in EAX. Constructs RFString members at offsets0,8,10,18,20,30,38,104,744,13CC; invokes proven no-op
// vector constructors at6C,78,9C,A8,700, which do not initialize vector floats. Invokes count-only array constructor51EBE0 at1BC,1C8,1D4,1E0,1F0,678,69C,6C0,70C,730,B68; constructs
// inline record40/cache-array wrappers atCEC andE30. EH vector iterator6065FA receives base self+F80,stride6C,count10, ctor416D40/dtor416DB0 for ten embedded skin108 records, then
// constructs final string13CC. SEH/C++ state tracks completed subobjects; unwind tails destroy completed strings, call no-op count-header destructors and destroy the completed
// ten-element skin array at the final state. No whole5396-byte memset or scalar/flags default reset is present. Fresh startup native629B10 passes this constructor and
// destructor43D030 to EH vector construction of75 records at683548,stride1514 (5396). This RF EntityInfo/class-record ownership disproves inherited NumaInformation label; clear false
// library flag and replace bogus Concurrency pointer type.
void *__thiscall rf_entity_class5396_construct_members(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  rf_string_construct_empty((_DWORD *)self + 4);
  rf_string_construct_empty((_DWORD *)self + 6);
  rf_string_construct_empty((_DWORD *)self + 8);
  rf_string_construct_empty((_DWORD *)self + 12);
  rf_string_construct_empty((_DWORD *)self + 14);
  rf_vector3_default_construct_noop((char *)self + 108);
  rf_vector3_default_construct_noop((char *)self + 120);
  rf_vector3_default_construct_noop((char *)self + 156);
  rf_vector3_default_construct_noop((char *)self + 168);
  rf_string_construct_empty((_DWORD *)self + 65);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 111);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 114);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 117);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 120);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 124);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 414);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 423);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 432);
  rf_vector3_default_construct_noop((char *)self + 1792);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 451);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 460);
  rf_string_construct_empty((_DWORD *)self + 465);
  rf_embedded_array_construct_count_only_51ebe0((_DWORD *)self + 730);
  rf_inline_record40_array8_construct((char *)self + 3308);
  rf_inline_record40_array8_construct((char *)self + 3632);
  `eh vector constructor iterator'(
    (char *)self + 3968,
    0x6Cu,
    10,
    (void (__thiscall *)(void *))rf_clutter_skin108_construct_strings,
    (void (__thiscall *)(void *))rf_clutter_skin108_destroy_strings);
  rf_string_construct_empty((_DWORD *)self + 1267);
  return self;
}

