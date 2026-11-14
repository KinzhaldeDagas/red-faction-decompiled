// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A4270 rf_two_rfstring_prefix_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Thiscall receiver,no stack arguments,returns receiver. Constructs only RFStrings at0 and8 via55F5D0; no writes to cache+16,sound+20 or remaining scalar bytes. Weapon constructor512270 uses as callback for3state/12action records stride28; reverse destructor49FAF0 destroys strings+8 then0. False Microsoft Concurrency constructor/type/library classification corrected; no allocation/whole-record zeroing.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Original two-field constructor contract preserved and generic name now reflects verified16-byte level-record array use. Reallocator45E160 supplies this callback to EH
// vector construction withstride16,alongside destructor49FAF0. Native constructor only initializes RFStrings0 then8,returns receiver,no stack args;same prefix remains valid for
// earlier28-byte weapon animation and larger networking records. Does not know whole record stride or zero trailing fields;no type/layout expansion. Shared SEH cleanup unchanged.
void *__thiscall rf_two_rfstring_prefix_construct(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  return self;
}

