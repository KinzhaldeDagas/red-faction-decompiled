// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512270 rf_weapon_record1360_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Thiscall ECX record pointer,no stack arguments,returns receiver EAX. Misidentified Microsoft Concurrency constructor; static callback62D510 constructs64records stride1360 at912000 using this function and512440 destructor. Constructs RFStrings at0,8,16,28,40,64,620; invokes NO-WRITE vector constructors at76,88,648. EH-vector constructs3records stride28 at672 and12records at756 through4A4270 (only RFStrings+0/+8), destructor49FAF0; constructs3RFStrings stride8 at1120. NO-WRITE vectors1160,1176,1192; then RFStrings1208,1228,1256,1272,1316,1344. No blanket memset or scalar/bitmap/count/cache/size initialization: no-op vector/matrix defaults retain supplied storage. Static
// zero initialization is separate from this function. SEH tails unwind completed strings/arrays in reverse; does not allocate/free whole record. Corrected application constructor classification and erased false SDK receiver type.
void *__thiscall rf_weapon_record1360_construct(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  rf_string_construct_empty((_DWORD *)self + 4);
  rf_string_construct_empty((_DWORD *)self + 7);
  rf_string_construct_empty((_DWORD *)self + 10);
  rf_string_construct_empty((_DWORD *)self + 16);
  rf_vector3_default_construct_noop((char *)self + 76);
  rf_vector3_default_construct_noop((char *)self + 88);
  rf_string_construct_empty((_DWORD *)self + 155);
  rf_vector3_default_construct_noop((char *)self + 648);
  `eh vector constructor iterator'(
    (char *)self + 672,
    0x1Cu,
    3,
    (void (__thiscall *)(void *))rf_two_rfstring_prefix_construct,
    (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
  `eh vector constructor iterator'(
    (char *)self + 756,
    0x1Cu,
    12,
    (void (__thiscall *)(void *))rf_two_rfstring_prefix_construct,
    (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
  `eh vector constructor iterator'(
    (char *)self + 1120,
    8u,
    3,
    (void (__thiscall *)(void *))rf_string_construct_empty,
    rf_string_destroy_buffer);
  rf_vector3_default_construct_noop((char *)self + 1160);
  rf_vector3_default_construct_noop((char *)self + 1176);
  rf_vector3_default_construct_noop((char *)self + 1192);
  rf_string_construct_empty((_DWORD *)self + 302);
  rf_string_construct_empty((_DWORD *)self + 307);
  rf_string_construct_empty((_DWORD *)self + 314);
  rf_string_construct_empty((_DWORD *)self + 318);
  rf_string_construct_empty((_DWORD *)self + 329);
  rf_string_construct_empty((_DWORD *)self + 336);
  return self;
}

